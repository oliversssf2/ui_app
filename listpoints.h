#ifndef LISTPOINTS_H
#define LISTPOINTS_H

#include <QWidget>

namespace Ui {
class listpoints;
}

class listpoints : public QWidget
{
    Q_OBJECT

public:
    explicit listpoints(QWidget *parent = nullptr);
    ~listpoints();

private:
    Ui::listpoints *ui;
};

#endif // LISTPOINTS_H
