#ifndef PATHPLANNER_H
#define PATHPLANNER_H

#include <QWidget>
#include <QDebug>
#include <QtCore>
#include <QString>
#include <QDataStream>
#include <QFile>
#include <QList>
#include <QMessageBox>

#include <helper.h>
#include <renderarea.h>

#include "pointcreater.h"

namespace Ui {
class pathPlanner;
}

class pathPlanner : public QWidget
{
    Q_OBJECT

public:
    explicit pathPlanner(QWidget *parent = nullptr);
    ~pathPlanner();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    void updateName();
    void recieveIndexQuery();

    void recieveAddPointQuery(QPointF pos, bool pushBackAnyway = false);
    void recieveAddPointQueryWithRotation(QPointF pos, int rotation, bool pushBackAnyway = false);

    void on_pushButton_3_clicked();
    void updateList(qint32 size);

    void on_pushButton_4_clicked();

    void on_flipButton_clicked();

    void on_setSaftyDist_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_addPointButton_clicked();

    void on_pushButton_5_clicked();

signals:
    void sendPlaneModel(qint32 fileindex);
    void send_index(qint32 index); // send the index of the selected item in the combobox(start from 1 not 0)
    void removePoint(qint32 index);
    void addPoint(QPointF pos, int index, int rotation);
    void loadPath();
    void savePath();
    void flip();
    void setSaftyDist(double multiplier);
    void selectCurrentRow(int currentRow);
    void modifyquery(int currentRow);
    void setMode(int i);
    void saveCenter(int i);

private:
    Ui::pathPlanner *ui;
    RenderArea *rarea;
    inspectionPath insPath;
    pointCreater* pointcreater;
};

#endif // PATHPLANNER_H
