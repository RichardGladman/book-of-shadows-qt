#include "herbmodel.h"

QSqlQuery HerbModel::list()
{
    QSqlQuery query;

    query.prepare("SELECT id, name FROM herbs ORDER BY name");
    query.exec();

    return query;
}

HerbModel HerbModel::load(int id)
{
    HerbModel model {0, "", ""};

    QSqlQuery query;
    query.prepare("SELECT * FROM herbs WHERE id = ?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.description(query.value(2).toString());
    }

    return model;
}

HerbModel::HerbModel(int id, QString name, QString description) : m_id {id}, m_name {name}, m_description {description} {}
HerbModel::HerbModel(QString name, QString description) : HerbModel {0, name, description} {}

bool HerbModel::save()
{
    QSqlQuery query;

    if (m_id == 0) {
        query.prepare("INSERT INTO herbs(name, description) VALUES(?, ?)");
    } else {
        query.prepare("UPDATE herbs SET name=?, description=? WHERE id=?");
    }

    query.addBindValue(m_name);
    query.addBindValue(m_description);

    if (m_id != 0) {
        query.addBindValue(m_id);
    }

    return query.exec();
}

int HerbModel::id() const
{
    return m_id;
}

QString HerbModel::name() const
{
    return m_name;
}

QString HerbModel::description() const
{
    return m_description;
}

void HerbModel::id(int id)
{
    m_id = id;
}

void HerbModel::name(QString name)
{
    m_name = name;
}

void HerbModel::description(QString description)
{
    m_description = description;
}
