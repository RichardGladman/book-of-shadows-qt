#ifndef ZODIACMODEL_H
#define ZODIACMODEL_H

#include <QSqlQuery>
#include <QString>

class ZodiacModel
{
public:
    static QSqlQuery list();
    static ZodiacModel load(int id);

    ZodiacModel(int id, QString name, QString description);
    ZodiacModel(QString name, QString description);
    ZodiacModel(QString name);

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

#endif // ZODIACMODEL_H
