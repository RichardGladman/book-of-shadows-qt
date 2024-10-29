#ifndef GODMODEL_H
#define GODMODEL_H

#include <QSqlQuery>
#include <QString>

class GodModel
{
public:
    static QSqlQuery list();

    GodModel(int id, QString name, QString description, int polarityId);
    GodModel(QString name, QString description, int polarityId);

    GodModel(const GodModel &source);

    int id() const;
    QString name() const;
    QString description() const;
    int polarityId() const;

    void id(int id);
    void name(QString name);
    void description(QString description);
    void polarityId(int polarityId);

    bool save();

private:
    int m_id;
    QString m_name;
    QString m_description;
    int m_polarity_id;
};

#endif // GODMODEL_H
