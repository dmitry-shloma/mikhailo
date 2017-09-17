#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QMessageBox>
#include <QProcess>
#include <QDir>
#include <QSettings>
#include <QTextCodec>

#include <exception>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::CustomizeWindowHint);
    setWindowFlags(Qt::FramelessWindowHint);

    ui->pbTheory->click();

    QSettings settings("d:/MyProjects/MikhailoFramework/MikhailoDefaultApp/Src/MikhailoDefaultApp.conf",
                       QSettings::IniFormat);
    QTextCodec *codec = QTextCodec::codecForName("CP1251");
    settings.setIniCodec(codec);

    ui->lbTitle->setText(settings.value("MikhailoDefaultApp/title").toString());
    ui->lbTheme->setText(tr("Реле времени"));
    ui->lbTarget->setText(ui->lbTarget->text().arg(tr("изучить реле времени...")));

    ui->pbAdmin->setVisible(settings.value("MikhailoDefaultApp/pbAdminVisible", true).toBool());
    ui->pbCalc->setVisible(settings.value("MikhailoDefaultApp/pbCalcVisible", true).toBool());
    ui->pbAbout->setVisible(settings.value("MikhailoDefaultApp/pbAboutVisible", true).toBool());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbClose_clicked()
{
    close();
}

void MainWindow::on_pbMinimize_clicked()
{
    setWindowState(Qt::WindowMinimized);
}

void MainWindow::on_pbTheory_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pbDescLabStand_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pbSequenceSteps_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pbProcessResult_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pbControlQuestions_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pbBibliography_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_pbCalc_clicked()
{
    try {
        startCalculator();
    } catch (std::exception &e) {
        QMessageBox::warning(this, tr("ва"), QString::fromAscii(e.what()));
    }
}

void MainWindow::startCalculator()
{
    QProcess *process = new QProcess(this);
#ifdef __linux__
    QString calc = "kcalc";
#elif _WIN32
    QString calc = "C:\\Windows\\System32\\calc.exe";
#else
    throw "В разработке...";
#endif
    process->start(calc);
}

void MainWindow::setCenterScreen(QWidget widget)
{
    QDesktopWidget *desktop = QApplication::desktop();
    int x = (desktop->width() - width()) / 2;
    int y = (desktop->height() - height()) / 2;
    widget.move(x, y);
}
