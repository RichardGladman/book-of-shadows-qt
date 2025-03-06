#include "planetmodel.h"

QSqlQuery PlanetModel::list()
{
    QSqlQuery query;
    query.prepare("SELECT id, name FROM planets ORDER BY name");
    query.exec();

    return query;
}

PlanetModel PlanetModel::load(int id)
{
    PlanetModel model {0, "", ""};

    QSqlQuery query;
    query.prepare("SELECT * FROM planets WHERE id=?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.description(query.value(2).toString());
    }

    return model;
}

PlanetModel::PlanetModel(int id, QString name, QString description) : m_id {id}, m_name {name}, m_description {description} {}
PlanetModel::PlanetModel(QString name, QString description) : PlanetModel { 0, name, description } {}
PlanetModel::PlanetModel(QString name) : PlanetModel { 0, name, ""} {}

bool PlanetModel::save()
{
    QString sql;

    if (m_id == 0) {
        sql = "INSERT INTO planets(name, description) VALUES(?, ?)";
    } else {
        sql = "UPDATE planets SET name=?, description=? WHERE id=?";
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

void PlanetModel::remove()
{
    QSqlQuery query;
    query.prepare("DELETE FROM planets WHERE id=?");
    query.addBindValue(m_id);
    query.exec();
}

int PlanetModel::id() const
{
    return m_id;
}

QString PlanetModel::name() const
{
    return m_name;
}

QString PlanetModel::description() const
{
    return m_description;
}

void PlanetModel::id(int id)
{
    m_id = id;
}

void PlanetModel::name(QString name)
{
    m_name = name;
}

void PlanetModel::description(QString description)
{
    m_description = description;
}
