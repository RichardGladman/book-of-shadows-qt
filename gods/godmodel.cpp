#include "godmodel.h"

#include <QSqlQuery>

GodModel::GodModel(int id, QString name, QString description, int polarityId) : m_id {id}, m_name {name}, m_description {description}, m_polarity_id {polarityId} {}
GodModel::GodModel(QString name, QString description, int polarityId) : GodModel {0, name, description, polarityId} {}

GodModel::GodModel(const GodModel &source) : GodModel {source.m_id, source.m_name, source.m_description, source.m_polarity_id} {}

int GodModel::id() const
{
    return m_id;
}

QString GodModel::name() const
{
    return m_name;
}

bool GodModel::save()
{
    QString sql;

    if (m_id == 0) {
        sql = "INSERT INTO gods(name, description, polarity_id) VALUES(?, ?, ?)";
    } else {
        sql = "UPDATE gods SET name=?, description=?, polarity_id=? WHERE id=?";
    }

    QSqlQuery query;
    query.prepare(sql);

    query.addBindValue(m_name);
    query.addBindValue(m_description);
    query.addBindValue(m_polarity_id);

    if (m_id != 0) {
        query.addBindValue(m_id);
    }

    return query.exec();
}

QString GodModel::description() const
{
    return m_description;
}

int GodModel::polarityId() const
{
    return m_polarity_id;
}

void GodModel::id(int id)
{
    m_id = id;
}

void GodModel::name(QString name)
{
    m_name = name;
}

void GodModel::description(QString description)
{
    m_description = description;
}

void GodModel::polarityId(int polarityId)
{
    m_polarity_id = polarityId;
}