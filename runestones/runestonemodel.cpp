#include "runestonemodel.h"

QSqlQuery RunestoneModel::list()
{
    QSqlQuery query;

    query.prepare("SELECT id, name FROM runestones ORDER BY name");
    query.exec();

    return query;
}

RunestoneModel RunestoneModel::load(int id)
{
    RunestoneModel model(0, "", "");

    QSqlQuery query;
    query.prepare("SELECT * FROM runestones WHERE id=?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.description(query.value(2).toString());
        model.planet(query.value(2).toInt());
        model.polarity(query.value(4).toInt());
        model.zodiac(query.value(5).toInt());
    }

    return model;
}

RunestoneModel::RunestoneModel(int id, QString name, QString description) {}

int RunestoneModel::id() const
{
    return this->m_id;
}

QString RunestoneModel::name() const
{
    return this->name();
}

QString RunestoneModel::description() const
{
    return this->m_description;
}

PlanetModel RunestoneModel::planet() const
{
    return this->planet();
}

PolarityModel RunestoneModel::polarity() const
{
    return this->m_polarity;
}

QList<AnimalModel> RunestoneModel::animals() const
{
    return this->m_animals;
}

QList<ColourModel> RunestoneModel::colours() const
{
    return this->m_colours;
}

QList<GodModel> RunestoneModel::gods() const
{
    return this->m_gods;
}

QList<HerbModel>RunestoneModel::herbs() const
{
    return this->m_herbs;
}

QList<TreeModel> RunestoneModel::trees() const
{
    return this->m_trees;
}



void RunestoneModel::id(int id)
{
    this->m_id = id;
}

void RunestoneModel::name(QString name)
{
    this->m_name = name;
}

void RunestoneModel::description(QString description)
{
    this->m_description = description;
}

void RunestoneModel::planet(int planet_id)
{
    this->m_planet = PlanetModel::load(planet_id);
}

void RunestoneModel::polarity(int polarity_id)
{
    this->m_polarity = PolarityModel::load(polarity_id);
}

void RunestoneModel::zodiac(int zodiac_id)
{
    this->m_zodiac = ZodiacModel::load(zodiac_id);
}

void RunestoneModel::animals(QList<QString> animals)
{
    for (const QString &name: animals) {
        this->m_animals.append(AnimalModel::load(name));
    }
}

void RunestoneModel::colours(QList<QString> colours)
{
    for (const QString &name: colours) {
        this->m_colours.append(ColourModel::load(name));
    }
}

void RunestoneModel::gods(QList<QString> gods)
{
    for (const QString &name: gods) {
        this->m_gods.append(GodModel::load(name));
    }
}

void RunestoneModel::herbs(QList<QString> herbs)
{
    for (const QString &name: herbs) {
        this->m_herbs.append(HerbModel::load(name));
    }
}

void RunestoneModel::trees(QList<QString> trees)
{
    for (const QString &name: trees) {
        this->m_trees.append(TreeModel::load(name));
    }
}
