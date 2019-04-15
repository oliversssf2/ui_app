#ifndef LISTPOINTS_H
#define LISTPOINTS_H

#include <QWidget>

namespace Ui {
class listPoints;
}

class listPoints : public QWidget
{
    Q_OBJECT

public:
    explicit listPoints(QWidget *parent = nullptr);
    ~listPoints();

private:
    Ui::listPoints *ui;
};

#endif // LISTPOINTS_H
