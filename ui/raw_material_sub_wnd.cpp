#include "raw_material_sub_wnd.h"
#include "ui_raw_material_sub_wnd.h"

raw_material_sub_wnd::raw_material_sub_wnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::raw_material_sub_wnd)
{
    ui->setupUi(this);
}

raw_material_sub_wnd::~raw_material_sub_wnd()
{
    delete ui;
}
