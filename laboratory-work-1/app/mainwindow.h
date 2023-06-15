#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "TestWork.h"
#include "MainWork1.h"
#include "MainWork2.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonTestRun_clicked();

    void on_pushButtonMain1Run_clicked();

    void on_pushButtonMain2Run_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
