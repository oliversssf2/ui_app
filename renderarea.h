﻿#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QtCore>
#include <QPainter>
#include <QVector2D>
#include <QtMath>
#include <QMouseEvent>
#include <QMessageBox>

#include <helper.h>
#include <config.h>
#include <vector>
#include <cmath>



#include <spline_library/spline.h>
#include <spline_library/splines/uniform_cr_spline.h>

constexpr double Pi = 3.141592653;

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
    void recieve_index(qint32);
    void removePoint(qint32 index);
    inline int getSplineSize(){return splinePoints.size();}
    void addPoint(QPointF pos, int index);
    void addPointWithRotation(QPointF pos, int index, int rotation);
    void loadPath();
    void savePath();
    void flip();
    void setSaftyDist(double multiplier);
    void selectCurrentRow(int currentRow);

    void previewBox(QPointF pos, int rotation);
    void stopPreview();
    void queryPoint(int index); // for modifying point

    void modifyPoint(QPointF pos, int index, int rotation);
    void saveCenter(int i);
signals:
    void queryIndex();
    void updateList(qint32);
    void addPointQuery(QPointF pos, bool pushBackAnyway = false);
    void addPointQueryWithRotation(QPointF pos, int rotation, bool pushBackAnyway = false);
    void updateName();
    void loadPoint(QPointF pos, int rotation); //for modifying point

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void printPath(QPainter& painter);
    void updateSpline();
    std::shared_ptr<LoopingUniformCRSpline<QVector2D>> createSpline(){ return std::make_shared<LoopingUniformCRSpline<QVector2D>>(splinePoints); emit updateName();}
    void drawPath();

private slots:
    void on_pushButton_clicked();

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_pushButton_2_clicked();

    void on_checkBox_stateChanged(int arg1);


private:
    Ui::RenderArea *ui;
    inspectionPath inspath;
    std::vector<QVector2D> splinePoints;
    std::shared_ptr<LoopingUniformCRSpline<QVector2D>> mySpline;
    std::vector<int> pointRotation;
    std::vector<QPointF> centers;

    QImage plane;
    QString imageName; // path/name of the image
    QString filePath;
    QString centerFilePath;

    QPainter* mypainter = nullptr;
    bool initialized = false;
    bool splineReady = false;
    double pathDensity;

    bool displayLine = true;
    int currentRow = -1;

    bool preview = false;
    QPointF previewPoint;
    int previewRotation;

    int boxWidth = 50;
    int boxHeight = 74;
};

inline void toSplinePoints(inspectionPath& inspath, std::vector<QVector2D>& splinePoints)
{
    for(auto &k : inspath.path)
    {
        splinePoints.push_back(QVector2D(k.x, k.y));
    }
}

inline void toinsPath(std::vector<QVector2D>& splinePoints, inspectionPath& inspath)
{
    inspath.path.clear();
    for(auto &k : splinePoints)
    {
        inspath.path.push_back(coord{int(k.x()), int(k.y())});
    }
}

#endif // RENDERAREA_H
