#include "pathplanner.h"
#include "ui_pathplanner.h"

pathPlanner::pathPlanner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pathPlanner)
{
    ui->setupUi(this);

    rarea = new RenderArea();
    ui->horizontalLayout->addWidget(rarea);

    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection); // enable multiple selection, returns the smallest index if only 1 index is needed

    pointcreater = new pointCreater();
    //pointcreater->exec();

    connect(this, &pathPlanner::sendPlaneModel, rarea, &RenderArea::setAircraft);
    connect(rarea, &RenderArea::queryIndex, this, &pathPlanner::recieveIndexQuery);
    connect(this, &pathPlanner::send_index, rarea, &RenderArea::recieve_index);
    connect(rarea, &RenderArea::updateList, this, &pathPlanner::updateList);
    connect(this, &pathPlanner::removePoint, rarea, &RenderArea::removePoint);
    connect(rarea, &RenderArea::addPointQuery, this, &pathPlanner::recieveAddPointQuery);
    connect(this, &pathPlanner::addPoint, rarea, &RenderArea::addPointWithRotation);
    connect(this, &pathPlanner::loadPath, rarea, &RenderArea::loadPath);
    connect(this, & pathPlanner::savePath, rarea, &RenderArea::savePath);
    connect(rarea, &RenderArea::updateName, this, &pathPlanner::updateName);
    connect(this, &pathPlanner::flip, rarea, &RenderArea::flip);
    connect(this, &pathPlanner::setSaftyDist, rarea, &RenderArea::setSaftyDist);
    connect(this, &pathPlanner::selectCurrentRow, rarea, &RenderArea::selectCurrentRow);
    connect(pointcreater, &pointCreater::addPoint, this, &pathPlanner::recieveAddPointQueryWithRotation);
    connect(pointcreater, &pointCreater::previewBox, rarea, &RenderArea::previewBox);
    connect(pointcreater, &pointCreater::stopPreview, rarea, &RenderArea::stopPreview);
    connect(rarea, &RenderArea::addPointQueryWithRotation, this, &pathPlanner::recieveAddPointQueryWithRotation);
    connect(this, &pathPlanner::modifyquery, pointcreater, &pointCreater::modifyQuery);
    connect(pointcreater, &pointCreater::updatePoint, rarea, &RenderArea::modifyPoint);

    connect(pointcreater, &pointCreater::pointQuery, rarea, &RenderArea::queryPoint);
    connect(rarea, &RenderArea::loadPoint, pointcreater, &pointCreater::loadPoint);
    connect(this, &pathPlanner::setMode, pointcreater, &pointCreater::setMode);
    connect(this, &pathPlanner::saveCenter, rarea, &RenderArea::saveCenter);

    //connect(pointcreater, &pointCreater::modifyPoint, rarea, &RenderArea::modifyPoint);

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
    if(ui->listWidget->count()>0)
    {
        int index = ui->listWidget->currentRow();
        if(index >= 0)
        {
            std::cout << index << std::endl;
            //std::cout << "index is: " << index << std::endl;
            emit removePoint(index);
            //The spline library need at least 4 points or it will terminate the whole program
            delete ui->listWidget->takeItem(index);
            updateName();
        }
        else {
            QMessageBox::warning(this, "WARNING!!!", "SELECT BEFORE REMOVING A POINT");
        }
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
    emit loadPath();
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

void pathPlanner::recieveAddPointQueryWithRotation(QPointF pos, int rotation, bool pushBackAnyway)
{

    int index = ui->listWidget->currentRow();
    if(pushBackAnyway) index = -1;
    if(index >= 0)
        std::cout << "index is: " << index << std::endl;
    ui->listWidget->addItem("anything");
    updateName();
    emit addPoint(pos, index, rotation);
}

void pathPlanner::recieveAddPointQuery(QPointF pos, bool pushBackAnyway)
{
    recieveAddPointQueryWithRotation(pos, 0, pushBackAnyway);
}

void pathPlanner::on_pushButton_4_clicked()
{
    emit savePath();
}


void pathPlanner::on_flipButton_clicked()
{
    emit flip();
}

void pathPlanner::on_setSaftyDist_clicked()
{
    if(ui->listWidget->currentRow() != -1) // something is selected
    {
        pointcreater->show();
        emit modifyquery(ui->listWidget->currentRow());
    }
}

void pathPlanner::on_listWidget_currentRowChanged(int currentRow)
{
    emit selectCurrentRow(currentRow);
}

void pathPlanner::on_addPointButton_clicked()
{
    pointcreater->show();
    emit setMode(0);
}

void pathPlanner::on_pushButton_5_clicked()
{
    emit saveCenter(ui->comboBox->currentIndex());
}
