#ifndef NOTEMODEL_H
#define NOTEMODEL_H

#include <QSqlQuery>
#include <QString>

class NoteModel
{
public:
    static QSqlQuery list(QString searchFor = nullptr);
    static NoteModel load(int id);

    NoteModel(int id, QString title, QString text);
    NoteModel(QString titile, QString text);
    NoteModel(QString title);

    int id() const;
    QString title() const;
    QString text() const;

    void id(int id);
    void title(QString title);
    void text(QString text);

    bool save();
    void remove();

private:
    int m_id;
    QString m_title;
    QString m_text;
};

#endif // NOTEMODEL_H
