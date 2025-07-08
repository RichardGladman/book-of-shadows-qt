#include "treemodel.h"

QSqlQuery TreeModel::list()
{
    QSqlQuery query;

    query.prepare("SELECT id, name FROM trees ORDER BY name");
    query.exec();

    return query;
}

TreeModel TreeModel::load(int id)
{
    TreeModel model(0, "", "");

    QSqlQuery query;
    query.prepare("SELECT * FROM trees WHERE id=?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.description(query.value(2).toString());
    }

    return model;
}

TreeModel TreeModel::load(QString name)
{
    TreeModel model(0, "", "");

    QSqlQuery query;
    query.prepare("SELECT * FROM trees WHERE name=?");
    query.addBindValue(name);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.description(query.value(2).toString());
    }

    return model;
}

QList<TreeModel> TreeModel::load(QString &arcana, int id)
{
    QList<TreeModel> trees;
    QString sql;

    if (arcana == "runestone") {
        sql = "SELECT t2.* FROM runestone_tree t1 INNER JOIN trees t2 ON t1.tree_id = t2.id WHERE t1.runestone_id = ?";
    } else if (arcana == "tarot") {
        sql = "SELECT t2.* FROM tarot_tree t1 INNER JOIN trees t2 ON t1.tree_id = t2.id WHERE t1.tarot_id = ?";
    } else if (arcana == "crystal") {
        sql = "SELECT t2.* FROM crystal_tree t1 INNER JOIN trees t2 ON t1.tree_id = t2.id WHERE t1.tree_id = ?";
    }

    QSqlQuery query;
    query.prepare(sql);
    query.addBindValue(id);

    if (query.exec()) {
        while (query.next()) {
            TreeModel model = TreeModel(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString());
            trees.append(model);
        }
    }

    return trees;
}

TreeModel::TreeModel(int id, QString name, QString description) :
    m_id {id}, m_name {name}, m_description {description} {}
TreeModel::TreeModel(QString name, QString description) : TreeModel(0, name, description) {}
TreeModel::TreeModel(QString name) : TreeModel(0, name, "") {};

bool TreeModel::save()
{
    QString sql;

    if (m_id == 0) {
        sql = "INSERT INTO trees(name, description) VALUES(?, ?)";
    } else {
        sql = "UPDATE trees SET name=?, description=? WHERE id=?";
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

void TreeModel::remove()
{
    QSqlQuery query;
    query.prepare("DELETE FROM trees WHERE id=>");
    query.addBindValue(m_id);
    query.exec();
}

int TreeModel::id() const
{
    return m_id;
}

QString TreeModel::name() const
{
    return m_name;
}

QString TreeModel::description() const
{
    return m_description;
}

void TreeModel::id(int id)
{
    m_id = id;
}

void TreeModel::name(QString name)
{
    m_name = name;
}

void TreeModel::description(QString description)
{
    m_description = description;
}
