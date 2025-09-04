#include "runespellmodel.h"

QSqlQuery RunespellModel::list()
{
    QSqlQuery query;

    query.prepare("SELECT id title FROM runespells");
    query.exec();

    return query;
}

RunespellModel RunespellModel::load(int id)
{
    RunespellModel model {};

    QSqlQuery query;
    query.prepare("SELECT * FROM runespells WHERE id=?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.title(query.value(1).toString());
        model.description(query.value(2).toString());
    }

    return model;
}

RunespellModel::RunespellModel() {}

int RunespellModel::id() const
{
    return m_id;
}

QString RunespellModel::title() const
{
    return m_title;
}

QString RunespellModel::description() const
{
    return m_description;
}

void RunespellModel::id(int i)
{
    m_id = i;
}

void RunespellModel::title(QString title)
{
    m_title = title;
}

void RunespellModel::description(QString description)
{
    m_description = description;
}

bool RunespellModel::save()
{
    QString sql;

    if (m_id == 0) {
        sql = "INSERT INTO runespells(title, description) VALUES(?, ?)";
    } else {
        sql = "UPDATE runespells SET title = ?, description = ? WHERE id = ?";
    }

    QSqlQuery query;
    query.prepare(sql);

    query.addBindValue(m_title);
    query.addBindValue(m_description);

    if (m_id != 0) {
        query.addBindValue(m_id);
    }


}

void RunespellModel::remove()
{

}
