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

signals:
    void addPoint(QPointF pos, int rot);
    void previewBox(QPointF pos, int rot);
    void stopPreview();

protected:
    void reject() override;

private slots:
    void on_buttonBox_accepted();

    void on_spinBox_3_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::pointCreater *ui;
    int currentIndex = -1;
};

#endif // POINTCREATER_H
