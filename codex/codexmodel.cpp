#include "codexmodel.h"


QSqlQuery CodexModel::list(QString search_for)
{
    QSqlQuery query;

    QString select_clause = "SELECT id, name FROM codex ";
    QString order_clause = "ORDER BY name";
    QString where_clause;
    if (search_for == "") {
        where_clause = "";
    } else {
        where_clause = "WHERE name LIKE ? ";
    }

    query.prepare(select_clause + where_clause + order_clause);
    if (search_for != "") {
        query.addBindValue("%" + search_for.trimmed() + "%");
    }

    query.exec();

    return query;
}

CodexModel CodexModel::load(int id)
{
    CodexModel model {0, "", ""};

    QSqlQuery query;
    query.prepare("SELECT * FROM codex WHERE id=?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.description(query.value(2).toString());
    }

    return model;
}

CodexModel CodexModel::load(QString name)
{
    CodexModel model {0, "", ""};

    QSqlQuery query;
    query.prepare("SELECT * FROM codex WHERE name=?");
    query.addBindValue(name);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.description(query.value(2).toString());
    }

    return model;
}

CodexModel::CodexModel(int id, QString name, QString description) : m_id {id}, m_name {name}, m_description {description} {}
CodexModel::CodexModel(QString name, QString description) : CodexModel {0, name, description} {}
CodexModel::CodexModel(QString name) : CodexModel { 0, name, ""} {}

bool CodexModel::save()
{
    QString sql;

    if (m_id == 0) {
        sql = "INSERT INTO codex(name, description) VALUES(?, ?)";
    } else {
        sql = "UPDATE codex SET name=?, description=? WHERE id=?";
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

void CodexModel::remove()
{
    QSqlQuery query;
    query.prepare("DELETE FROM codex WHERE id=?");
    query.addBindValue(m_id);
    query.exec();
}

int CodexModel::id() const
{
    return m_id;
}

QString CodexModel::name() const
{
    return m_name;
}

QString CodexModel::description() const
{
    return m_description;
}

void CodexModel::id(int id)
{
    m_id = id;
}

void CodexModel::name(QString name)
{
    m_name = name;
}

void CodexModel::description(QString description)
{
    m_description = description;
}
