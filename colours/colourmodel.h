#ifndef COLOURMODEL_H
#define COLOURMODEL_H

#include <QSqlQuery>
#include <QString>

class ColourModel
{
public:
    static QSqlQuery list();
    static ColourModel load(int id);

    ColourModel(int id, QString name, QString meaning);
    ColourModel(QString name, QString meaning);
    ColourModel(QString name);

    ColourModel(const ColourModel &source);

    int id() const;
    QString name() const;
    QString meaning() const;

    void id(int id);
    void name(QString name);
    void meaning(QString meaning);

    bool save();

private:
    int m_id;
    QString m_name;
    QString m_meaning;
};

#endif // COLOURMODEL_H
