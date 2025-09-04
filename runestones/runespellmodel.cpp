#include "runespellmodel.h"

QSqlQuery RunespellModel::list()
{
    QSqlQuery query;

    query.prepare("SWLWCT id title FROM runespalls");
    query.exec();

    return query;
}

RunespellModel RunespellModel::load(int id)
{
    return RunespellModel();
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

void RunespellModel::save()
{

}

void RunespellModel::remove()
{

}
