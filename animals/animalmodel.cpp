#include "animalmodel.h"


QSqlQuery AnimalModel::list()
{
    QSqlQuery query;

    query.prepare("SELECT id, name FROM Animals ORDER BY name");
    query.exec();

    return query;
}

AnimalModel AnimalModel::load(int id)
{
    AnimalModel model {0, "", ""};

    QSqlQuery query;
    query.prepare("SELECT * FROM Animals WHERE id=?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.description(query.value(2).toString());
    }

    return model;
}

AnimalModel AnimalModel::load(QString name)
{
    AnimalModel model {0, "", ""};

    QSqlQuery query;
    query.prepare("SELECT * FROM animals WHERE name=?");
    query.addBindValue(name);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.description(query.value(2).toString());
    }

    return model;
}

AnimalModel::AnimalModel(int id, QString name, QString description) : m_id {id}, m_name {name}, m_description {description} {}
AnimalModel::AnimalModel(QString name, QString description) : AnimalModel {0, name, description} {}
AnimalModel::AnimalModel(QString name) : AnimalModel { 0, name, ""} {}

bool AnimalModel::save()
{
    QString sql;

    if (m_id == 0) {
        sql = "INSERT INTO Animals(name, description) VALUES(?, ?)";
    } else {
        sql = "UPDATE Animals SET name=?, description=? WHERE id=?";
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

void AnimalModel::remove()
{
    QSqlQuery query;
    query.prepare("DELETE FROM Animals WHERE id=?");
    query.addBindValue(m_id);
    query.exec();
}

int AnimalModel::id() const
{
    return m_id;
}

QString AnimalModel::name() const
{
    return m_name;
}

QString AnimalModel::description() const
{
    return m_description;
}

void AnimalModel::id(int id)
{
    m_id = id;
}

void AnimalModel::name(QString name)
{
    m_name = name;
}

void AnimalModel::description(QString description)
{
    m_description = description;
}
