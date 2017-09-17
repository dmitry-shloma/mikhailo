#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbClose_clicked();
    void on_pbMinimize_clicked();
    void on_pbTheory_clicked();
    void on_pbDescLabStand_clicked();
    void on_pbSequenceSteps_clicked();
    void on_pbProcessResult_clicked();
    void on_pbControlQuestions_clicked();
    void on_pbBibliography_clicked();
    void on_pbCalc_clicked();

private:
    void setCenterScreen(QWidget widget);
    void startCalculator();

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
