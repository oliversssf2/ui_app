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
    emit stopPreview();
    this->hide();
}

void pointCreater::on_buttonBox_accepted()
{
    emit addPoint(QPointF(ui->spinBox->value(), ui->spinBox_2->value()), ui->spinBox_3->value());
}

void pointCreater::on_spinBox_3_valueChanged(int arg1)
{
    emit previewBox(QPointF(ui->spinBox->value(), ui->spinBox_2->value()), ui->spinBox_3->value());
}

void pointCreater::on_spinBox_2_valueChanged(int arg1)
{
    emit previewBox(QPointF(ui->spinBox->value(), ui->spinBox_2->value()), ui->spinBox_3->value());
}

void pointCreater::on_spinBox_valueChanged(int arg1)
{
    emit previewBox(QPointF(ui->spinBox->value(), ui->spinBox_2->value()), ui->spinBox_3->value());
}
