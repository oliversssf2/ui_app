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
    QDir dir = QString(PATHSDIR);
    qDebug() << dir;
    QString path = dir.absoluteFilePath("%1.txt").arg(index);
    qDebug() << path;
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
    {
        qWarning() << file.error() << file.errorString();
        return;
    }
    QDataStream out(&file);

    write_coord(out, 12, 23, flags::next_line);
    write_coord(out, 25, 435, flags::next_line);
    write_coord(out, 734, 213, flags::next_line);
    write_coord(out, 324, 234, flags::eof);

    file.close();

    if(!file.open(QIODevice::ReadOnly))
    {
        qWarning() << file.error() << file.errorString();
        return;
    }

    QDataStream in(&file);

    inspectionPath k;
    read_coord(in, k);

    file.close();
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
