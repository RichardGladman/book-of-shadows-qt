#include "colourmodel.h"

ColourModel::ColourModel(int id, QString name, QString meaning) : m_id {id}, m_name {name}, m_meaning {meaning} {}
ColourModel::ColourModel(QString name, QString meaning) : ColourModel {0, name, meaning} {}
ColourModel::ColourModel(QString name) : ColourModel { 0, name, ""} {}

ColourModel::ColourModel(const ColourModel &source) : ColourModel {source.m_id, source.m_name, source.m_meaning} {}

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
