#pragma once

#include <QWidget>

namespace Ui {
class vnc;
}

class VNC : public QWidget
{
    Q_OBJECT

public:
    explicit VNC(QWidget *parent = nullptr);
    ~VNC();

private:
    Ui::vnc *ui;
};

