#ifndef RUNESPELLMODEL_H
#define RUNESPELLMODEL_H

#include <QSqlQuery>
#include <QString>

class RunespellModel
{
public:
    static QSqlQuery list();
    static RunespellModel load(int id);
    RunespellModel();

    int id() const;
    QString title() const;
    QString description() const;

    void id(int i);
    void title(QString title);
    void description(QString description);

    void save();
    void remove();

private:
    int m_id;
    QString m_title;
    QString m_description;
};

#endif // RUNESPELLMODEL_H
