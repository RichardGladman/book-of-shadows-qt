#ifndef ANIMALMODEL_H
#define ANIMALMODEL_H

#include <QSqlQuery>
#include <QString>

class AnimalModel
{
public:
    static QSqlQuery list();
    static AnimalModel load(int id);

    AnimalModel(int id, QString name, QString description);
    AnimalModel(QString name, QString description);
    AnimalModel(QString name);

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

#endif // ANIMALMODEL_H
