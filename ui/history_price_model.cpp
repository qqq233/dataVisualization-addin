#include "history_price_model.h"

history_price_model::history_price_model()
{
    init();
}

history_price_model::~history_price_model()
{

}

void history_price_model::set_data(QMap<QString, QList<QVariant> > data)
{
    if(!data_check(data)){
        qDebug() << "model 数据校验失败";
        return;
    }

    m_data.clear();
    m_data = data;

    refresh();
}

void history_price_model::init()
{
    QStringList header;
    header << "时间" << "价格";
    this->setHorizontalHeaderLabels(header);
}

void history_price_model::refresh()
{
    clear();
    QStringList header;
    header << "时间" << "价格";
    this->setHorizontalHeaderLabels(header);

    QList<QVariant> time_list = m_data["time"];
    QList<QVariant> price_list = m_data["price"];

    int col = 0;
    int time_len = time_list.size();
    for(int row=0; row<time_len; row++){
        QStandardItem *item_time = new QStandardItem;
        item_time->setText(time_list[row].toString());
        this->setItem(row, col++, item_time);

        QStandardItem *item_price = new QStandardItem;
        item_price->setText(price_list[row].toString());
        this->setItem(row, col, item_price);

        col = 0;
    }
}

bool history_price_model::data_check(QMap<QString, QList<QVariant> > data)
{
    int time_len = data["time"].size();
    int price_len = data["price"].size();

    if(time_len <= 0 || price_len <= 0 || time_len != price_len)
        return false;
    else
        return true;
}
