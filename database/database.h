#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>

class database
{
public:
    static database *getInstance();
    virtual ~database();

    ///
    /// \brief select_rows 查询多个字段
    /// \param res
    /// \param query
    /// \return
    ///
    bool select_rows(QList<QList<QVariant>> &res, QString query);

    bool select_row(QList<QVariant> &res, QString query, QStringList replace_list);

    bool select_row(QList<QVariant> &res, QString query);

    int is_table_exits(QString query);

    bool insert_row(QString query, QStringList replace_list);

    bool create_teble(QString query);

private:
    database();
    void init();

    static database *m_instance;

    QSqlDatabase m_local_db;
};

#endif // DATABASE_H
