#ifndef DATA_ANALYSIS_WND_H
#define DATA_ANALYSIS_WND_H

#include "database/db_operator.h"
#include "ui/history_price_model.h"
#include "ui/lines_view.h"
#include <QWidget>
#include <map>
#include <string>
#include <iterator>
#include <QDateTime>
#include <QMessageBox>
#include <QHBoxLayout>

using namespace std;

namespace Ui {
class data_analysis_wnd;
}

/**
 * @brief The data_analysis_wnd class 数据分析窗口
 */
class data_analysis_wnd : public QWidget
{
    Q_OBJECT

public:
    explicit data_analysis_wnd(QWidget *parent = nullptr);
    ~data_analysis_wnd();

    void refresh_ui();

    void refresh_lines();

private:
    Ui::data_analysis_wnd *ui;

    db_operator *m_db;

    map<string, list<string>> m_type_name_map;

    history_price_model *m_data_model;

    lines_view *m_line_view;

    void init();

    void initConnect();

    bool is_product_exits(QString type_chz, QString name_chz);

private slots:
    void slot_type_changed(QString type);

    void on_price_input_btn_clicked();

    void on_price_search_btn_clicked();

    void on_ok_clicked();

    void slot_refresh();

signals:
    void sig_refresh();
};

#endif // DATA_ANALYSIS_WND_H
