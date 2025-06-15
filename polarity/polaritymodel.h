#ifndef POLARITYMODEL_H
#define POLARITYMODEL_H

#include <QString>
#include <QSqlQuery>

class PolarityModel
{
public:
    static QSqlQuery list();
    static PolarityModel load(int id);
    static PolarityModel load(QString name);

    PolarityModel(QString name, QString meaning);
    PolarityModel(QString name, QString meaning, QString image);
    PolarityModel(int id, QString name, QString meaning, QString image);
    PolarityModel(const PolarityModel &source);

    int id() const;
    QString name() const;
    QString meaning() const;
    QString image() const;

    void id(const int id);
    void name(const QString &name);
    void meaning(const QString &meaning);
    void image(const QString &image);

    bool operator==(const PolarityModel &rhs) const;

    bool save();
    void remove();

private:
    int m_id {0};
    QString m_name {};
    QString m_meaning {};
    QString m_image {};

};

#endif // POLARITYMODEL_H
