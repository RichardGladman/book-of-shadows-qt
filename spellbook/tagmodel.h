#ifndef TAGMODEL_H
#define TAGMODEL_H

#include <QSqlQuery>
#include <QString>

// CREATE TABLE IF NOT EXISTS tags (id INTEGER PRIMARY KEY, tag VARCHAR(255), runespell INTEGER)
class TagModel
{
public:
    static QList<TagModel> list(int runespell);
    static TagModel load(int id);

    TagModel(int id, QString tag, int runespell);
    TagModel();

    int id() const;
    QString tag() const;
    int runespell() const;

    void id(int id);
    void tag(QString tag);
    void runespell(int runespell);

    bool save();
    void remove();

private:
    int m_id;
    QString m_tag;
    int m_runespell;
};

#endif // TAGMODEL_H
