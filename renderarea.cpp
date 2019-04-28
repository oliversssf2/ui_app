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
    penForPath.setWidth(6);

    QPen penForRobot;
    penForRobot.setStyle(Qt::SolidLine);
    penForRobot.setColor(QColor(51, 153, 255));
    penForRobot.setCapStyle(Qt::RoundCap);
    penForRobot.setJoinStyle(Qt::RoundJoin);
    penForRobot.setWidth(4);

    QPen penForEllipse;
    penForEllipse.setStyle(Qt::SolidLine);
    penForEllipse.setColor(QColor(255, 153, 51));
    penForEllipse.setCapStyle(Qt::RoundCap);
    penForEllipse.setJoinStyle(Qt::RoundJoin);
    penForEllipse.setWidth(2);

    painter.drawImage(target, plane, source);

    if(initialized) // don't do this whan the data is no
    {
        if(splineReady)
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


            for(double i = 0.0, lastpoint = -0.01; i <= mySpline->getMaxT(); i+=0.01)
            {
                painter.setPen(penForRobot);
                if(mySpline->arcLength(i, lastpoint) >= pathDensity)
                {
                    lastpoint = i;
                    painter.save();// save the state of the painter(EG rotation, translation, penstyel blah blah blah)

                    auto slope = mySpline->getTangent(i);
                    auto tiltRadian = std::atan2(slope.tangent.y(), slope.tangent.x());
                    auto tiltDegree = qRadiansToDegrees(tiltRadian);
                    painter.translate(mySpline->getPosition(i)[0], mySpline->getPosition(i)[1]); //translate the painter to the goal position
                    painter.rotate(tiltDegree); //rotate the painter according to the tangent

                    painter.drawRect(-10, -10, 20, 20); //draw the rectangle
                    painter.restore();// restore the saved state so the rotation and translation won't affect the next iteration
                }
            }
            for(int i = 0; i < mySpline->getMaxT(); i++)
            {
                painter.setPen(penForEllipse);
                painter.drawEllipse(QPointF(mySpline->getPosition(i).x(), mySpline->getPosition(i).y()), 5, 5);
                painter.drawEllipse(QPointF(mySpline->getPosition(i).x(), mySpline->getPosition(i).y()), 10, 10);

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

            for(auto &k : splinePoints)
            {
                painter.setPen(penForEllipse);
                painter.drawEllipse(QPointF(k.x(), k.y()), 5, 5);
                painter.drawEllipse(QPointF(k.x(), k.y()), 10, 10);

            }
        }

        initialized = false;
        splineReady = false;
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
    for(auto i = splinePoints.begin(); i!=splinePoints.end()-1; i++)
    {
        write_coord(out, i->x(), i->y(),flags::next_line);
    }
    auto lastPt = splinePoints.end()-1;
    write_coord(out, lastPt->x(), lastPt->y(), flags::eof);
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

    if(splinePoints.size() >= 1)
    {
        initialized = true;
        std::cout << "LESS THAN 4 POINTS, DRAW STRAIGHT LINE INSTEAD OF SPLINE" << std::endl;
    }

    if(splinePoints.size()>=4)
    {
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
    updateSpline();
}

void RenderArea::addPoint(QPointF pos, int index)
{
    if(index = -1) // when no points are chosen index are set to -1
        splinePoints.push_back(QVector2D{float(pos.x()), float(pos.y())});
    else
        splinePoints.insert(splinePoints.begin()+index, QVector2D{float(pos.x()), float(pos.y())});
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
        if(read_coord(in, temPath)){}
        for(auto &k : temPath.path)
        {
            emit addPointQuery(QPointF(k.x, k.y));
        }
        file.close();
    }
    updateSpline();
}

void RenderArea::flip()
{
    auto splinePoints_ = splinePoints;
    for(auto k = splinePoints_.rbegin(); k != splinePoints_.rend(); k++)
    {
        emit addPointQuery(QPointF(k->x(), height()-k->y()));
    }
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
        splinePoints[i][0] = splinePoints_[i].x() + multiplier * std::cos(normal) * (splinePoints_[i].x() >= width()/2 ? 1 : -1)/**(mySpline->getPosition(i).y() >= (width()/2) ? -1:1)*/;
        splinePoints[i][1] = splinePoints_[i].y() - multiplier * std::sin(normal)/**(mySpline->getPosition(i).y() >= (width()/2) ? -1:1)*/;
    }
    updateSpline();
}
