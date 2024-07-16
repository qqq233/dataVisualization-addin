#include "db_operator.h"

db_operator::db_operator()
{

}

map<string, list<string>> db_operator::select_products()
{
    QString str = "select type_chz, name_chz from products_category;";

    QList<QList<QVariant>> value;
    map<string, list<string>> res;
    if(!database::getInstance()->select_rows(value, str)){
        qDebug() << "type and name select failed";
        return res;
    }

    foreach(auto list, value){
        string type = list[0].toString().toStdString();
        string name = list[1].toString().toStdString();
        res[type].push_back(name);
    }

    return res;
}

bool db_operator::input_price(QString type, QString name, QString price, QString time)
{
    QString str = "select type_en, name_en from products_category "
                  "where type_chz=? and name_chz=?;";

    QStringList replace_list;
    replace_list.push_back(type);
    replace_list.push_back(name);

    QList<QVariant> res_type_name_en;
    if(!database::getInstance()->select_row(res_type_name_en, str, replace_list)){
        qDebug() << "type_en and name_en select failed";
        return false;
    }

    if(res_type_name_en.size() != 2)
        return false;

    QString table_name = res_type_name_en[0].toString() + "_" + res_type_name_en[1].toString();
    str = QString("show tables like '%1'").arg(table_name);
    int ret = database::getInstance()->is_table_exits(str);

    // 表已存在
    if(ret == 1){
        str = QString("insert into %1 (time, price) values(?,?);").arg(table_name);
        replace_list.clear();
        replace_list.push_back(time);
        replace_list.push_back(price);

        if(database::getInstance()->insert_row(str, replace_list)){
            return true;
        }
        else
            return false;
    }
    // 表不存在
    else if(ret == 0){
        str = QString("create table %1"
              "(id int primary key AUTO_INCREMENT, "
              "time nchar(50) not null, "
              "price double not null);")
                .arg(table_name);
        if(!database::getInstance()->create_teble(str))
            return false;

        str = QString("insert into %1 (time, price) values(?,?);").arg(table_name);
        replace_list.clear();
        replace_list.push_back(time);
        replace_list.push_back(price);

        if(database::getInstance()->insert_row(str, replace_list)){
            return true;
        }
        else
            return false;
    }
    // 查询失败
    else if(ret == -1){
        return false;
    }
}

QMap<QString, QList<QVariant>> db_operator::select_price(QString type, QString name)
{
    QMap<QString, QList<QVariant>> res;
    QList<QList<QVariant>> value;

    QString str = "select type_en, name_en from products_category "
                  "where type_chz=? and name_chz=?;";

    QStringList replace_list;
    replace_list.push_back(type);
    replace_list.push_back(name);

    QList<QVariant> res_type_name_en;
    if(!database::getInstance()->select_row(res_type_name_en, str, replace_list)){
        qDebug() << "type_en and name_en select failed";
        return res;
    }

    if(res_type_name_en.size() != 2)
        return res;

    QString table_name = res_type_name_en[0].toString() + "_" + res_type_name_en[1].toString();
    str = QString("show tables like '%1'").arg(table_name);
    int ret = database::getInstance()->is_table_exits(str);

    if(ret <= 0){
        qDebug() << "价格数据表不存在";
        return res;
    }

    str = QString("select time, price from %1;").arg(table_name);

    if(!database::getInstance()->select_rows(value, str)){
        qDebug() << "价格查询失败";
        return res;
    }

    QList<QVariant> time_list;
    QList<QVariant> price_list;

    foreach(auto list, value){
        time_list.push_back(list[0]);
        price_list.push_back(list[1]);
    }

    res["time"] = time_list;
    res["price"] = price_list;

    return res;
}

bool db_operator::input_product(QString type_chz, QString type_en, QString name_chz, QString name_en)
{
    QString str = QString("insert into products_category "
                          "(type_chz, type_en, name_chz, name_en) "
                          "values(?, ?, ?, ?);");
    QStringList replacelist;
    replacelist.push_back(type_chz);
    replacelist.push_back(type_en);
    replacelist.push_back(name_chz);
    replacelist.push_back(name_en);

    if(!database::getInstance()->insert_row(str, replacelist)){
        return false;
    }

    return true;
}


