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

    painter.drawImage(target, plane, source);

    if(initialized) // don't do this whan the data is no
    {
        if(splineReady)
        {
            QPainterPath path;
            path.moveTo(mySpline->getPosition(0)[0], mySpline->getPosition(0)[1]);

            for(double i = 0; i <= mySpline->getMaxT(); i+=0.01) // draw the path by consistently drawing straight lines between interpolated coordinate on the spline
            {
                    path.lineTo(mySpline->getPosition(i)[0], mySpline->getPosition(i)[1]);
            }

            path.moveTo(mySpline->getPosition(0)[0], mySpline->getPosition(0)[1]);
            painter.drawPath(path);

            for(double i = 0.0, lastpoint = -0.01; i <= mySpline->getMaxT(); i+=0.01)
            {
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
        }
        else
        {
            QPainterPath path;
            path.moveTo(splinePoints[0].x(), splinePoints[0].y()); //move the QPen to the first spot

            for(int i = 0; i < splinePoints.size(); i++)
            {
                path.lineTo(splinePoints[i].x(), splinePoints[i].y());
            }
            path.lineTo(splinePoints[0].x(), splinePoints[0].y()); // move to the first spot again to close the shape
            painter.drawPath(path);
        }
    initialized = false;
    splineReady = false;
    }
}

void RenderArea::setAircraft(qint32 index)
{
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

    write_coord(out, 345, 23, flags::next_line);
    write_coord(out, 25, 435, flags::next_line);
    write_coord(out, 734, 213, flags::next_line);
    write_coord(out, 354, 227, flags::next_line);
    write_coord(out, 254, 153, flags::next_line);
    write_coord(out, 324, 234, flags::next_line);
    write_coord(out, 345, 23, flags::eof);


    file.close();

    if(!file.open(QIODevice::ReadOnly))
    {
        qWarning() << file.error() << file.errorString();
        return;
    }

    QDataStream in(&file);
    read_coord(in, inspath);
    file.close();

    toSplinePoints(inspath, splinePoints);
    std::cout << splinePoints.size() << std::endl;

    QDir aircraftDir(AIRCRAFTSDIR);
    QString imageName = QString(":/aircrafts/%1.png").arg(index);
    plane =  QImage(imageName);

    emit updateList(splinePoints.size());
    updateSpline();
}



void RenderArea::on_pushButton_clicked()
{
    updateSpline();
}

void RenderArea::updateSpline()
{
    mySpline = createSpline();
    if(splinePoints.size() >= 1)
        initialized = true;
    if(splinePoints.size()>=4)
        splineReady = true;
    std::cout << mySpline->getMaxT() << std::endl;
    std::cout << mySpline->isLooping() << std::endl;
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
