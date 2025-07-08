#include "tarotmodel.h"

QSqlQuery TarotModel::list(const QString &term)
{
    QSqlQuery query;

    QString sql = "SELECT id, name FROM tarot ";

    if (term != "") {
        sql += "WHERE name LIKE ? OR meaning LIKE ? ";
    }

    sql += "ORDER BY name";

    query.prepare(sql);

    if (term != "") {
        query.addBindValue("%" + term + "%");
        query.addBindValue("%" + term + "%");
    }

    query.exec();

    return query;
}

TarotModel TarotModel::load(int id)
{
    TarotModel model(0, "", "");

    QSqlQuery query;
    query.prepare("SELECT * FROM tarot WHERE id=?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.description(query.value(2).toString());
        model.planet(query.value(3).toInt());
        model.polarity(query.value(4).toInt());
        model.zodiac(query.value(5).toInt());

        QString arcana = "tarot";
        model.animals(AnimalModel::load(arcana, model.id()));
        model.colours(ColourModel::load(arcana, model.id()));
        model.gods(GodModel::load(arcana, model.id()));
        model.herbs(HerbModel::load(arcana, model.id()));
        model.trees(TreeModel::load(arcana, model.id()));
    }

    return model;
}

TarotModel::TarotModel(int id, QString name, QString description, int planet_id, int polarity_id, int zodiac_id) :
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

bool TarotModel::save()
{
    QString sql;

    if (m_id == 0) {
        sql = "INSERT INTO tarot(name, meaning, planet_id, polarity_id, zodiac_id) VALUES(?,?,?,?,?)";
    } else {
        sql = "UPDATE tarot SET name=?, meaning=?, planet_id=?, polarity_id=?, zodiac_id=? WHERE id=?";
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

void TarotModel::saveAnimals(QList<QString> animals)
{
    QSqlQuery query;
    query.prepare("DELETE FROM tarot_animal WHERE tarot_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("INSERT INTO tarot_animal(tarot_id, animal_id) VALUES(?,?)");
    for (QString &name: animals) {
        AnimalModel animal = AnimalModel::load(name);
        query.addBindValue(m_id);
        query.addBindValue(animal.id());
        query.exec();
    }
}

void TarotModel::saveColours(QList<QString> colours)
{
    QSqlQuery query;
    query.prepare("DELETE FROM tarot_colour WHERE tarot_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("INSERT INTO tarot_colour(tarot_id, colour_id) VALUES(?,?)");
    for (QString &name: colours) {
        ColourModel colour = ColourModel::load(name);
        query.addBindValue(m_id);
        query.addBindValue(colour.id());
        query.exec();
    }
}

void TarotModel::saveGods(QList<QString> gods)
{
    QSqlQuery query;
    query.prepare("DELETE FROM tarot_god WHERE tarot_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("INSERT INTO tarot_god(tarot_id, god_id) VALUES(?,?)");
    for (QString &name: gods) {
        GodModel god = GodModel::load(name);
        query.addBindValue(m_id);
        query.addBindValue(god.id());
        query.exec();
    }
}

void TarotModel::saveHerbs(QList<QString> herbs)
{
    QSqlQuery query;
    query.prepare("DELETE FROM tarot_herb WHERE tarot_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("INSERT INTO tarot_herb(tarot_id, herb_id) VALUES(?,?)");
    for (QString &name: herbs) {
        HerbModel herb = HerbModel::load(name);
        query.addBindValue(m_id);
        query.addBindValue(herb.id());
        query.exec();
    }
}

void TarotModel::saveTrees(QList<QString> trees)
{
    QSqlQuery query;
    query.prepare("DELETE FROM tarot_tree WHERE tarot_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("INSERT INTO tarot_tree(tarot_id, tree_id) VALUES(?,?)");
    for (QString &name: trees) {
        TreeModel tree = TreeModel::load(name);
        query.addBindValue(m_id);
        query.addBindValue(tree.id());
        query.exec();
    }
}

void TarotModel::remove()
{
    QSqlQuery query;

    query.prepare("DELETE FROM tarot_animal WHERE tarot_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("DELETE FROM tarot_colour WHERE tarot_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("DELETE FROM tarot_god WHERE tarot_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("DELETE FROM tarot_herb WHERE tarot_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("DELETE FROM tarot_tree WHERE tarot_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("DELETE FROM tarots WHERE id=?");
    query.addBindValue(m_id);
    query.exec();
}

int TarotModel::id() const
{
    return this->m_id;
}

QString TarotModel::name() const
{
    return this->m_name;
}

QString TarotModel::description() const
{
    return this->m_description;
}

PlanetModel TarotModel::planet() const
{
    return this->m_planet;
}

PolarityModel TarotModel::polarity() const
{
    return this->m_polarity;
}

ZodiacModel TarotModel::zodiac() const
{
    return this->m_zodiac;
}

QList<AnimalModel> TarotModel::animals() const
{
    return this->m_animals;
}

QList<ColourModel> TarotModel::colours() const
{
    return this->m_colours;
}

QList<GodModel> TarotModel::gods() const
{
    return this->m_gods;
}

QList<HerbModel>TarotModel::herbs() const
{
    return this->m_herbs;
}

QList<TreeModel> TarotModel::trees() const
{
    return this->m_trees;
}



void TarotModel::id(int id)
{
    this->m_id = id;
}

void TarotModel::name(QString name)
{
    this->m_name = name;
}

void TarotModel::description(QString description)
{
    this->m_description = description;
}

void TarotModel::planet(int planet_id)
{
    this->m_planet = PlanetModel::load(planet_id);
}

void TarotModel::polarity(int polarity_id)
{
    this->m_polarity = PolarityModel::load(polarity_id);
}

void TarotModel::zodiac(int zodiac_id)
{
    this->m_zodiac = ZodiacModel::load(zodiac_id);
}

void TarotModel::animals(QList<QString> animals)
{
    for (const QString &name: animals) {
        this->m_animals.append(AnimalModel::load(name));
    }
}

void TarotModel::animals(QList<AnimalModel> animals)
{
    this->m_animals = animals;
}

void TarotModel::colours(QList<QString> colours)
{
    for (const QString &name: colours) {
        this->m_colours.append(ColourModel::load(name));
    }
}

void TarotModel::colours(QList<ColourModel> colours)
{
    this->m_colours = colours;
}

void TarotModel::gods(QList<QString> gods)
{
    for (const QString &name: gods) {
        this->m_gods.append(GodModel::load(name));
    }
}

void TarotModel::gods(QList<GodModel> gods)
{
    this->m_gods = gods;
}

void TarotModel::herbs(QList<QString> herbs)
{
    for (const QString &name: herbs) {
        this->m_herbs.append(HerbModel::load(name));
    }
}

void TarotModel::herbs(QList<HerbModel> herbs)
{
    this->m_herbs = herbs;
}

void TarotModel::trees(QList<QString> trees)
{
    for (const QString &name: trees) {
        this->m_trees.append(TreeModel::load(name));
    }
}

void TarotModel::trees(QList<TreeModel> trees)
{
    this->m_trees = trees;
}
