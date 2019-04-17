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
    qDebug() << dir;
    QFile path(dir);
    if (!path.open(QIODevice::ReadWrite))
    {
        qWarning() << "file open failed: " << dir;
        return;
    }
    QDataStream out(&path);
    out << QString("HI");
    out << qint32(989);
    QDataStream in(&path);
    cood t;
    while(!path.atEnd())
    {
        QString x;
        qint32 y;
        in >> x >> y;
        qDebug() << x << "and" << y;
//        in >> t.x >> t.y;
//        insPath.addInspectionPoint(t);
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
