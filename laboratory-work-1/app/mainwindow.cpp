#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidgetTest->setHorizontalHeaderLabels(QStringList() << "Xi" << "Vi" << "V2i" << "Vi - V2i" << "ОЛП" << "Hi" << "C1" << "C2" << "Ui" << "|Ui - Vi|");
    ui->tableWidgetTest->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidgetMain1->setHorizontalHeaderLabels(QStringList() << "Xi" << "Vi" << "V2i" << "Vi - V2i" << "ОЛП" << "Hi" << "C1" << "C2");
    ui->tableWidgetMain1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidgetMain2->setHorizontalHeaderLabels(QStringList() << "Xi" << "V1i" << "V1_2i" << "V1i - V1_2i" << "V2i" << "V2_2i" << "V2i - V2_2i" << "ОЛП" << "Hi" << "C1" << "C2");
    ui->tableWidgetMain2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->graphMain2Faz->xAxis->setLabel("u1");
    ui->graphMain2Faz->yAxis->setLabel("u2");
    ui->graphMain2U1->xAxis->setLabel("x");
    ui->graphMain2U1->yAxis->setLabel("u1");
    ui->graphMain2U2->xAxis->setLabel("x");
    ui->graphMain2U2->yAxis->setLabel("u2");
    ui->graphMain1->xAxis->setLabel("x");
    ui->graphMain1->yAxis->setLabel("u");
    ui->graphTestTrue->xAxis->setLabel("Истинная траектория");
    ui->graphTestNum->xAxis->setLabel("Численная траектория");


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonTestRun_clicked()
{
    double u0 = ui->lineEditTestU0->text().toDouble();
    double b = ui->lineEditTestB->text().toDouble();
    int N = ui->lineEditTestN->text().toInt();
    double h0 = ui->lineEditTestH0->text().toDouble();
    double eps = ui->lineEditTestLP->text().toDouble();
    bool ctrlLP = ui->radioButtonTestCLP->isChecked();

    TestWork T(b, u0, h0, N, ctrlLP, eps);
    T.Run();
    QVector<double> x = QVector<double>(T.grid.begin(), T.grid.end());
    QVector<double> y_num = QVector<double>(T.final_num_values.begin(), T.final_num_values.end());
    QVector<double> y_true = QVector<double>(T.true_values.begin(), T.true_values.end());

    ui->graphTestNum->addGraph();
    ui->graphTestNum->graph(0)->setData(x, y_num);
    ui->graphTestNum->graph(0)->rescaleAxes();
    ui->graphTestNum->replot();

    ui->graphTestTrue->addGraph();
    ui->graphTestTrue->graph(0)->setData(x, y_true);
    ui->graphTestTrue->rescaleAxes();
    ui->graphTestTrue->replot();

    T.grid_step.pop_back();
    T.grid_step.insert(T.grid_step.begin(), h0);
    ui->tableWidgetTest->clearContents();
    ui->tableWidgetTest->setRowCount(0);

    double maxOLP = 0, maxTrueDiff = 0;
    int indMaxStep = 0, indMinStep = 0, indMaxTrueDiff = 0;
    for (int i = 0; i < T.grid.size(); i++)
    {
        QTableWidgetItem *x = new QTableWidgetItem(QString::number(T.grid[i]));
        QTableWidgetItem *v = new QTableWidgetItem(QString::number(T.num_values[i]));
        QTableWidgetItem *v2 = new QTableWidgetItem(QString::number(T.d_num_values[i]));
        QTableWidgetItem *diff = new QTableWidgetItem(QString::number(T.num_values[i] - T.d_num_values[i]));
        double tmp1 = std::abs(T.d_num_values[i] - T.num_values[i]) / 15 * 16;
        if (tmp1 > maxOLP)
            maxOLP = tmp1;
        QTableWidgetItem *OLP = new QTableWidgetItem(QString::number(tmp1));
        double tmp2 = T.grid_step[i];
        if (T.grid_step[indMaxStep] < tmp2)
            indMaxStep = i;
        if (T.grid_step[indMinStep] > tmp2)
            indMinStep = i;
        QTableWidgetItem *h = new QTableWidgetItem(QString::number(tmp2));
        int tmp4 = i > 0 ? T.div2[i] - T.div2[i-1] : 0;
        int tmp5 = i > 0 ? T.mult2[i] - T.mult2[i-1] : 0;
        QTableWidgetItem *c1 = new QTableWidgetItem(QString::number(tmp4));
        QTableWidgetItem *c2 = new QTableWidgetItem(QString::number(tmp5));
        QTableWidgetItem *u = new QTableWidgetItem(QString::number(T.true_values[i]));
        double tmp3 = std::abs(T.true_values[i] - T.final_num_values[i]);
        if (tmp3 > maxTrueDiff)
        {
            maxTrueDiff = tmp3;
            indMaxTrueDiff = i;
        }
        QTableWidgetItem *true_diff = new QTableWidgetItem(QString::number(tmp3));
        ui->tableWidgetTest->insertRow(i);
        ui->tableWidgetTest->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i)));
        ui->tableWidgetTest->setItem(i, 0, x);
        ui->tableWidgetTest->setItem(i, 1, v);
        ui->tableWidgetTest->setItem(i, 2, v2);
        ui->tableWidgetTest->setItem(i, 3, diff);
        ui->tableWidgetTest->setItem(i, 4, OLP);
        ui->tableWidgetTest->setItem(i, 5, h);
        ui->tableWidgetTest->setItem(i, 6, c1);
        ui->tableWidgetTest->setItem(i, 7, c2);
        ui->tableWidgetTest->setItem(i, 8, u);
        ui->tableWidgetTest->setItem(i, 9, true_diff);
    }

    QString ref = "Число шагов метода: "  + QString::number(T.grid.size()-1) + "\nb - xN = " +  QString::number(T.right_border - T.grid.back())
            + "\nmax|ОЛП| = " + QString::number(maxOLP) + "\nОбщее число удвоений шага: " + QString::number(T.mult) + "\nОбщее число делений шага: "
            + QString::number(T.div) + "\nmax{Hi} = " + QString::number(T.grid_step[indMaxStep]) + " при x = " + QString::number(T.grid[indMaxStep])
            + "\nmin{Hi} = " + QString::number(T.grid_step[indMinStep]) + " при x = " + QString::number(T.grid[indMinStep])
            + "\nmax|Ui - Vi| = " + QString::number(maxTrueDiff) + " при x = " + QString::number(T.grid[indMaxTrueDiff]);
    ui->textBrowserTest->setText(ref);
}


void MainWindow::on_pushButtonMain1Run_clicked()
{
    double u0 = ui->lineEditMain1U0->text().toDouble();
    double b = ui->lineEditMain1B->text().toDouble();
    double h0 = ui->lineEditMain1H0->text().toDouble();
    int N = ui->lineEditMain1N->text().toInt();
    double eps = ui->lineEditMain1EPS->text().toDouble();
    bool ctl = ui->radioButtonMain1CLP->isChecked();

    MainWork1 M(b, u0, h0, N, ctl, eps);
    M.Run();
    QVector<double> x(M.grid.begin(), M.grid.end());
    QVector<double> y(M.final_num_values.begin(), M.final_num_values.end());

    ui->graphMain1->addGraph();
    ui->graphMain1->graph(0)->setData(x, y);
    ui->graphMain1->graph(0)->rescaleAxes();
    ui->graphMain1->replot();

    M.grid_step.pop_back();
    M.grid_step.insert(M.grid_step.begin(), h0);
    ui->tableWidgetMain1->clearContents();
    ui->tableWidgetMain1->setRowCount(0);

    double maxOLP = 0;
    int indMaxStep = 0, indMinStep = 0;
    for (int i = 0; i < M.grid.size(); i++)
    {
        QTableWidgetItem *x = new QTableWidgetItem(QString::number(M.grid[i]));
        QTableWidgetItem *v = new QTableWidgetItem(QString::number(M.num_values[i]));
        QTableWidgetItem *v2 = new QTableWidgetItem(QString::number(M.d_num_values[i]));
        QTableWidgetItem *diff = new QTableWidgetItem(QString::number(M.num_values[i] - M.d_num_values[i]));
        double tmp1 = std::abs(M.d_num_values[i] - M.num_values[i]) / 15 * 16;
        if (tmp1 > maxOLP)
            maxOLP = tmp1;
        QTableWidgetItem *OLP = new QTableWidgetItem(QString::number(tmp1));
        double tmp2 = M.grid_step[i];
        if (M.grid_step[indMaxStep] < tmp2)
            indMaxStep = i;
        if (M.grid_step[indMinStep] > tmp2)
            indMinStep = i;
        QTableWidgetItem *h = new QTableWidgetItem(QString::number(M.grid_step[i]));
        int tmp4 = i > 0 ? M.div2[i] - M.div2[i-1] : 0;
        int tmp5 = i > 1 ? M.mult2[i-1] - M.mult2[i-2] : 0;
        QTableWidgetItem *c1 = new QTableWidgetItem(QString::number(tmp4));
        QTableWidgetItem *c2 = new QTableWidgetItem(QString::number(tmp5));
        ui->tableWidgetMain1->insertRow(i);
        ui->tableWidgetMain1->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i)));
        ui->tableWidgetMain1->setItem(i, 0, x);
        ui->tableWidgetMain1->setItem(i, 1, v);
        ui->tableWidgetMain1->setItem(i, 2, v2);
        ui->tableWidgetMain1->setItem(i, 3, diff);
        ui->tableWidgetMain1->setItem(i, 4, OLP);
        ui->tableWidgetMain1->setItem(i, 5, h);
        ui->tableWidgetMain1->setItem(i, 6, c1);
        ui->tableWidgetMain1->setItem(i, 7, c2);
    }

    QString ref = "Число шагов метода: "  + QString::number(M.grid.size()-1) + "\nb - xN = " +  QString::number(M.right_border - M.grid.back())
            + "\nmax|ОЛП| = " + QString::number(maxOLP) + "\nОбщее число удвоений шага: " + QString::number(M.mult) + "\nОбщее число делений шага: "
            + QString::number(M.div) + "\nmax{Hi} = " + QString::number(M.grid_step[indMaxStep]) + " при x = " + QString::number(M.grid[indMaxStep])
            + "\nmin{Hi} = " + QString::number(M.grid_step[indMinStep]) + " при x = " + QString::number(M.grid[indMinStep]);
    ui->textBrowserMain1->setText(ref);
    qDebug() << M.grid.back() << "   " << M.grid_step.back();
}


void MainWindow::on_pushButtonMain2Run_clicked()
{
    double alpha = ui->lineEditMain2Alpha->text().toDouble();
    double beta = ui->lineEditMain2Beta->text().toDouble();
    double u1 = ui->lineEditMain2U1->text().toDouble();
    double u2 = ui->lineEditMain2U2->text().toDouble();
    double b = ui->lineEditMain2B->text().toDouble();
    double h0 = ui->lineEditMain2H0->text().toDouble();
    int N = ui->lineEditMain2N->text().toInt();
    double eps = ui->lineEditMain2LP->text().toDouble();
    bool ctl = ui->radioButtonMain2CLP->isChecked();

    MainWork2 M(alpha, beta, b, u1, u2, h0, N, ctl, eps);
    M.Run();
    QVector<double> x(M.grid.begin(), M.grid.end());
    QVector<double> y1(M.final_num_values_1.begin(), M.final_num_values_1.end());
    QVector<double> y2(M.final_num_values_2.begin(), M.final_num_values_2.end());
    //qDebug() << "u1:\n" << y1 << "\nu2:\n" << y2;
    int j = 0;
    QVector<int> delim;
    delim.push_back(1);
    bool up = std::abs(y1[0]) < std::abs(y1[1]);
    while(j < y1.size()-1)
    {
        if ((y1[j] < y1[j+1] && !up)||(y1[j] > y1[j+1] && up))
        {
            delim.push_back(j+1);
            up = !up;
        }
        j++;
    }
    delim.push_back(j+1);
    //qDebug() << "\nDelim: " << delim << "\n";
    QVector<QVector<double>> y1_parts(delim.size()-1);
    QVector<QVector<double>> y2_parts(delim.size()-1);
    for (int i = 0; i < y1_parts.size(); i++)
    {
        y1_parts[i] = QVector<double>(y1.begin()+delim[i]-1, y1.begin()+delim[i+1]);
        y2_parts[i] = QVector<double>(y2.begin()+delim[i]-1, y2.begin()+delim[i+1]);
        //qDebug() << "\nparts " << i << ":\n" << y1_parts[i];
    }
    for (int i = 0; i < y1_parts.size(); i++)
    {
        ui->graphMain2Faz->addGraph();
        ui->graphMain2Faz->graph(i)->setData(y1_parts[i], y2_parts[i]);
        if (i > 0)
            ui->graphMain2Faz->graph(i)->rescaleAxes(true);
        else
            ui->graphMain2Faz->graph(i)->rescaleAxes();
    }
    ui->graphMain2Faz->replot();

    ui->graphMain2U1->addGraph();
    ui->graphMain2U1->graph(0)->setData(x, y1, true);
    ui->graphMain2U1->graph(0)->rescaleAxes();
    ui->graphMain2U1->replot();

    ui->graphMain2U2->addGraph();
    ui->graphMain2U2->graph(0)->setData(x, y2, true);
    ui->graphMain2U2->graph(0)->rescaleAxes();
    ui->graphMain2U2->replot();

    M.grid_step.pop_back();
    M.grid_step.insert(M.grid_step.begin(), h0);

    ui->tableWidgetMain2->clearContents();
    ui->tableWidgetMain2->setRowCount(0);

    double maxOLP = 0;
    int indMaxStep = 0, indMinStep = 0;
    for (int i = 0; i < M.grid.size(); i++)
    {
        QTableWidgetItem *x = new QTableWidgetItem(QString::number(M.grid[i]));
        QTableWidgetItem *v1 = new QTableWidgetItem(QString::number(M.num_values_1[i]));
        QTableWidgetItem *v1_2 = new QTableWidgetItem(QString::number(M.d_num_values_1[i]));
        QTableWidgetItem *diff1 = new QTableWidgetItem(QString::number(M.num_values_1[i] - M.d_num_values_1[i]));
        QTableWidgetItem *v2 = new QTableWidgetItem(QString::number(M.num_values_2[i]));
        QTableWidgetItem *v2_2 = new QTableWidgetItem(QString::number(M.d_num_values_2[i]));
        QTableWidgetItem *diff2 = new QTableWidgetItem(QString::number(M.num_values_2[i] - M.d_num_values_2[i]));
        double olp1 = std::abs(M.d_num_values_1[i] - M.num_values_1[i]) / 15 * 16;
        double olp2 = std::abs(M.d_num_values_2[i] - M.num_values_2[i]) / 15 * 16;
        double tmp1 = std::max(olp1, olp2);
        if (tmp1 > maxOLP)
            maxOLP = tmp1;
        QTableWidgetItem *OLP = new QTableWidgetItem(QString::number(tmp1));
        double tmp2 = M.grid_step[i];
        if (M.grid_step[indMaxStep] < tmp2)
            indMaxStep = i;
        if (M.grid_step[indMinStep] > tmp2)
            indMinStep = i;
        QTableWidgetItem *h = new QTableWidgetItem(QString::number(M.grid_step[i]));
        int tmp4 = i > 0 ? M.div2[i] - M.div2[i-1] : 0;
        int tmp5 = i > 1 ? M.mult2[i-1] - M.mult2[i-2] : 0;
        QTableWidgetItem *c1 = new QTableWidgetItem(QString::number(tmp4));
        QTableWidgetItem *c2 = new QTableWidgetItem(QString::number(tmp5));
        ui->tableWidgetMain2->insertRow(i);
        ui->tableWidgetMain2->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i)));
        ui->tableWidgetMain2->setItem(i, 0, x);
        ui->tableWidgetMain2->setItem(i, 1, v1);
        ui->tableWidgetMain2->setItem(i, 2, v1_2);
        ui->tableWidgetMain2->setItem(i, 3, diff1);
        ui->tableWidgetMain2->setItem(i, 4, v2);
        ui->tableWidgetMain2->setItem(i, 5, v2_2);
        ui->tableWidgetMain2->setItem(i, 6, diff2);
        ui->tableWidgetMain2->setItem(i, 7, OLP);
        ui->tableWidgetMain2->setItem(i, 8, h);
        ui->tableWidgetMain2->setItem(i, 9, c1);
        ui->tableWidgetMain2->setItem(i, 10, c2);
    }

    QString ref = "Число шагов метода: "  + QString::number(M.grid.size()-1) + "\nb - xN = " +  QString::number(M.right_border - M.grid.back())
            + "\nmax|ОЛП| = " + QString::number(maxOLP) + "\nОбщее число удвоений шага: " + QString::number(M.mult) + "\nОбщее число делений шага: "
            + QString::number(M.div) + "\nmax{Hi} = " + QString::number(M.grid_step[indMaxStep]) + " при x = " + QString::number(M.grid[indMaxStep])
            + "\nmin{Hi} = " + QString::number(M.grid_step[indMinStep]) + " при x = " + QString::number(M.grid[indMinStep]);
    ui->textBrowserMain2->setText(ref);
}

