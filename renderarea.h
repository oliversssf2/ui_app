#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QtCore>
#include <helper.h>

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
    void setAircraft(inspectionPath& path, QImage& plane, qint32 index);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::RenderArea *ui;
    inspectionPath path;
    QImage plane;
};

#endif // RENDERAREA_H
