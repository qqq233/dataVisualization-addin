#ifndef HISTORY_PRICE_MODEL_H
#define HISTORY_PRICE_MODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QDebug>

class history_price_model : public QStandardItemModel
{
public:
    history_price_model();
    ~history_price_model();

    void set_data(QMap<QString, QList<QVariant>> data);

private:
    void init();

    void refresh();

    bool data_check(QMap<QString, QList<QVariant>> data);

    QMap<QString, QList<QVariant>> m_data;
};

#endif // HISTORY_PRICE_MODEL_H
