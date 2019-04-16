#include "pathplanner.h"
#include "ui_pathplanner.h"

pathPlanner::pathPlanner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pathPlanner)
{
    ui->setupUi(this);
    rarea = new RenderArea();
    ui->horizontalLayout->addWidget(rarea);
}

pathPlanner::~pathPlanner()
{
    delete rarea;
    delete ui;
}

void pathPlanner::on_pushButton_2_clicked()
{
    int index = ui->comboBox->currentIndex();
    QString dir = QString(":/paths/%1.txt").arg(index);
    QFile path(dir);
    if(!path.exists())
        qDebug() << "DOESN'T EXISTS";
//    if(!path.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        qDebug() << "Failed";
//        return;
//    }

    if (!path.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    while(!path.atEnd())
    {
        QString t = path.readLine();
        qDebug() << t;
    }
}

void pathPlanner::on_pushButton_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }
    updateName();
}

void pathPlanner::updateName()
{
    for(int t = 0; t < ui->listWidget->count(); t++)
    {
        QString name = QString("Point_%1").arg(t);
        ui->listWidget->item(t)->setText(name);

    }
   }
