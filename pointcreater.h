#ifndef POINTCREATER_H
#define POINTCREATER_H

#include <QDialog>

namespace Ui {
class pointCreater;
}

class pointCreater : public QDialog
{
    Q_OBJECT

public:
    explicit pointCreater(QWidget *parent = nullptr);
    ~pointCreater();


public slots:
    void modifyQuery(int pointIndex);

    void setMode(int i);

    void loadPoint(QPointF pos, int rotation);

signals:
    void updatePoint(QPointF pos, int index, int rotation);
    void addPoint(QPointF pos, int rot);
    void previewBox(QPointF pos, int rot);
    void stopPreview();
    void pointQuery(int index);


protected:
    void reject() override;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_xspinBox_valueChanged(int arg1);

    void on_yspinBox_valueChanged(int arg1);

    void on_rotspinBox_valueChanged(int arg1);



//    void on_xaddten_clicked();

//    void on_xminusten_clicked();

//    void on_yaddten_clicked();

//    void on_yminusten_clicked();

//    void on_rotaddten_clicked();

//    void on_rotminuxten_clicked();

private:
    Ui::pointCreater *ui;
    int currentIndex = -1;

    int mode = -1;
    //mode:
    // 0 : add Point
    // 1 : modify Point
};

#endif // POINTCREATER_H
