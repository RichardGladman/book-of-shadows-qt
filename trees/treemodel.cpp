#include "treemodel.h"

QSqlQuery TreeModel::list()
{
    QSqlQuery query;

    query.prepare("SELECT id, name FROM trees ORDER BY name");
    query.exec();

    return query;
}

TreeModel TreeModel::load(int id)
{
    TreeModel model(0, "", "");

    QSqlQuery query;
    query.prepare("SELECT * FROM trees WHERE id=?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.description(query.value(2).toString());
    }

    return model;
}

TreeModel TreeModel::load(QString name)
{
    TreeModel model(0, "", "");

    QSqlQuery query;
    query.prepare("SELECT * FROM trees WHERE name=?");
    query.addBindValue(name);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.description(query.value(2).toString());
    }

    return model;
}

TreeModel::TreeModel(int id, QString name, QString description) :
    m_id {id}, m_name {name}, m_description {description} {}
TreeModel::TreeModel(QString name, QString description) : TreeModel(0, name, description) {}
TreeModel::TreeModel(QString name) : TreeModel(0, name, "") {};

bool TreeModel::save()
{
    QString sql;

    if (m_id == 0) {
        sql = "INSERT INTO trees(name, description) VALUES(?, ?)";
    } else {
        sql = "UPDATE trees SET name=?, description=? WHERE id=?";
    }

    QSqlQuery query;
    query.prepare(sql);

    query.addBindValue(m_name);
    query.addBindValue(m_description);

    if (m_id != 0) {
        query.addBindValue(m_id);
    }

    return query.exec();
}

void TreeModel::remove()
{
    QSqlQuery query;
    query.prepare("DELETE FROM trees WHERE id=>");
    query.addBindValue(m_id);
    query.exec();
}

int TreeModel::id() const
{
    return m_id;
}

QString TreeModel::name() const
{
    return m_name;
}

QString TreeModel::description() const
{
    return m_description;
}

void TreeModel::id(int id)
{
    m_id = id;
}

void TreeModel::name(QString name)
{
    m_name = name;
}

void TreeModel::description(QString description)
{
    m_description = description;
}
