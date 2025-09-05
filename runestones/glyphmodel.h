#ifndef GLYPHMODEL_H
#define GLYPHMODEL_H

#include <QSqlQuery>
#include <QString>

class GlyphModel
{
public:
    static QList<GlyphModel> list(int runespell);
    static GlyphModel load(int id);

    GlyphModel(int id, QString name, int runespell, int xpos, int ypos, int width, int height);
    GlyphModel();

    int id();
    QString name();
    int runespell();
    int xpos();
    int ypos();
    int width();
    int height();

    void id(int id);
    void name(QString name);
    void runespell(int runespell);
    void xpos(int xpos);
    void ypos(int ypos);
    void width(int width);
    void height(int height);

    bool save();
    void remove();

private:
    int m_id;
    QString m_name;
    int m_runespell;
    int m_xpos;
    int m_ypos;
    int m_width;
    int m_height;
};

#endif // GLYPHMODEL_H
