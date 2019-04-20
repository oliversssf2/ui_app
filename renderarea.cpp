#include "renderarea.h"
#include "ui_renderarea.h"

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderArea),
    plane(QImage())
{
    ui->setupUi(this);
}

RenderArea::~RenderArea()
{
    delete ui;
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    QRectF target(0, 0, 500, 500);
    QRectF source(0, 0, plane.width(), plane.height());

    QPainter painter(this);
    painter.drawImage(target, plane, source);
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
    read_coord(in, inspath);
    file.close();

    QDir aircraftDir(AIRCRAFTSDIR);
    QString imageName = QString(":/aircrafts/%1.png").arg(index);
    plane =  QImage(imageName);
    qDebug() << plane.width() << plane.height();
    repaint();
}

