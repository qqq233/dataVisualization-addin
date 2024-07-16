#ifndef MAINAPP_WND_H
#define MAINAPP_WND_H

#include "ui/main_left_widget.h"
#include "ui/data_analysis_wnd.h"
#include "database/db_operator.h"
#include <QMainWindow>
#include <QHBoxLayout>

namespace Ui {
class mainApp_Wnd;
}

class mainApp_Wnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainApp_Wnd(QWidget *parent = nullptr);
    ~mainApp_Wnd();

private:
    void initUI();
    void init();

    void clean();
    void refresh_ui();

    //////////////////////////////////////////////////////
    // 数据库查询操作
    bool set_type_name();

    /////////////////////////////////////////////////////

private:
    Ui::mainApp_Wnd *ui;

    QHBoxLayout *m_mainLayout;

    main_left_widget *m_left_widegt;

    data_analysis_wnd *m_data_als_wnd;

};

#endif // MAINAPP_WND_H
