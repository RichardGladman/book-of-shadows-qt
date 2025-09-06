#include "tagmodel.h"

QList<TagModel> TagModel::list(int runespell)
{
    QList<TagModel> tags;
    QSqlQuery query;

    query.prepare("SELECT * FROM tags WHERE runespell = ?");

    if (query.exec()) {
        while (query.next()) {
            TagModel tag {query.value(0).toInt(), query.value(1).toString(), query.value(2).toInt()};
            tags.push_back(tag);
        }
    }

    return tags;
}

TagModel TagModel::load(int id)
{
    TagModel tag {};
    QSqlQuery query;

    query.prepare("SELECT * FROM tags WHERE id = ?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        tag.id(query.value(0).toInt());
        tag.tag(query.value(2).toString());
        tag.runespell(query.value(3).toInt());
    }

    return tag;
}

TagModel::TagModel(int id, QString tag, int runespell) :
    m_id {id}, m_tag {tag}, m_runespell {runespell} {}

TagModel::TagModel() : TagModel (0, "", 0) {}

int TagModel::id() const
{
    return m_id;
}

QString TagModel::tag() const
{
    return m_tag;
}

int TagModel::runespell() const
{
    return m_runespell;
}


void TagModel::id(int id)
{
    m_id = id;
}

void TagModel::tag(QString tag)
{
    m_tag = tag;
}

void TagModel::runespell(int runespell)
{
    m_runespell = runespell;
}

bool TagModel::save()
{
    return false;
}

void TagModel::remove()
{

}
