#include "renderarea.h"
#include "ui_renderarea.h"

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderArea)
{
    ui->setupUi(this);
    resize(500, 500);
    setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
}

RenderArea::~RenderArea()
{
    delete ui;
}

void RenderArea::paintEvent(QPaintEvent *event)
{

}

void RenderArea::setAircraft(inspectionPath& path, QImage& plane, qint32 index)
{

}

