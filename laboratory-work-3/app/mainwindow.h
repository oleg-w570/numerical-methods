#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "functions.h"
#include "solver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

    void on_PushApproximate_clicked();

    void on_FuncList_currentRowChanged(int currentRow);

    void on_lineA_textEdited(const QString &arg1);

    void on_lineB_textEdited(const QString &arg1);

    void on_lineSa_textEdited(const QString &arg1);

    void on_lineSb_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Problem currTask;

    void replotGraphs(int n = 2000);
};

#endif // MAINWINDOW_H
