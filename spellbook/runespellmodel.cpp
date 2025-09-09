#include "runespellmodel.h"

QSqlQuery RunespellModel::list()
{
    QSqlQuery query;

    query.prepare("SELECT id title FROM runespells");
    query.exec();

    return query;
}

RunespellModel RunespellModel::load(int id)
{
    RunespellModel model {};

    QSqlQuery query;
    query.prepare("SELECT * FROM runespells WHERE id=?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.title(query.value(1).toString());
        model.description(query.value(2).toString());
        model.glyphs(GlyphModel::list(model.id()));
        model.tags(TagModel::list(model.id()));
    }

    return model;
}

RunespellModel::RunespellModel(QString name, QString description) : m_title {name}, m_description {description} {}
RunespellModel::RunespellModel() : RunespellModel {"", ""} {}

int RunespellModel::id() const
{
    return m_id;
}

QString RunespellModel::title() const
{
    return m_title;
}

QString RunespellModel::description() const
{
    return m_description;
}

QList<GlyphModel> RunespellModel::glyphs() const
{
    return m_glyphs;
}

QList<TagModel> RunespellModel::tags() const
{
    return m_tags;
}

void RunespellModel::id(int i)
{
    m_id = i;
}

void RunespellModel::title(QString title)
{
    m_title = title;
}

void RunespellModel::description(QString description)
{
    m_description = description;
}

void RunespellModel::glyphs(QList<GlyphModel> glyphs)
{
    m_glyphs = glyphs;
}

void RunespellModel::tags(QList<TagModel> tags)
{
    m_tags = tags;
}

void RunespellModel::add_glyph(GlyphModel glyph)
{
    m_glyphs.push_back(glyph);
}

void RunespellModel::add_tag(TagModel tag)
{
    m_tags.push_back(tag);
}

bool RunespellModel::save()
{
    QString sql;

    if (m_id == 0) {
        sql = "INSERT INTO runespells(title, description) VALUES(?, ?)";
    } else {
        sql = "UPDATE runespells SET title = ?, description = ? WHERE id = ?";
    }

    QSqlQuery query;
    query.prepare(sql);

    query.addBindValue(m_title);
    query.addBindValue(m_description);

    if (m_id != 0) {
        query.addBindValue(m_id);
    }

    if (query.exec()) {
        if (m_id == 0) {
            m_id = query.lastInsertId().toInt();
        }

        for (GlyphModel &glyph: m_glyphs) {
            glyph.runespell(m_id);
            if (!glyph.save()) {
                return false;
            }
        }

        for (TagModel &tag: m_tags) {
            tag.runespell(m_id);
            if (!tag.save()) {
                return false;
            }
        }
    } else {
        return false;
    }

    return true;
}

void RunespellModel::remove()
{
    for (GlyphModel &glyph: m_glyphs) {
        glyph.remove();
    }

    for (TagModel &tag: m_tags) {
        tag.remove();
    }

    QSqlQuery query;
    query.prepare("DELETE FROM runespells WHERE id=?");
    query.addBindValue(m_id);
    query.exec();
}
