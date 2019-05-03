#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    auto *wdg = new pathPlanner();
    wdg->show();
}

void MainWindow::on_pushButton_clicked()
{
    if(!QProcess::startDetached("/bin/sh", QStringList{QString(SCRIPTSDIR) + "/arduino.sh"}))
        qDebug() << "failed to RUN!!!!";
}
