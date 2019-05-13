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
    if(!QProcess::startDetached("/bin/bash", QStringList{QString(SCRIPTSDIR) + "/rviz.sh"}))
        qDebug() << "failed to RUN!!!!";
}

void MainWindow::on_pushButton_3_clicked()
{
  if(!QProcess::startDetached("/bin/bash", QStringList{QString(SCRIPTSDIR) + "/dynamixel.sh"}))
      qDebug() << "failed to RUN!!!!";
}

void MainWindow::on_runRealsense_clicked()
{
  if(!QProcess::startDetached("/bin/bash", QStringList{QString(SCRIPTSDIR) + "/realsense.sh"}))
      qDebug() << "failed to RUN!!!!";
}

void MainWindow::on_pushButton_4_clicked()
{
    if(!QProcess::startDetached("/bin/bash", QStringList{QString(SCRIPTSDIR) + "/car.sh"}))
        qDebug() << "failed to RUN!!!!";
}
