#ifndef RAW_MATERIAL_SUB_WND_H
#define RAW_MATERIAL_SUB_WND_H

#include <QWidget>

namespace Ui {
class raw_material_sub_wnd;
}

class raw_material_sub_wnd : public QWidget
{
    Q_OBJECT

public:
    explicit raw_material_sub_wnd(QWidget *parent = nullptr);
    ~raw_material_sub_wnd();

private:
    Ui::raw_material_sub_wnd *ui;
};

#endif // RAW_MATERIAL_SUB_WND_H
