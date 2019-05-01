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
    ui->xspinBox->setValue(0);
    ui->yspinBox->setValue(0);
    ui->rotspinBox->setValue(0);
    currentIndex = -1;
    mode = -1;
    emit stopPreview();
    this->hide();
}

void pointCreater::on_buttonBox_accepted()
{
    if(mode == 0)
        emit addPoint(QPointF(ui->xspinBox->value(), ui->yspinBox->value()), ui->rotspinBox->value());
    else if(mode == 1)
    {
        emit stopPreview();
        emit updatePoint(QPointF(ui->xspinBox->value(), ui->yspinBox->value()), currentIndex, ui->rotspinBox->value());
        mode = -1;
        currentIndex = -1;
        hide();
    }
}

void pointCreater::on_buttonBox_rejected()
{
    ui->xspinBox->setValue(0);
    ui->yspinBox->setValue(0);
    ui->rotspinBox->setValue(0);
    emit stopPreview();
    currentIndex = -1;
    mode = -1;
    this->hide();
}

void pointCreater::on_xspinBox_valueChanged(int arg1)
{
    emit previewBox(QPointF(ui->xspinBox->value(), ui->yspinBox->value()), ui->rotspinBox->value());
}

void pointCreater::on_yspinBox_valueChanged(int arg1)
{
    emit previewBox(QPointF(ui->xspinBox->value(), ui->yspinBox->value()), ui->rotspinBox->value());
}

void pointCreater::on_rotspinBox_valueChanged(int arg1)
{
    emit previewBox(QPointF(ui->xspinBox->value(), ui->yspinBox->value()), ui->rotspinBox->value());
}

void pointCreater::modifyQuery(int pointIndex)
{
    emit pointQuery(pointIndex);
    currentIndex = pointIndex;
    setMode(1);
}

void pointCreater::loadPoint(QPointF pos, int rotation)
{
    ui->xspinBox->setValue(pos.x());
    ui->yspinBox->setValue(pos.y());
    ui->rotspinBox->setValue(rotation);
    emit previewBox(QPointF(ui->xspinBox->value(), ui->yspinBox->value()), ui->rotspinBox->value());
}

void pointCreater::setMode(int i)
{
    mode = i;
    if(mode == 0)
    {
        setWindowTitle("New Point");
        ui->currentPointIndex->setText("new point");
    }
    else if(mode == 1)
    {
        setWindowTitle("Modifying Point");
        ui->currentPointIndex->setNum(currentIndex);
    }
}




