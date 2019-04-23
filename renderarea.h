#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QtCore>
#include <QPainter>
#include <QVector2D>
#include <QtMath>

#include <helper.h>
#include <config.h>
#include <vector>



#include <spline_library/spline.h>
#include <spline_library/splines/uniform_cr_spline.h>

namespace Ui {
class RenderArea;
}

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    explicit RenderArea(QWidget *parent = nullptr);
    ~RenderArea();

public slots:
    void setAircraft(qint32 index);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;
    void printPath(QPainter& painter);
    void updateSpline();
    std::shared_ptr<LoopingUniformCRSpline<QVector2D>> createSpline(){ return std::make_shared<LoopingUniformCRSpline<QVector2D>>(splinePoints); }

private slots:
    void on_pushButton_clicked();

private:
    Ui::RenderArea *ui;
    inspectionPath inspath;
    std::vector<QVector2D> splinePoints;
    std::shared_ptr<LoopingUniformCRSpline<QVector2D>> mySpline;
    QImage plane;
    QPainter* mypainter = nullptr;
    bool initialized = false;
};

#endif // RENDERAREA_H
