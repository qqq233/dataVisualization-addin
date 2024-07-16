#include "database.h"

database *database::m_instance = nullptr;

database::database()
{
    init();
}

database *database::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new database;
        return m_instance;
    }
    return m_instance;
}

database::~database()
{
    if(m_instance != nullptr)
        m_instance = nullptr;
}

bool database::select_rows(QList<QList<QVariant>> &res, QString query)
{
    if(!m_local_db.isOpen())
        return false;

    QSqlQuery sqlquery(m_local_db);
    if(sqlquery.exec(query)){
        while(sqlquery.next()){
            QList<QVariant> list;
            QVariant value;
            int i = 0;
            while((value = sqlquery.value(i)).isValid()){
                list.append(value);
                i++;
            }
            res.append(list);
        }
        return true;
    }
    else{
        return false;
    }
}

bool database::select_row(QList<QVariant> &res, QString query, QStringList replace_list)
{
    QSqlQuery sqlquery(m_local_db);
    sqlquery.prepare(query);
    foreach (auto str, replace_list) {
        sqlquery.addBindValue(str);
    }
    if(sqlquery.exec()){
        if(sqlquery.next()){
            QVariant value;
            int i = 0;
            while((value = sqlquery.value(i)).isValid()){
                res.append(value);
                i++;
            }
            return true;
        }
        return false;
    }
    else{
        return false;
    }
}

bool database::select_row(QList<QVariant> &res, QString query)
{
    QSqlQuery sqlquery(m_local_db);

    m_local_db.transaction();
    if(sqlquery.exec(query)){
        QVariant value;
        int i = 0;
        while((value = sqlquery.value(i)).isValid()){
            res.append(value);
            i++;
        }
    }
    m_local_db.commit();

    if(res.isEmpty())
        return false;
    else
        return true;
}

int database::is_table_exits(QString query)
{
    QSqlQuery sqlquery(m_local_db);
    if(sqlquery.exec(query)){
        if(sqlquery.next()){
            return 1;
        }
        else{
            return 0;
        }
    }
    else
        return -1;
}

bool database::insert_row(QString query, QStringList replace_list)
{
    QSqlQuery sqlquery(m_local_db);
    sqlquery.prepare(query);
    foreach (auto str, replace_list) {
        sqlquery.addBindValue(str);
    }

    m_local_db.transaction();
    if(!sqlquery.exec()){
        return false;
    }
    m_local_db.commit();
}

bool database::create_teble(QString query)
{
    QSqlQuery sqlquery(m_local_db);

    m_local_db.transaction();
    if(!sqlquery.exec(query)){
        return false;
    }
    m_local_db.commit();
}

void database::init()
{
    m_local_db = QSqlDatabase::addDatabase("QODBC", "local_connect");
    m_local_db.setHostName("127.0.0.1");
    m_local_db.setPort(3306);
    m_local_db.setDatabaseName("history_price");
    m_local_db.setUserName("root");
    m_local_db.setPassword("1234");


    if(!m_local_db.open())
        qDebug() << "db open failed";

}
