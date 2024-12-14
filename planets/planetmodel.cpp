#include "planetmodel.h"

PlanetModel::PlanetModel(int id, QString name, QString description) : m_id {id}, m_name {name}, m_description {description} {}
PlanetModel::PlanetModel(QString name, QString description) : PlanetModel { 0, name, description } {}
PlanetModel::PlanetModel(QString name) : PlanetModel { 0, name, ""} {}

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
