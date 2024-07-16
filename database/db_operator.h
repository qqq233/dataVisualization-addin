#ifndef DB_OPERATOR_H
#define DB_OPERATOR_H

#include "database.h"
#include <map>
#include <string>
#include <iterator>
#include <QSqlQuery>

using namespace std;

class db_operator
{
public:
    db_operator();

    map<string, list<string>> select_products();

    bool input_price(QString type, QString name, QString price, QString time);

    QMap<QString, QList<QVariant>> select_price(QString type, QString name);

    bool input_product(QString type_chz, QString type_en, QString name_chz, QString name_en);
};

#endif // DB_OPERATOR_H
