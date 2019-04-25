#include "pathplanner.h"
#include "ui_pathplanner.h"

pathPlanner::pathPlanner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pathPlanner)
{
    ui->setupUi(this);

    rarea = new RenderArea();
    ui->horizontalLayout->addWidget(rarea);

    connect(this, &pathPlanner::sendPlaneModel, rarea, &RenderArea::setAircraft);
    connect(rarea, &RenderArea::queryIndex, this, &pathPlanner::recieveIndexQuery);
    connect(this, &pathPlanner::send_index, rarea, &RenderArea::recieve_index);
    connect(rarea, &RenderArea::updateList, this, &pathPlanner::updateList);
    connect(this, &pathPlanner::removePoint, rarea, &RenderArea::removePoint);
    connect(rarea, &RenderArea::addPointQuery, this, &pathPlanner::recieveAddPointQuery);
    connect(this, &pathPlanner::addPoint, rarea, &RenderArea::addPoint);
}

pathPlanner::~pathPlanner()
{
    delete rarea;
    delete ui;
}

void pathPlanner::on_pushButton_2_clicked()
{
    int index = ui->comboBox->currentIndex();
    sendPlaneModel(index);
}

void pathPlanner::on_pushButton_clicked() // remove point
{
    if(rarea->getSplineSize() > 4)
    {
        int index = ui->listWidget->currentRow();
        //std::cout << "index is: " << index << std::endl;
        emit removePoint(index);
        //The spline library need at least 4 points or it will terminate the whole program
        delete ui->listWidget->takeItem(index);
        updateName();
    }
    else {
        QMessageBox::warning(
                    this,
                    tr("WARNING"),
                    tr("CANNOT REMOVE POINT WHEN THERE ARE LESS THAN FOUR!")
                    );
    }

}

void pathPlanner::updateName()
{
    for(int t = 0; t < ui->listWidget->count(); t++)
    {
        QString name = QString("Point_%1").arg(t);
        ui->listWidget->item(t)->setText(name);

    }
}

void pathPlanner::recieveIndexQuery()
{
    emit send_index(ui->listWidget->currentRow());
}

void pathPlanner::on_pushButton_3_clicked()
{
    ui->listWidget->addItem("anything");
    updateName();
}



void pathPlanner::updateList(qint32 size)
{
    ui->listWidget->clear();
    for(int i = 0; i != size; i++)
    {
        ui->listWidget->addItem("h");
    }
    updateName();
}

void pathPlanner::recieveAddPointQuery(QPointF pos)
{
    auto index = ui->listWidget->currentRow();
    std::cout << "index is: " << index << std::endl;
    ui->listWidget->addItem("anything");
    updateName();
    emit addPoint(pos, index);
}
