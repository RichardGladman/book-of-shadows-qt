#ifndef PLANETMODEL_H
#define PLANETMODEL_H

#include <QSqlQuery>
#include <QString>

class PlanetModel
{
public:
    static QSqlQuery list();
    static PlanetModel load(int id);

    PlanetModel(int id, QString name, QString description);
    PlanetModel(QString name, QString description);
    PlanetModel(QString name);

    int id() const;
    QString name() const;
    QString description() const;

    void id(int id);
    void name(QString name);
    void description(QString description);

    bool save();
    void remove();

private:
    int m_id {};
    QString m_name;
    QString m_description;
};

#endif // PLANETMODEL_H
