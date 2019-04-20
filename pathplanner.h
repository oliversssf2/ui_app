#ifndef PATHPLANNER_H
#define PATHPLANNER_H

#include <QWidget>
#include <QDebug>
#include <QtCore>
#include <QString>
#include <QDataStream>
#include <QFile>
#include <QList>

#include <helper.h>
#include <renderarea.h>
#include <config.h>

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

signals:
    void send(inspectionPath& path, QImage& plane, qint32 index);

private:
    Ui::pathPlanner *ui;
    RenderArea *rarea;
    inspectionPath insPath;
};

#endif // PATHPLANNER_H
