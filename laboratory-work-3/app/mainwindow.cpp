#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    currTask = Problem(TestFunc, dTF, d2TF, -1.0, 1.0, 0.0, 0.0);
    ui->graphF->addGraph();
    ui->graphF->graph(0)->setPen(QPen(Qt::green));
    ui->graphF->addGraph();

    ui->graphdF->addGraph();
    ui->graphdF->graph(0)->setPen(QPen(Qt::green));
    ui->graphdF->addGraph();

    ui->graphddF->addGraph();
    ui->graphddF->graph(0)->setPen(QPen(Qt::green));
    ui->graphddF->addGraph();

    replotGraphs();

    ui->tableCoef->setColumnCount(6);
    ui->tableCoef->setHorizontalHeaderLabels(
            QStringList() << "x[i-1]" << "x[i]" << "a[i]" << "b[i]" << "c[i]" << "d[i]");
    ui->tableCoef->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableData->setColumnCount(7);
    ui->tableData->setHorizontalHeaderLabels(
            QStringList() << "x[j]" << "F[j]" << "S[j]" << "F[j]-S[j]" << "F'[j]" << "S'[j]" << "F'[j]-S'[j]");
    ui->tableData->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_PushApproximate_clicked() {
    int n = ui->lineEditSplitNum->text().toInt();
    if (n > 1000) replotGraphs(2 * n);

    Solver Sol(n, currTask);
    Spline S = Sol.getSpline();
    QVector<double> x, s, ds, d2s, f, df, d2f;
    double xi = currTask.a;
    double step = (currTask.b - currTask.a) / (2 * n);
    double err = 0.0, err1 = 0.0, err2 = 0.0;
    double errX = 0.0, errX1 = 0.0, errX2 = 0.0;
    while (xi <= currTask.b) {
        x.push_back(xi);
        s.push_back(S(xi));
        ds.push_back(S.d(xi));
        d2s.push_back(S.d2(xi));
        f.push_back(currTask.f(xi));
        df.push_back(currTask.df(xi));
        d2f.push_back(currTask.d2f(xi));

        double tmp = std::abs(f.back() - s.back());
        if (tmp > err) {
            err = tmp;
            errX = xi;
        }
        tmp = std::abs(df.back() - ds.back());
        if (tmp > err1) {
            err1 = tmp;
            errX1 = xi;
        }
        tmp = std::abs(d2f.back() - d2s.back());
        if (tmp > err2) {
            err2 = tmp;
            errX2 = xi;
        }

        xi += step;
    }


    ui->graphF->graph(1)->setData(x, s);
    ui->graphF->graph(1)->rescaleAxes(true);
    ui->graphF->replot();

    ui->graphdF->graph(1)->setData(x, ds);
    ui->graphdF->graph(1)->rescaleAxes(true);
    ui->graphdF->replot();

    ui->graphddF->graph(1)->setData(x, d2s);
    ui->graphddF->graph(1)->rescaleAxes(true);
    ui->graphddF->replot();

    ui->tableCoef->setRowCount(n);
    for (int i = 0; i < n; i++) {
        ui->tableCoef->setItem(i, 0, new QTableWidgetItem(QString::number(S.grid[i])));
        ui->tableCoef->setItem(i, 1, new QTableWidgetItem(QString::number(S.grid[i + 1])));
        ui->tableCoef->setItem(i, 2, new QTableWidgetItem(QString::number(S.A[i])));
        ui->tableCoef->setItem(i, 3, new QTableWidgetItem(QString::number(S.B[i])));
        ui->tableCoef->setItem(i, 4, new QTableWidgetItem(QString::number(S.C[i])));
        ui->tableCoef->setItem(i, 5, new QTableWidgetItem(QString::number(S.D[i])));
    }
    ui->tableData->setRowCount(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        ui->tableData->setItem(i, 0, new QTableWidgetItem(QString::number(x[i])));
        ui->tableData->setItem(i, 1, new QTableWidgetItem(QString::number(f[i])));
        ui->tableData->setItem(i, 2, new QTableWidgetItem(QString::number(s[i])));
        ui->tableData->setItem(i, 3, new QTableWidgetItem(QString::number(f[i] - s[i])));
        ui->tableData->setItem(i, 4, new QTableWidgetItem(QString::number(df[i])));
        ui->tableData->setItem(i, 5, new QTableWidgetItem(QString::number(ds[i])));
        ui->tableData->setItem(i, 6, new QTableWidgetItem(QString::number(df[i] - ds[i])));
    }

    QString ref = "Сетка сплайна: n=" + QString::number(n)
                  + "\nКонтрольная сетка: N=" + QString::number(2 * n)
                  + "\nПогрешность сплайна на контрольной сетке:\nmax|Fj-Sj|=" + QString::number(err) + " при x=" +
                  QString::number(errX)
                  + "\nПогрешность производной на контрольной сетке:\nmax|F'j-S'j|=" + QString::number(err1) +
                  " при x=" + QString::number(errX1)
                  + "\nПогрешность второй производной на контрольной сетке:\nmax|F''j-S''j|=" + QString::number(err2) +
                  " при x=" + QString::number(errX2);
    ui->reference->setText(ref);

}


void MainWindow::on_FuncList_currentRowChanged(int currentRow) {
    switch (currentRow) {
        case 0:
            currTask = Problem(TestFunc, dTF, d2TF, -1.0, 1.0, 0.0, 0.0);
            break;
        case 1:
            currTask = Problem(MainFunc1, dF1, d2F1, 2.0, 4.0, 0.0, 0.0);
            break;
        case 2:
            currTask = Problem(MainFunc2, dF2, d2F2, 0.0, 1.0, 0.0, 0.0);
            break;
        case 3:
            currTask = Problem(MainFunc3, dF3, d2F3, 0.0, 2.0, 0.0, 0.0);
            break;
        case 4:
            currTask = Problem(MainFunc4, dF4, d2F4, 0.2, 2.0, 0.0, 0.0);
            break;
        default:
            break;
    }

    ui->lineA->setText(QString::number(currTask.a));
    ui->lineB->setText(QString::number(currTask.b));
    ui->lineSa->setText(QString::number(currTask.mu1));
    ui->lineSb->setText(QString::number(currTask.mu2));
    replotGraphs();
}

void MainWindow::replotGraphs(int n) {
    ui->graphF->graph(1)->data().data()->clear();
    ui->graphdF->graph(1)->data().data()->clear();
    ui->graphddF->graph(1)->data().data()->clear();
    QVector<double> x, f, df, d2f;
    double xi = currTask.a;
    double step = (currTask.b - currTask.a) / (n);

    while (xi <= currTask.b) {
        x.push_back(xi);
        f.push_back(currTask.f(xi));
        df.push_back(currTask.df(xi));
        d2f.push_back(currTask.d2f(xi));
        xi += step;
    }

    ui->graphF->graph(0)->setData(x, f);
    ui->graphF->graph(0)->rescaleAxes();
    ui->graphF->replot();

    ui->graphdF->graph(0)->setData(x, df);
    ui->graphdF->graph(0)->rescaleAxes();
    ui->graphdF->replot();

    ui->graphddF->graph(0)->setData(x, d2f);
    ui->graphddF->graph(0)->rescaleAxes();
    ui->graphddF->replot();
}

void MainWindow::on_lineA_textEdited(const QString &arg1) {
    currTask.a = arg1.toDouble();
    replotGraphs();
}


void MainWindow::on_lineB_textEdited(const QString &arg1) {
    currTask.b = arg1.toDouble();
    replotGraphs();
}


void MainWindow::on_lineSa_textEdited(const QString &arg1) {
    ui->graphF->graph(1)->data().data()->clear();
    ui->graphdF->graph(1)->data().data()->clear();
    ui->graphddF->graph(1)->data().data()->clear();
    currTask.mu1 = arg1.toDouble();
}


void MainWindow::on_lineSb_textEdited(const QString &arg1) {
    ui->graphF->graph(1)->data().data()->clear();
    ui->graphdF->graph(1)->data().data()->clear();
    ui->graphddF->graph(1)->data().data()->clear();
    currTask.mu2 = arg1.toDouble();
}

