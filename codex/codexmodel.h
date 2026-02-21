#ifndef CODEXMODEL_H
#define CODEXMODEL_H

#include <QString>
#include <QSqlQuery>

class CodexModel
{
public:
    static QSqlQuery list(QString search_for = "");
    static CodexModel load(int id);
    static CodexModel load(QString name);

    CodexModel(int id, QString name, QString description);
    CodexModel(QString name, QString description);
    CodexModel(QString name);

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

#endif // CODEXMODEL_H
