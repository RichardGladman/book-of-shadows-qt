#include "notemodel.h"

QSqlQuery NoteModel::list(QString searchFor) {

    searchFor = "%" + searchFor + "%";

    QString sql;

    sql = "SELECT id, title FROM notes";

    if (searchFor != nullptr) {
        sql += " WHERE title LIKE ? OR text LIKE ? ";
    }

    sql += " ORDER BY title";

    QSqlQuery query;
    query.prepare(sql);
    query.exec();

    return query;

}

NoteModel NoteModel::load(int id)
{
    NoteModel model {0, "", ""};

    QSqlQuery query;
    query.prepare("SELECT * FROM notes WHERE id=?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.title(query.value(1).toString());
        model.text(query.value(2).toString());
    }

    return model;
}

NoteModel::NoteModel(int id, QString title, QString text) : m_id {id}, m_title {title}, m_text {text} {}
NoteModel::NoteModel(QString title, QString text) : NoteModel {0, title, text} {}
NoteModel::NoteModel(QString title) : NoteModel {0, title, ""} {}

bool NoteModel::save()
{
    QString sql;

    if (m_id == 0) {
        sql = "INSERT INTO notes(title, text) VALUES(?, ?)";
    } else {
        sql = "UPDATE notes SET title=?, text=? WHERE id=?";
    }

    QSqlQuery query;
    query.prepare(sql);
    query.addBindValue(m_title);
    query.addBindValue(m_text);

    if (m_id != 0) {
        query.addBindValue(m_id);
    }

    return query.exec();
}

void NoteModel::remove()
{
    QSqlQuery query;
    query.prepare("DELETE FROM notes WHERE id=?");
    query.addBindValue(m_id);
    query.exec();
}

int NoteModel::id() const
{
    return m_id;
}

QString NoteModel::title() const
{
    return m_title;
}

QString NoteModel::text() const
{
    return m_text;
}

void NoteModel::id(int id)
{
    m_id =id;
}

void NoteModel::title(QString title)
{
    m_title = title;
}

void NoteModel::text(QString text)
{
    m_text = text;
}
