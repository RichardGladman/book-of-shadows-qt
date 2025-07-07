#ifndef RUNESTONEMODEL_H
#define RUNESTONEMODEL_H

#include <QString>

#include "../planets/planetmodel.h"
#include "../polarity/polaritymodel.h"
#include "../zodiac/zodiacmodel.h"

#include "../animals/animalmodel.h"
#include "../colours/colourmodel.h"
#include "../gods/godmodel.h"
#include "../herbs/herbmodel.h"
#include "../trees/treemodel.h"

class RunestoneModel
{
public:
    static QSqlQuery list();
    static RunestoneModel load(int id);

    RunestoneModel(int id, QString name, QString description, int planet_id=0, int polarity_id=0, int zodiac_id=0);

    bool save();
    void saveAnimals(QList<QString> animals);
    void saveColours(QList<QString> colours);
    void saveGods(QList<QString> gods);
    void saveHerbs(QList<QString> herbs);
    void saveTrees(QList<QString> trees);

    int id() const;
    QString name() const;
    QString description() const;
    PlanetModel planet() const;
    PolarityModel polarity() const;
    QList<AnimalModel> animals() const;
    QList<ColourModel> colours() const;
    QList<GodModel> gods() const;
    QList<HerbModel> herbs() const;
    QList<TreeModel> trees() const;

    void id(int id);
    void name(QString name);
    void description(QString description);
    void planet(int planet_id);
    void polarity(int polarity_id);
    void zodiac(int zodiac_id);

    void animals(QList<QString> animals);
    void animals(QList<AnimalModel> animals);
    void colours(QList<QString> colours);
    void colours(QList<ColourModel> colours);
    void gods(QList<QString> gods);
    void gods(QList<GodModel> gods);
    void herbs(QList<QString> herbs);
    void herbs(QList<HerbModel> herbs);
    void trees(QList<QString> trees);
    void trees(QList<TreeModel> trees);

private:
    int m_id;
    QString m_name;
    QString m_description;

    PlanetModel m_planet;
    PolarityModel m_polarity;
    ZodiacModel m_zodiac;

    QList<AnimalModel> m_animals;
    QList<ColourModel> m_colours;
    QList<GodModel> m_gods;
    QList<HerbModel> m_herbs;
    QList<TreeModel> m_trees;
};

#endif // RUNESTONEMODEL_H
