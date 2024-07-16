#include "data_analysis_wnd.h"
#include "ui_data_analysis_wnd.h"

data_analysis_wnd::data_analysis_wnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::data_analysis_wnd)
{
    ui->setupUi(this);
    initConnect();
    init();
    refresh_ui();
}

data_analysis_wnd::~data_analysis_wnd()
{
    delete ui;
}

void data_analysis_wnd::refresh_ui()
{
    ui->name->clear();
    ui->type->clear();
    ui->price_lineEdit->clear();

    m_type_name_map.clear();

    m_type_name_map = m_db->select_products();

    map<string, list<string>>::iterator it = m_type_name_map.begin();

    while(it != m_type_name_map.end()){
        QString type = QString::fromStdString(it->first);
        ui->type->addItem(type);
        it ++;
    }
}

void data_analysis_wnd::refresh_lines()
{

}

void data_analysis_wnd::init()
{
    m_data_model = new history_price_model();

    ui->tableView->setModel(m_data_model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QHBoxLayout *layout_lineview = new QHBoxLayout;
    ui->charts_widget->setLayout(layout_lineview);

    m_line_view = new lines_view(ui->charts_widget);
    layout_lineview->addWidget(m_line_view);

    ui->tabWidget->setCurrentIndex(0);
}

void data_analysis_wnd::initConnect()
{
    connect(ui->type, &QComboBox::currentTextChanged, this, &data_analysis_wnd::slot_type_changed);
    connect(this, &data_analysis_wnd::sig_refresh, this, &data_analysis_wnd::slot_refresh);
}

bool data_analysis_wnd::is_product_exits(QString type_chz, QString name_chz)
{
    map<string, list<string>>::iterator it = m_type_name_map.begin();

    list<string> current_type_product_list;
    while(it != m_type_name_map.end()){
        QString type = QString::fromStdString(it->first);
        if(type == type_chz){
            current_type_product_list = it->second;
        }
        it ++;
    }

    foreach(auto name, current_type_product_list){
        if(QString::fromStdString(name) == name_chz){
            return true;
        }
    }
    return false;
}

void data_analysis_wnd::slot_type_changed(QString type)
{
    if(type.isEmpty())
        return;

    ui->name->clear();

    auto it = m_type_name_map.find(type.toStdString());

    auto list = it->second;
    foreach(auto name, list){
        ui->name->addItem(QString::fromStdString(name));
    }
}

void data_analysis_wnd::on_price_input_btn_clicked()
{
    QString type = ui->type->currentText();
    QString name = ui->name->currentText();
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString price = ui->price_lineEdit->text();

    QString str = QString("是否录入当前价格：%1：%2").arg(name).arg(price);
    QMessageBox box;
    box.setText(str);
    box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    int ret = box.exec();

    if(ret == QMessageBox::Ok){
        if(m_db->input_price(type, name, price, time)){
            box.setText("录入成功");
            box.setStandardButtons(QMessageBox::Ok);
            box.exec();
        }
        else{
            box.setText("录入失败");
            box.setStandardButtons(QMessageBox::Ok);
            box.exec();
        }
    }
    else if(ret == QMessageBox::Cancel)
        return;
}

void data_analysis_wnd::on_price_search_btn_clicked()
{
    QString type = ui->type->currentText();
    QString name = ui->name->currentText();

    QMap<QString, QList<QVariant>> res = m_db->select_price(type, name);
    if(res.size() == 0){
        QMessageBox box;
        box.setText("查询数据为空");
        box.setStandardButtons(QMessageBox::Ok);
        box.exec();
        return;
    }

    m_data_model->set_data(res);
    m_line_view->set_data(res, name);
}

void data_analysis_wnd::on_ok_clicked()
{
    QString type_chz = ui->type_chz->text();
    QString type_en = ui->type_en->text();
    QString name_chz = ui->name_chz->text();
    QString name_en = ui->name_en->text();

    if(type_chz.isEmpty() || type_en.isEmpty() || name_chz.isEmpty() || name_en.isEmpty()){
        QMessageBox box;
        box.setText("输入内容不允许为空");
        box.setStandardButtons(QMessageBox::Ok);
        box.exec();
        return;
    }

    // 校验商品是否已录入
    if(is_product_exits(type_chz, name_chz)){
        QMessageBox box;
        box.setText("当前商品已存在,请勿重复录入");
        box.setStandardButtons(QMessageBox::Ok);
        box.exec();
        return;
    }

    // 录入
    if(!m_db->input_product(type_chz, type_en, name_chz, name_en)){
        QMessageBox box;
        box.setText("商品录入失败");
        box.setStandardButtons(QMessageBox::Ok);
        box.exec();
        return;
    }
    else{
        QMessageBox box;
        box.setText("商品录入成功");
        box.setStandardButtons(QMessageBox::Ok);
        box.exec();

        emit sig_refresh();
        return;
    }
}

void data_analysis_wnd::slot_refresh()
{
    refresh_ui();
}
