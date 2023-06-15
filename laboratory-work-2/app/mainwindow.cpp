#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->chartview1->setChart(new QChart);
    ui->chartview1->chart()->legend()->setAlignment(Qt::AlignBottom);
    ui->chartview2->setChart(new QChart);
    ui->chartview2->chart()->legend()->setAlignment(Qt::AlignBottom);
    ui->chartview1->setRubberBand(QChartView::RectangleRubberBand);
    ui->chartview2->setRubberBand(QChartView::RectangleRubberBand);
    ui->chartview1->chart()->setTitle("График решений");
    ui->chartview2->chart()->setTitle("График погрешности");

//    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonRun_clicked()
{
    ui->chartview1->chart()->removeAllSeries();
    ui->chartview2->chart()->removeAllSeries();

    unsigned long long N = ui->lineEditN->text().toULongLong();
    MODE mode = ui->radioButtonTest->isChecked() ? TEST : MAIN;
//    unsigned long long lower_bound = mode == TEST ? 200 : 500;
//    N = std::max(N, lower_bound);
    S.calculate(N, mode);

    std::vector<double>& num_sol = S.getNumSolution();
    std::vector<double>& sec_sol = S.getSecondSolution();
    std::vector<double>& diff = S.getDifference();
    auto eps = std::max_element(diff.begin(), diff.end());
    auto eps_pos = static_cast<double>(eps - diff.begin()) / static_cast<double>(N);
//    qDebug() << diff << "\n" << num_sol << "\n" << sec_sol << "\n";

    QLineSeries *num_solution = new QLineSeries;
    num_solution->setName("ν(x)");
    QLineSeries *second_solution = new QLineSeries;
    QString sec_name = mode == TEST ? "u(x)" : "ν₂(x)";
    second_solution->setName(sec_name);
    QLineSeries *difference = new QLineSeries;
    difference->setName("|ν(x)-"+sec_name+"|");



    ui->table->setRowCount(N+1);
    ui->table->setColumnCount(4);
    ui->table->setHorizontalHeaderLabels(QStringList() << "x" << "ν(x)" << sec_name << "|ν(x)-"+sec_name+"|");

    double x = 0.0;
    for (unsigned long long i = 0; i < num_sol.size(); i++)
    {
//        if (std::abs(0.29 - x) < 1e-8) qDebug() << Qt::fixed << qSetRealNumberPrecision(16) << num_sol[i];
        num_solution->append(x, num_sol[i]);
        second_solution->append(x, sec_sol[i]);
        difference->append(x, diff[i]);
        ui->table->setItem(i, 0, new QTableWidgetItem(QString::number(x)));
        ui->table->setItem(i, 1, new QTableWidgetItem(QString::number(num_sol[i])));
        ui->table->setItem(i, 2, new QTableWidgetItem(QString::number(sec_sol[i])));
        ui->table->setItem(i, 3, new QTableWidgetItem(QString::number(diff[i])));
        x += 1.0/N;
    }

    ui->chartview1->chart()->addSeries(num_solution);
    ui->chartview1->chart()->addSeries(second_solution);
    ui->chartview1->chart()->createDefaultAxes();
    ui->chartview2->chart()->addSeries(difference);
    ui->chartview2->chart()->createDefaultAxes();

    QString ref = "Для решения задачи использована равномерная сетка с числом разбиений n = " + QString::number(N)
        + ".\nЗадача должна быть решена с погрешностью не более Ɛ = 0.5e-6.\nЗадача решена с погрешностью ";
    ref += mode == TEST ? "Ɛ₁ =  " : "Ɛ₂ =  ";
    ref += QString::number(*eps) + ".\n";
    ref += mode == TEST ? "Максимальное отклонение аналитического и численного решения наблюдается в точке x = " + QString::number(eps_pos) + "."
        : "Максимальное разность численных решений в общих узлах сетки наблюдается в точке x = " + QString::number(eps_pos) + ".";
    ui->reference->setText(ref);
}

