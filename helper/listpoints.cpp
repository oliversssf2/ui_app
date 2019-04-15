#include "listpoints.h"
#include "ui_listpoints.h"

listPoints::listPoints(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::listPoints)
{
    ui->setupUi(this);
}

listPoints::~listPoints()
{
    delete ui;
}
