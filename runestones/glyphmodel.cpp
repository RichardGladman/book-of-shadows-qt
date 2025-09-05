#include "glyphmodel.h"

QList<GlyphModel> GlyphModel::list(int runespell)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM glyphs WHERE runespell = ?");
}

GlyphModel GlyphModel::load(int id)
{
    return GlyphModel {};
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
    return false;
}
void GlyphModel::remove()
{

}
