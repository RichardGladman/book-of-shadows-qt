#include "colourmodel.h"

QSqlQuery ColourModel::list()
{
    QSqlQuery query;

    query.prepare("SELECT id, name FROM colours ORDER BY name");
    query.exec();

    return query;
}

ColourModel ColourModel::load(int id)
{
    ColourModel model {0, "", ""};

    QSqlQuery query;
    query.prepare("SELECT * FROM colours WHERE id=?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.meaning(query.value(2).toString());
    }

    return model;
}

ColourModel::ColourModel(int id, QString name, QString meaning) : m_id {id}, m_name {name}, m_meaning {meaning} {}
ColourModel::ColourModel(QString name, QString meaning) : ColourModel {0, name, meaning} {}
ColourModel::ColourModel(QString name) : ColourModel { 0, name, ""} {}

ColourModel::ColourModel(const ColourModel &source) : ColourModel {source.m_id, source.m_name, source.m_meaning} {}

bool ColourModel::save()
{
    QString sql;

    if (m_id == 0) {
        sql = "INSERT INTO colours(name, meaning) VALUES(?, ?)";
    } else {
        sql = "UPDATE colours SET name=?, meaning=? WHERE id=?";
    }

    QSqlQuery query;
    query.prepare(sql);

    query.addBindValue(m_name);
    query.addBindValue(m_meaning);

    if (m_id != 0) {
        query.addBindValue(m_id);
    }

    return query.exec();
}

int ColourModel::id() const
{
    return m_id;
}

QString ColourModel::name() const
{
    return m_name;
}

QString ColourModel::meaning() const
{
    return m_meaning;
}

void ColourModel::id(int id)
{
    m_id = id;
}

void ColourModel::name(QString name)
{
    m_name = name;
}

void ColourModel::meaning(QString meaning)
{
    m_meaning = meaning;
}
