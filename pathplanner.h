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

    void on_pushButton_3_clicked();
    void updateList(qint32 size);

signals:
    void sendPlaneModel(qint32 fileindex);
    void send_index(qint32 index); // send the index of the selected item in the combobox(start from 1 not 0)
    void removePoint(qint32 index);

private:
    Ui::pathPlanner *ui;
    RenderArea *rarea;
    inspectionPath insPath;
};

#endif // PATHPLANNER_H
