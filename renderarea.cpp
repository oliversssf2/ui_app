#include "renderarea.h"
#include "ui_renderarea.h"

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderArea),
    plane(QImage()),
    mySpline({})
{
    ui->setupUi(this);
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
    mypainter = &painter;

    painter.drawImage(target, plane, source);

    if(initialized) // don't do this whan the data is no
    {
        QPainterPath path;
        path.moveTo(mySpline->getPosition(0)[0], mySpline->getPosition(0)[1]);

        for(float i = 0.0f; i <= mySpline->getMaxT(); i+=0.05f)
        {
            path.lineTo(mySpline->getPosition(i)[0], mySpline->getPosition(i)[1]);
        }

        path.moveTo(mySpline->getPosition(0)[0], mySpline->getPosition(0)[1]);

        for(float i = 0.0f; i <= mySpline->getMaxT(); i+=0.05f)
        {
            QRectF box(QPointF(mySpline->getPosition(i)[0]+20, mySpline->getPosition(i)[1]+20), QPointF(mySpline->getPosition(i)[0]-20, mySpline->getPosition(i)[1]-20));
            painter.drawRect(box);
            auto slope = mySpline->getTangent(i);
            auto tiltAng = qAtan2(slope.tangent.y(), slope.tangent.x());
            painter.rotate(tiltAng);
        }

        painter.rotate(rand());
        painter.drawPath(path);
    }    
    mypainter = nullptr;
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

    for(auto &k : inspath.path)
    {
        splinePoints.push_back(QVector2D(k.x, k.y));
    }
    std::cout << splinePoints.size() << std::endl;

    QDir aircraftDir(AIRCRAFTSDIR);
    QString imageName = QString(":/aircrafts/%1.png").arg(index);
    plane =  QImage(imageName);

    updateSpline();
}



void RenderArea::on_pushButton_clicked()
{
    updateSpline();
}

void RenderArea::updateSpline()
{
    mySpline = createSpline();
    initialized = true;
    std::cout << mySpline->getMaxT() << std::endl;
    std::cout << mySpline->isLooping() << std::endl;
    repaint();
}
