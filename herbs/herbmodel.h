#ifndef HERBMODEL_H
#define HERBMODEL_H

#include <QSqlQuery>
#include <QString>

class HerbModel
{
public:
    static QSqlQuery list();
    static HerbModel load(int id);

    HerbModel(int id, QString name, QString description);
    HerbModel(QString name, QString description);

    int id() const;
    QString name() const;
    QString description() const;

    void id(int id);
    void name(QString name);
    void description(QString description);

    bool save();

private:
    int m_id;
    QString m_name;
    QString m_description;
};

#endif // HERBMODEL_H
