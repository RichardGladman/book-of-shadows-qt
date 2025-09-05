#ifndef RUNESPELLMODEL_H
#define RUNESPELLMODEL_H

#include <QSqlQuery>
#include <QString>

#include "glyphmodel.h"

class RunespellModel
{
public:
    static QSqlQuery list();
    static RunespellModel load(int id);
    RunespellModel();

    int id() const;
    QString title() const;
    QString description() const;

    QList<GlyphModel> glyphs() const;

    void id(int i);
    void title(QString title);
    void description(QString description);

    void add_glyph(GlyphModel glyph);

    bool save();
    void remove();

private:
    int m_id;
    QString m_title;
    QString m_description;

    QList<GlyphModel> m_glyphs;
};

#endif // RUNESPELLMODEL_H
