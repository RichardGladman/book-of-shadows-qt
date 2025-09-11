#ifndef RUNESPELLMODEL_H
#define RUNESPELLMODEL_H

#include <QSqlQuery>
#include <QString>

#include "glyphmodel.h"
#include "tagmodel.h"

class RunespellModel
{
public:
    static QSqlQuery list();
    static RunespellModel load(int id);

    RunespellModel(int id, QString name, QString description);
    RunespellModel();

    int id() const;
    QString title() const;
    QString description() const;

    QList<GlyphModel> glyphs() const;
    QList<TagModel> tags() const;

    void id(int i);
    void title(QString title);
    void description(QString description);
    void glyphs(QList<GlyphModel> glyphs);
    void tags(QList<TagModel> tags);

    void add_glyph(GlyphModel glyph);
    void add_tag(TagModel tag);

    bool save();
    void remove();

private:
    int m_id {};
    QString m_title;
    QString m_description;

    QList<GlyphModel> m_glyphs;
    QList<TagModel> m_tags;
};

#endif // RUNESPELLMODEL_H
