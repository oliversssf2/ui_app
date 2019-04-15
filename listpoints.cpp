#include "listpoints.h"
#include "ui_listpoints.h"

listpoints::listpoints(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::listpoints)
{
    ui->setupUi(this);
}

listpoints::~listpoints()
{
    delete ui;
}
