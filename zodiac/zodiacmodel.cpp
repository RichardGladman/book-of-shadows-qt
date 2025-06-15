#include "zodiacmodel.h"

QSqlQuery ZodiacModel::list()
{
    QSqlQuery query;

    query.prepare("SELECT id, name FROM zodiac ORDER BY name");
    query.exec();

    return query;
}

ZodiacModel ZodiacModel::load(int id)
{
    ZodiacModel model(0, "", "");

    QSqlQuery query;
    query.prepare("SELECT * FROM zodiac WHERE id=?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.description(query.value(2).toString());
    }

    return model;
}

ZodiacModel ZodiacModel::load(QString name)
{
    ZodiacModel model(0, "", "");

    QSqlQuery query;
    query.prepare("SELECT * FROM zodiac WHERE name=?");
    query.addBindValue(name);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.description(query.value(2).toString());
    }

    return model;
}

ZodiacModel::ZodiacModel(int id, QString name, QString description) : m_id {id}, m_name {name}, m_description {description} {}
ZodiacModel::ZodiacModel(QString name, QString description) : ZodiacModel {0, name, description} {}
ZodiacModel::ZodiacModel(QString name) : ZodiacModel {0, name, ""} {}

bool ZodiacModel::save()
{
    QString sql;

    if (m_id == 0) {
        sql = "INSERT INTO zodiac(name, description) VALUES(?, ?)";
    } else {
        sql = "UPDATE zodiac SET name=?, description=? WHERE id=?";
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

void ZodiacModel::remove()
{
    QSqlQuery query;
    query.prepare("DELETE FROM zodiac WHERE id=?");
    query.addBindValue(m_id);
    query.exec();
}

int ZodiacModel::id() const
{
    return m_id;
}

QString ZodiacModel::name() const
{
    return m_name;
}

QString ZodiacModel::description() const
{
    return m_description;
}

void ZodiacModel::id(int id)
{
    m_id = id;
}

void ZodiacModel::name(QString name)
{
    m_name = name;
}

void ZodiacModel::description(QString description)
{
    m_description = description;
}
