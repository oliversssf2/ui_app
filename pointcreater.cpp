#include "pointcreater.h"
#include "ui_pointcreater.h"

pointCreater::pointCreater(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pointCreater)
{
    ui->setupUi(this);
}

pointCreater::~pointCreater()
{
    delete ui;
}

void pointCreater::reject()
{
    ui->spinBox->setValue(0);
    ui->spinBox_2->setValue(0);
    ui->spinBox_3->setValue(0);
    currentIndex = -1;
    this->hide();
}

void pointCreater::on_buttonBox_accepted()
{
    emit addPoint(QPointF(ui->spinBox->value(), ui->spinBox_2->value()), ui->spinBox_3->value());
}
