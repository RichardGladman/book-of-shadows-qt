#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QSqlQuery>
#include <QString>

class TreeModel
{
public:
    static QSqlQuery list();
    static TreeModel load(int id);
    static TreeModel load(QString name);

    TreeModel(int id, QString name, QString description);
    TreeModel(QString name, QString description);
    TreeModel(QString name);

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

#endif // TREEMODEL_H
