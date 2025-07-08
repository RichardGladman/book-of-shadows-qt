#include "crystalmodel.h"

QSqlQuery CrystalModel::list(const QString &term)
{
    QSqlQuery query;

    QString sql = "SELECT id, name FROM crystals ";

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

CrystalModel CrystalModel::load(int id)
{
    CrystalModel model(0, "", "");

    QSqlQuery query;
    query.prepare("SELECT * FROM crystals WHERE id=?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.description(query.value(2).toString());
        model.planet(query.value(3).toInt());
        model.polarity(query.value(4).toInt());
        model.zodiac(query.value(5).toInt());

        QString arcana = "crystal";
        model.animals(AnimalModel::load(arcana, model.id()));
        model.colours(ColourModel::load(arcana, model.id()));
        model.gods(GodModel::load(arcana, model.id()));
        model.herbs(HerbModel::load(arcana, model.id()));
        model.trees(TreeModel::load(arcana, model.id()));
    }

    return model;
}

CrystalModel::CrystalModel(int id, QString name, QString description, int planet_id, int polarity_id, int zodiac_id) :
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

bool CrystalModel::save()
{
    QString sql;

    if (m_id == 0) {
        sql = "INSERT INTO crystals(name, meaning, planet_id, polarity_id, zodiac_id) VALUES(?,?,?,?,?)";
    } else {
        sql = "UPDATE crystals SET name=?, meaning=?, planet_id=?, polarity_id=?, zodiac_id=? WHERE id=?";
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

void CrystalModel::saveAnimals(QList<QString> animals)
{
    QSqlQuery query;
    query.prepare("DELETE FROM crystal_animal WHERE Crystal_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("INSERT INTO crystal_animal(Crystal_id, animal_id) VALUES(?,?)");
    for (QString &name: animals) {
        AnimalModel animal = AnimalModel::load(name);
        query.addBindValue(m_id);
        query.addBindValue(animal.id());
        query.exec();
    }
}

void CrystalModel::saveColours(QList<QString> colours)
{
    QSqlQuery query;
    query.prepare("DELETE FROM crystal_colour WHERE Crystal_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("INSERT INTO crystal_colour(Crystal_id, colour_id) VALUES(?,?)");
    for (QString &name: colours) {
        ColourModel colour = ColourModel::load(name);
        query.addBindValue(m_id);
        query.addBindValue(colour.id());
        query.exec();
    }
}

void CrystalModel::saveGods(QList<QString> gods)
{
    QSqlQuery query;
    query.prepare("DELETE FROM crystal_god WHERE Crystal_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("INSERT INTO crystal_god(Crystal_id, god_id) VALUES(?,?)");
    for (QString &name: gods) {
        GodModel god = GodModel::load(name);
        query.addBindValue(m_id);
        query.addBindValue(god.id());
        query.exec();
    }
}

void CrystalModel::saveHerbs(QList<QString> herbs)
{
    QSqlQuery query;
    query.prepare("DELETE FROM crystal_herb WHERE Crystal_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("INSERT INTO crystal_herb(Crystal_id, herb_id) VALUES(?,?)");
    for (QString &name: herbs) {
        HerbModel herb = HerbModel::load(name);
        query.addBindValue(m_id);
        query.addBindValue(herb.id());
        query.exec();
    }
}

void CrystalModel::saveTrees(QList<QString> trees)
{
    QSqlQuery query;
    query.prepare("DELETE FROM crystal_tree WHERE Crystal_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("INSERT INTO crystal_tree(Crystal_id, tree_id) VALUES(?,?)");
    for (QString &name: trees) {
        TreeModel tree = TreeModel::load(name);
        query.addBindValue(m_id);
        query.addBindValue(tree.id());
        query.exec();
    }
}

void CrystalModel::remove()
{
    QSqlQuery query;

    query.prepare("DELETE FROM crystal_animal WHERE Crystal_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("DELETE FROM crystal_colour WHERE Crystal_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("DELETE FROM crystal_god WHERE Crystal_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("DELETE FROM crystal_herb WHERE Crystal_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("DELETE FROM crystal_tree WHERE Crystal_id=?");
    query.addBindValue(m_id);
    query.exec();

    query.prepare("DELETE FROM crystals WHERE id=?");
    query.addBindValue(m_id);
    query.exec();
}

int CrystalModel::id() const
{
    return this->m_id;
}

QString CrystalModel::name() const
{
    return this->m_name;
}

QString CrystalModel::description() const
{
    return this->m_description;
}

PlanetModel CrystalModel::planet() const
{
    return this->m_planet;
}

PolarityModel CrystalModel::polarity() const
{
    return this->m_polarity;
}

ZodiacModel CrystalModel::zodiac() const
{
    return this->m_zodiac;
}

QList<AnimalModel> CrystalModel::animals() const
{
    return this->m_animals;
}

QList<ColourModel> CrystalModel::colours() const
{
    return this->m_colours;
}

QList<GodModel> CrystalModel::gods() const
{
    return this->m_gods;
}

QList<HerbModel>CrystalModel::herbs() const
{
    return this->m_herbs;
}

QList<TreeModel> CrystalModel::trees() const
{
    return this->m_trees;
}



void CrystalModel::id(int id)
{
    this->m_id = id;
}

void CrystalModel::name(QString name)
{
    this->m_name = name;
}

void CrystalModel::description(QString description)
{
    this->m_description = description;
}

void CrystalModel::planet(int planet_id)
{
    this->m_planet = PlanetModel::load(planet_id);
}

void CrystalModel::polarity(int polarity_id)
{
    this->m_polarity = PolarityModel::load(polarity_id);
}

void CrystalModel::zodiac(int zodiac_id)
{
    this->m_zodiac = ZodiacModel::load(zodiac_id);
}

void CrystalModel::animals(QList<QString> animals)
{
    for (const QString &name: animals) {
        this->m_animals.append(AnimalModel::load(name));
    }
}

void CrystalModel::animals(QList<AnimalModel> animals)
{
    this->m_animals = animals;
}

void CrystalModel::colours(QList<QString> colours)
{
    for (const QString &name: colours) {
        this->m_colours.append(ColourModel::load(name));
    }
}

void CrystalModel::colours(QList<ColourModel> colours)
{
    this->m_colours = colours;
}

void CrystalModel::gods(QList<QString> gods)
{
    for (const QString &name: gods) {
        this->m_gods.append(GodModel::load(name));
    }
}

void CrystalModel::gods(QList<GodModel> gods)
{
    this->m_gods = gods;
}

void CrystalModel::herbs(QList<QString> herbs)
{
    for (const QString &name: herbs) {
        this->m_herbs.append(HerbModel::load(name));
    }
}

void CrystalModel::herbs(QList<HerbModel> herbs)
{
    this->m_herbs = herbs;
}

void CrystalModel::trees(QList<QString> trees)
{
    for (const QString &name: trees) {
        this->m_trees.append(TreeModel::load(name));
    }
}

void CrystalModel::trees(QList<TreeModel> trees)
{
    this->m_trees = trees;
}
