#include "glyphmodel.h"

QList<GlyphModel> GlyphModel::list(int runespell)
{
    QList<GlyphModel> glyphs;
    QSqlQuery query;
    query.prepare("SELECT * FROM glyphs WHERE runespell = ?");
    query.addBindValue(runespell);

    if (query.exec()) {
        while (query.next()) {
            GlyphModel glyph {query.value(0).toInt(), query.value(1).toString(), query.value(2).toInt(),
                                query.value(3).toDouble(), query.value(4).toDouble(), query.value(5).toDouble(), query.value(6).toDouble()};
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
        glyph.xpos(query.value(3).toDouble());
        glyph.ypos(query.value(4).toDouble());
        glyph.width(query.value(5).toDouble());
        glyph.height(query.value(6).toDouble());
    }

    return glyph;
}

GlyphModel::GlyphModel(int id, QString name, int runespell, double xpos, double ypos, double width, double height) :
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

double GlyphModel::xpos()
{
    return m_xpos;
}

double GlyphModel::ypos()
{
    return m_ypos;
}

double GlyphModel::width()
{
    return m_width;
}

double GlyphModel::height()
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

void GlyphModel::xpos(double xpos)
{
    m_xpos = xpos;
}

void GlyphModel::ypos(double ypos)
{
    m_ypos = ypos;
}

void GlyphModel::width(double width)
{
    m_width = width;
}

void GlyphModel::height(double height)
{
    m_height = height;
}

bool GlyphModel::save()
{
    QString sql;

    if (m_id == 0) {
        sql = "INSERT INTO glyphs(name, runespell, x_pos, y_pos, width, height) VALUES(?, ?, ?, ?, ?, ?)";
    } else {
        sql = "UPDATE glyphs SET name=?, runespell=?, x_pos=?, y_pos=?, width=?, height=? WHERE id=?";
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
