#include "main_left_widget.h"
#include "ui_main_left_widget.h"

main_left_widget::main_left_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::main_left_widget)
{
    ui->setupUi(this);
}

main_left_widget::~main_left_widget()
{
    delete ui;
}
