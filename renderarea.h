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
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

protected:
    //void paintEvent(QPaintEvent *event) override;

private:
    Ui::RenderArea *ui;

    QPixmap plane;

};

#endif // RENDERAREA_H
