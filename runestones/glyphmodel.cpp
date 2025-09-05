#include "glyphmodel.h"

QList<GlyphModel> GlyphModel::list(int runespell)
{
    QList<GlyphModel> glyphs;
    QSqlQuery query;
    query.prepare("SELECT * FROM glyphs WHERE runespell = ?");

    if (query.exec()) {
        while (query.next()) {
            GlyphModel glyph {query.value(0).toInt(), query.value(1).toString(), query.value(2).toInt(),
                                query.value(3).toInt(), query.value(4).toInt(), query.value(5).toInt(), query.value(6).toInt()};
            glyphs.push_back(glyph);
        }
    }

    return glyphs;
}

GlyphModel GlyphModel::load(int id)
{
    GlyphModel glyph {};
    QSqlQuery query;

    query.prepare("SELECT * FROM glyphs WHERE id = ?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        glyph.id(query.value(0).toInt());
        glyph.name(query.value(1).toString());
        glyph.runespell(query.value(2).toInt());
        glyph.xpos(query.value(3).toInt());
        glyph.ypos(query.value(4).toInt());
        glyph.width(query.value(5).toInt());
        glyph.height(query.value(6).toInt());
    }

    return glyph;
}

GlyphModel::GlyphModel(int id, QString name, int runespell, int xpos, int ypos, int width, int height) :
    m_id {id}, m_name {name}, m_runespell {runespell}, m_xpos {xpos}, m_ypos {ypos}, m_width {width}, m_height { height} {}

GlyphModel::GlyphModel() : GlyphModel(0, "", 0, 0, 0, 0, 0) {}

int GlyphModel::id()
{
    return m_id;
}

QString GlyphModel::name()
{
    return m_name;
}

int GlyphModel::runespell()
{
    return m_runespell;
}

int GlyphModel::xpos()
{
    return m_xpos;
}

int GlyphModel::ypos()
{
    return m_ypos;
}

int GlyphModel::width()
{
    return m_width;
}

int GlyphModel::height()
{
    return m_height;
}

void GlyphModel::id(int id)
{
    m_id = id;
}

void GlyphModel::name(QString name)
{
    m_name = name;
}

void GlyphModel::runespell(int runespell)
{
    m_runespell = runespell;
}

void GlyphModel::xpos(int xpos)
{
    m_xpos = xpos;
}

void GlyphModel::ypos(int ypos)
{
    m_ypos = ypos;
}

void GlyphModel::width(int width)
{
    m_width = width;
}

void GlyphModel::height(int height)
{
    m_height = height;
}

bool GlyphModel::save()
{
    QString sql;

    if (m_id == 0) {
        sql = "INSERT INTO glyphs(name, runespell, xpos, ypos, width, height) VALUES(?, ?, ?, ?, ?, ?)";
    } else {
        sql = "UPDATE glyphs SET name=?, runespell=?, xpos=?, ypos=?, width=?, height=? WHERE id=?";
    }

    QSqlQuery query;
    query.prepare(sql);

    query.addBindValue(m_name);
    query.addBindValue(m_runespell);
    query.addBindValue(m_xpos);
    query.addBindValue(m_ypos);
    query.addBindValue(m_width);
    query.addBindValue(m_height);

    if (m_id != 0) {
        query.addBindValue(m_id);
    }

    return query.exec();
}
void GlyphModel::remove()
{
    QSqlQuery query;
    query.prepare("DELETE FROM glyphs WHERE id=?");
    query.addBindValue(m_id);
    query.exec();
}
