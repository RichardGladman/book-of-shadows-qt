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

        QString arcana = "runestone";
        model.animals(AnimalModel::load(arcana, model.id()));
    }

    return model;
}

RunestoneModel::RunestoneModel(int id, QString name, QString description, int planet_id, int polarity_id, int zodiac_id) :
    m_id {id}, m_name {name}, m_description {description}
{
    m_planet = PlanetModel::load(planet_id);
    m_polarity = PolarityModel::load(polarity_id);
    m_zodiac = ZodiacModel::load(zodiac_id);

    m_animals = QList<AnimalModel> {};
    m_colours = QList<ColourModel> {};
    m_gods = QList<GodModel> {};
    m_herbs = QList<HerbModel> {};
    m_trees = QList<TreeModel> {};
}

bool RunestoneModel::save()
{
    QString sql;

    if (m_id == 0) {
        sql = "INSERT INTO runestones(name, meaning, planet_id, polarity_id, zodiac_id) VALUES(?,?,?,?,?)";
    } else {
        sql = "UPDATE runestones SET name=?, meaning=?, planet_id=?, polarity_id=?, zodiac_id=? WHERE id=?";
    }

    QSqlQuery query;
    query.prepare(sql);

    query.addBindValue(m_name);
    query.addBindValue(m_description);
    query.addBindValue(m_planet.id());
    query.addBindValue(m_polarity.id());
    query.addBindValue(m_zodiac.id());

    if (m_id != 0) {
        query.addBindValue(m_id);
    }

    bool success = query.exec();
    if (m_id == 0 && success) {
        m_id = query.lastInsertId().toInt();
    }

    return success;
}

void RunestoneModel::saveAnimals(QList<QString> animals)
{
    QSqlQuery query;
    query.prepare("DELETE FROM runestone_animal WHERE runestone_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("INSERT INTO runestone_animal(runestone_id, animal_id) VALUES(?,?)");
    for (QString &name: animals) {
        AnimalModel animal = AnimalModel::load(name);
        query.addBindValue(m_id);
        query.addBindValue(animal.id());
        query.exec();
    }
}

void RunestoneModel::saveColours(QList<QString> colours)
{
    QSqlQuery query;
    query.prepare("DELETE FROM runestone_colour WHERE runestone_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("INSERT INTO runestone_colour(runestone_id, colour_id) VALUES(?,?)");
    for (QString &name: colours) {
        ColourModel colour = ColourModel::load(name);
        query.addBindValue(m_id);
        query.addBindValue(colour.id());
        query.exec();
    }
}

void RunestoneModel::saveGods(QList<QString> gods)
{
    QSqlQuery query;
    query.prepare("DELETE FROM runestone_god WHERE runestone_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("INSERT INTO runestone_god(runestone_id, god_id) VALUES(?,?)");
    for (QString &name: gods) {
        GodModel god = GodModel::load(name);
        query.addBindValue(m_id);
        query.addBindValue(god.id());
        query.exec();
    }
}

void RunestoneModel::saveHerbs(QList<QString> herbs)
{
    QSqlQuery query;
    query.prepare("DELETE FROM runestone_herb WHERE runestone_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("INSERT INTO runestone_herb(runestone_id, herb_id) VALUES(?,?)");
    for (QString &name: herbs) {
        HerbModel herb = HerbModel::load(name);
        query.addBindValue(m_id);
        query.addBindValue(herb.id());
        query.exec();
    }
}

void RunestoneModel::saveTrees(QList<QString> trees)
{
    QSqlQuery query;
    query.prepare("DELETE FROM runestone_tree WHERE runestone_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("INSERT INTO runestone_tree(runestone_id, tree_id) VALUES(?,?)");
    for (QString &name: trees) {
        TreeModel tree = TreeModel::load(name);
        query.addBindValue(m_id);
        query.addBindValue(tree.id());
        query.exec();
    }
}

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

void RunestoneModel::animals(QList<AnimalModel> animals)
{
    this->m_animals = animals;
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
