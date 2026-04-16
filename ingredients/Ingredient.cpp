#include "Ingredient.h"

QSqlQuery IngredientModel::list(QString search_for)
{
    QSqlQuery query;

    QString select_clause = "SELECT id, name FROM ingredient ";
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

IngredientModel IngredientModel::load(int id)
{
    IngredientModel model {0, "", ""};

    QSqlQuery query;
    query.prepare("SELECT * FROM ingredient WHERE id=?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.description(query.value(2).toString());
    }

    return model;
}

IngredientModel IngredientModel::load(QString name)
{
    IngredientModel model {0, "", ""};

    QSqlQuery query;
    query.prepare("SELECT * FROM ingredient WHERE name=?");
    query.addBindValue(name);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.description(query.value(2).toString());
    }

    return model;
}

IngredientModel::IngredientModel(int id, QString name, QString description) : m_id {id}, m_name {name}, m_description {description} {}
IngredientModel::IngredientModel(QString name, QString description) : IngredientModel {0, name, description} {}
IngredientModel::IngredientModel(QString name) : IngredientModel { 0, name, ""} {}

bool IngredientModel::save()
{
    QString sql;

    if (m_id == 0) {
        sql = "INSERT INTO ingredient(name, description) VALUES(?, ?)";
    } else {
        sql = "UPDATE ingredient SET name=?, description=? WHERE id=?";
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

void IngredientModel::remove()
{
    QSqlQuery query;
    query.prepare("DELETE FROM ingredient WHERE id=?");
    query.addBindValue(m_id);
    query.exec();
}

int IngredientModel::id() const
{
    return m_id;
}

QString IngredientModel::name() const
{
    return m_name;
}

QString IngredientModel::description() const
{
    return m_description;
}

void IngredientModel::id(int id)
{
    m_id = id;
}

void IngredientModel::name(QString name)
{
    m_name = name;
}

void IngredientModel::description(QString description)
{
    m_description = description;
}
