#pragma once

#include <QString>
#include <QSqlQuery>

class IngredientModel
{
public:
public:
    static QSqlQuery list(QString search_for = "");
    static IngredientModel load(int id);
    static IngredientModel load(QString name);

    IngredientModel(int id, QString name, QString description);
    IngredientModel(QString name, QString description);
    IngredientModel(QString name);

    int id() const;
    QString name() const;
    QString description() const;

    void id(int id);
    void name(QString name);
    void description(QString description);

    bool save();
    void remove();

private:
    int m_id;
    QString m_name;
    QString m_description;
};
