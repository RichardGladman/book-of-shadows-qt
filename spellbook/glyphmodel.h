#ifndef GLYPHMODEL_H
#define GLYPHMODEL_H

#include <QSqlQuery>
#include <QString>

class GlyphModel
{
public:
    static QList<GlyphModel> list(int runespell);
    static GlyphModel load(int id);

    GlyphModel(int id, QString name, int runespell, double xpos, double ypos, double width, double height);
    GlyphModel();

    int id();
    QString name();
    int runespell();
    double xpos();
    double ypos();
    double width();
    double height();

    void id(int id);
    void name(QString name);
    void runespell(int runespell);
    void xpos(double xpos);
    void ypos(double ypos);
    void width(double width);
    void height(double height);

    bool save();
    void remove();

private:
    int m_id;
    QString m_name;
    int m_runespell;
    double m_xpos;
    double m_ypos;
    double m_width;
    double m_height;
};

#endif // GLYPHMODEL_H
