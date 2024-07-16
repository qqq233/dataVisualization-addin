#ifndef MAIN_LEFT_WIDGET_H
#define MAIN_LEFT_WIDGET_H

#include <QWidget>

namespace Ui {
class main_left_widget;
}

class main_left_widget : public QWidget
{
    Q_OBJECT

public:
    explicit main_left_widget(QWidget *parent = nullptr);
    ~main_left_widget();

private:
    Ui::main_left_widget *ui;
};

#endif // MAIN_LEFT_WIDGET_H
