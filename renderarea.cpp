#include "renderarea.h"
#include "ui_renderarea.h"

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderArea),
    plane(QImage()),
    mySpline({})
{
    ui->setupUi(this);
    ui->doubleSpinBox->setValue(25.0);
    this->setFixedSize(800, 800);
    this->resize(this->width(), this->width()); //keep the plane image a square
}

RenderArea::~RenderArea()
{
    delete ui;
}

void RenderArea::resizeEvent(QResizeEvent* event)
{
    this->resize(this->width(), this->width());
}


void RenderArea::paintEvent(QPaintEvent *event)
{
    QRectF target(0, 0, this->width(), this->height());
    QRectF source(0, 0, plane.width(), plane.height());

    QPainter painter(this);

    //Pen for drawing path...
    QPen penForPath;
    penForPath.setStyle(Qt::DashLine);
    penForPath.setColor(QColor(0, 204, 102));
    penForPath.setCapStyle(Qt::RoundCap);
    penForPath.setJoinStyle(Qt::RoundJoin);
    penForPath.setWidth(1);//6

    QPen penForRobot;
    penForRobot.setStyle(Qt::SolidLine);
    penForRobot.setColor(QColor(51, 153, 255));
    penForRobot.setCapStyle(Qt::RoundCap);
    penForRobot.setJoinStyle(Qt::RoundJoin);
    penForRobot.setWidth(1);//4

    QPen penForPreview;
    penForPreview.setStyle(Qt::SolidLine);
    penForPreview.setColor(QColor(95, 75, 139));
    penForPreview.setCapStyle(Qt::RoundCap);
    penForPreview.setJoinStyle(Qt::RoundJoin);
    penForPreview.setWidth(1);//4

    QPen penForEllipse;
    penForEllipse.setStyle(Qt::SolidLine);
    penForEllipse.setColor(QColor(255, 153, 51));
    penForEllipse.setCapStyle(Qt::RoundCap);
    penForEllipse.setJoinStyle(Qt::RoundJoin);
    penForEllipse.setWidth(1);//2

    QPen penForSelection;
    penForSelection.setStyle(Qt::SolidLine);
    penForSelection.setColor(QColor(255, 0, 0));
    penForSelection.setCapStyle(Qt::RoundCap);
    penForSelection.setJoinStyle(Qt::RoundJoin);
    penForSelection.setWidth(1);//4

    painter.drawImage(target, plane, source);

    if(initialized) // don't do this whan the data is no
    {
        if(splineReady)
        {
            if(displayLine)
            {
                QPainterPath path;
                painter.setPen(penForPath);
                path.moveTo(mySpline->getPosition(0)[0], mySpline->getPosition(0)[1]);

                for(double i = 0; i <= mySpline->getMaxT(); i+=0.01) // draw the path by consistently drawing straight lines between interpolated coordinate on the spline
                {
                        path.lineTo(mySpline->getPosition(i)[0], mySpline->getPosition(i)[1]);
                }

                path.moveTo(mySpline->getPosition(0)[0], mySpline->getPosition(0)[1]);
                painter.drawPath(path);
            }
        }
        else
        {
            QPainterPath path;
            painter.setPen(penForPath);

            path.moveTo(splinePoints[0].x(), splinePoints[0].y()); //move the QPen to the first spot

            for(int i = 0; i < splinePoints.size(); i++)
            {
                path.lineTo(splinePoints[i].x(), splinePoints[i].y());
            }
            path.lineTo(splinePoints[0].x(), splinePoints[0].y()); // move to the first spot again to close the shape
            painter.drawPath(path);


        }
        for(auto &k : splinePoints)
        {
            painter.setPen(penForEllipse);
            painter.drawEllipse(QPointF(k.x(), k.y()), 5, 5);
            painter.drawEllipse(QPointF(k.x(), k.y()), 10, 10);

        }
        for(auto i = 0; i < splinePoints.size(); i++)
        {
            painter.setPen(penForRobot);
            painter.save();
            painter.translate(splinePoints[i].x(), splinePoints[i].y());
            painter.rotate(pointRotation[i]);
            //painter.drawRect(-25, -37, 50, 74);
            painter.drawRect(-25, 0, 50, 74);
            painter.restore();
        }
        if(currentRow != -1)
        {
            painter.setPen(penForSelection);
            painter.drawRect(splinePoints[currentRow].x()-50, splinePoints[currentRow].y()-50, 100, 100);
        }

//        currentRow = -1;
        initialized = false;
        splineReady = false;
    }
    if(preview)
    {
        painter.setPen(penForPreview);
        painter.save();
        painter.translate(previewPoint.x(), previewPoint.y());
        painter.rotate(previewRotation);
        //painter.drawRect(-25, -37, 50, 74);
        painter.drawRect(-25, 0, 50, 74);
        painter.restore();
    }
}

void RenderArea::setAircraft(qint32 index)
{
    QDir dir = QString(PATHSDIR);
    qDebug() << dir;
    filePath = dir.absoluteFilePath("%1.txt").arg(index);
    qDebug() << filePath;

    QDir aircraftDir(AIRCRAFTSDIR);
    imageName = QString(":/aircrafts/%1.png").arg(index);
    plane =  QImage(imageName);

    emit updateList(splinePoints.size());
    updateSpline();
}

void RenderArea::savePath()
{
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly))
    {
        qWarning() << file.error() << file.errorString();
        return;
    }
    QDataStream out(&file);
    for(size_t t = 0; t < splinePoints.size()-1; t++)
    {
        write_coord(out, splinePoints[t].x(), splinePoints[t].y(), pointRotation[t], flags::next_line);
    }
    write_coord(out, splinePoints[splinePoints.size()-1].x(), splinePoints[splinePoints.size()-1].y(), pointRotation[pointRotation.size()-1], flags::eof);
    file.close();
}

void RenderArea::mousePressEvent(QMouseEvent *event)
{
    QPointF pos = event->pos();
    std::cout << "pos is: "  << pos.x() << " " << pos.y() << std::endl;
    if((pos.x() <= width()) && (pos.y() <= height())) // check the validity of adding pos
        emit addPointQuery(pos);
}


void RenderArea::on_pushButton_clicked()
{
    updateSpline();
}

void RenderArea::updateSpline()
{

    if(splinePoints.size() >= 1 && splinePoints.size() < 4)
    {
        initialized = true;
        std::cout << "LESS THAN 4 POINTS, DRAW STRAIGHT LINE INSTEAD OF SPLINE" << std::endl;
    }
    else if(splinePoints.size()>=4)
    {
        initialized = true;
        mySpline = createSpline();
        splineReady = true;
        std::cout << mySpline->getMaxT() << std::endl;
        std::cout << mySpline->isLooping() << std::endl;
    }

    repaint();
}

void RenderArea::on_doubleSpinBox_valueChanged(double arg1)
{
    pathDensity = arg1;
}

void RenderArea::on_pushButton_2_clicked()
{
    emit queryIndex();
}

void RenderArea::recieve_index(qint32 index)
{
    ui->label_2->setNum(index);
}

void RenderArea::removePoint(qint32 index)
{
    splinePoints.erase(splinePoints.begin()+index);
    pointRotation.erase(pointRotation.begin()+index);
    updateSpline();
}

void RenderArea::addPointWithRotation(QPointF pos, int index, int rotation)
{
    if(index == -1) // when no points are chosen index are set to -1
    {
        splinePoints.push_back(QVector2D{float(pos.x()), float(pos.y())});
        pointRotation.push_back(rotation);
    }
    else
    {
        splinePoints.insert(splinePoints.begin()+index, QVector2D{float(pos.x()), float(pos.y())});
        pointRotation.insert(pointRotation.begin()+index, rotation);
    }
    updateSpline();
}

void RenderArea::addPoint(QPointF pos, int index)
{
    addPointWithRotation(pos, index, 0);
}

void RenderArea::modifyPoint(QPointF pos, int index, int rotation)
{
    splinePoints[index][0] = pos.x();
    splinePoints[index][1] = pos.y();
    pointRotation[index] = rotation;
    updateSpline();
}

void RenderArea::loadPath()
{
    if(filePath.isEmpty()){ QMessageBox::warning(this, "WARNING!!!", "YOU HAVEN'T SPECIFIED THE MODEL YET");}
    else
    {
        QFile file(filePath);
        if(!file.open(QIODevice::ReadOnly))
        {
            qWarning() << file.error() << file.errorString();
            return;
        }

        QDataStream in(&file);
        inspectionPath temPath;
        std::vector<int> rotation;
        if(read_coord(in, temPath, rotation)){}
        for(size_t i = 0; i != temPath.path.size(); i++)
        {
            emit addPointQueryWithRotation(QPointF(temPath.path[i].x, temPath.path[i].y), rotation[i]);
        }
        file.close();
    }
    updateSpline();
}

void RenderArea::flip()
{
    auto splinePoints_ = splinePoints;
    auto pointRotation_ = pointRotation;
    for(int i = splinePoints_.size()-1; i >= 0; i--)
    {
        emit addPointQueryWithRotation(QPointF(splinePoints_[i].x(), height() - splinePoints_[i].y()), pointRotation_[i] >= 180 ? (360 - pointRotation_[i]) : (180 - pointRotation_[i]), true);
    }
//    for(auto k = splinePoints_.rbegin(); k != splinePoints_.rend(); k++)
//    {
//        emit addPointQuery(QPointF(k->x(), height()-k->y()));
//    }
}

void RenderArea::setSaftyDist(double multiplier)
{
    auto splinePoints_ = splinePoints;
    auto mySpline_ = mySpline;
    for(size_t i = 0; i <= mySpline_->getMaxT(); i++)
    {
        auto slope = mySpline_->getTangent(i);
        //std::cout << slope.tangent.x() << " " << slope.tangent.y() << std::endl;
        double normal = std::atan((slope.tangent.y()/slope.tangent.x()));
        splinePoints[i][0] = splinePoints_[i].x() + multiplier * std::cos(normal) * (splinePoints_[i].x() >= width()/1.9 ? 1 : -1);
        splinePoints[i][1] = splinePoints_[i].y() - multiplier * std::sin(normal) * (splinePoints_[i].x() >= width()/2 ? 1 : -1);
    }
    updateSpline();
}

void RenderArea::on_checkBox_stateChanged(int arg1)
{
    displayLine = ui->checkBox->isChecked();
    updateSpline();
}

void RenderArea::selectCurrentRow(int currentRow_)
{
    currentRow = currentRow_;
    updateSpline();
}

void RenderArea::previewBox(QPointF pos, int rotation)
{
    preview = true;
    previewPoint = pos;
    previewRotation = rotation;
    updateSpline();
}

void RenderArea::stopPreview()
{
    preview = false;
    updateSpline();
}

void RenderArea::queryPoint(int index)
{
    emit loadPoint(QPointF(splinePoints[index].x(), splinePoints[index].y()), pointRotation[index]);
}
