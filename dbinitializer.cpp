#include "dbinitializer.h"

#include <QDir>
#include <QtDebug>
#include <QSqlQuery>
#include <vector>

DBInitializer::DBInitializer() {}

void DBInitializer::createDataStore(const QString &base)
{
    QDir dir(base + "/data");
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qDebug() << "Failed to create data directory";
            return;
        }
    }

    dir = QDir(base + "/images");
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qDebug() << "Failed to create images directory";
            return;
        }
    }

    QFile file(base + "/data/bos.db");
    if (!file.exists()) {
        file.open(QIODevice::WriteOnly);
        file.close();
    }
}

void DBInitializer::createDatabaseTables()
{
    createPolarity();
    createColours();
    createGods();
    createHerbs();
    createPlanets();
    createAnimals();
    createTrees();
    createZodiac();
    createNotes();
    createRunestones();
    createTarot();
    createCrystals();
    createSpellbook();
}

void DBInitializer::createPolarity()
{
    QString sql = "CREATE TABLE IF NOT EXISTS polarities (id INTEGER PRIMARY KEY, name VARCHAR(255), meaning TEXT, image VARCHAR(255));";
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

void DBInitializer::createColours()
{
    QString sql = "CREATE TABLE IF NOT EXISTS colours (id INTEGER PRIMARY KEY, name VARCHAR(255), meaning TEXT);";
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

void DBInitializer::createGods()
{
    QString sql = "CREATE TABLE IF NOT EXISTS gods (id INTEGER PRIMARY KEY, name VARCHAR(255), polarity_id INTEGER, description TEXT);";
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

void DBInitializer::createHerbs()
{
    QString sql = "CREATE TABLE IF NOT EXISTS herbs (id INTEGER PRIMARY KEY, name VARCHAR(255), description TEXT);";
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

void DBInitializer::createPlanets()
{
    QString sql = "CREATE TABLE IF NOT EXISTS planets (id INTEGER PRIMARY KEY, name VARCHAR(255), description TEXT);";
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

void DBInitializer::createAnimals()
{
    QString sql = "CREATE TABLE IF NOT EXISTS animals (id INTEGER PRIMARY KEY, name VARCHAR(255), description TEXT);";
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

void DBInitializer::createTrees()
{
    QString sql = "CREATE TABLE IF NOT EXISTS trees (id INTEGER PRIMARY KEY, name VARCHAR(255), description TEXT);";
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

void DBInitializer::createZodiac()
{
    QString sql = "CREATE TABLE IF NOT EXISTS zodiac (id INTEGER PRIMARY KEY, name VARCHAR(255), description TEXT);";
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

void DBInitializer::createNotes()
{
    QString sql = "CREATE TABLE IF NOT EXISTS notes (id INTEGER PRIMARY KEY, title VARCHAR(255), text TEXT);";
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

void DBInitializer::createRunestones()
{
    std::vector<QString> statements {};

    statements.push_back(
        "CREATE TABLE IF NOT EXISTS runestones (id INTEGER PRIMARY KEY, name VARCHAR(255), meaning TEXT, "
        "planet_id INTEGER, polarity_id INTEGER, zodiac_id INTEGER);");
    statements.push_back("CREATE TABLE IF NOT EXISTS runestone_animal (runestone_id INTEGER, animal_id INTEGER, PRIMARY KEY(runestone_id, animal_id),"
                         " FOREIGN KEY (runestone_id) REFERENCES runestones(id))");
    statements.push_back("CREATE TABLE IF NOT EXISTS runestone_colour (runestone_id INTEGER, colour_id INTEGER, PRIMARY KEY(runestone_id, colour_id),"
                         " FOREIGN KEY (runestone_id) REFERENCES runestones(id))");
    statements.push_back("CREATE TABLE IF NOT EXISTS runestone_god (runestone_id INTEGER, god_id INTEGER, PRIMARY KEY(runestone_id, god_id),"
                         " FOREIGN KEY (runestone_id) REFERENCES runestones(id))");
    statements.push_back("CREATE TABLE IF NOT EXISTS runestone_herb (runestone_id INTEGER, herb_id INTEGER, PRIMARY KEY(runestone_id, herb_id),"
                         " FOREIGN KEY (runestone_id) REFERENCES runestones(id))");
    statements.push_back("CREATE TABLE IF NOT EXISTS runestone_tree (runestone_id INTEGER, tree_id INTEGER, PRIMARY KEY(runestone_id, tree_id),"
                         " FOREIGN KEY (runestone_id) REFERENCES runestones(id))");

    for (QString &sql: statements) {
        QSqlQuery query;
        query.prepare(sql);
        query.exec();
    }
}

void DBInitializer::createTarot()
{
    std::vector<QString> statements {};

    statements.push_back(
        "CREATE TABLE IF NOT EXISTS tarot (id INTEGER PRIMARY KEY, name VARCHAR(255), meaning TEXT, "
        "planet_id INTEGER, polarity_id INTEGER, zodiac_id INTEGER);");
    statements.push_back("CREATE TABLE IF NOT EXISTS tarot_animal (tarot_id INTEGER, animal_id INTEGER, PRIMARY KEY(tarot_id, animal_id),"
                         " FOREIGN KEY (tarot_id) REFERENCES tarot(id))");
    statements.push_back("CREATE TABLE IF NOT EXISTS tarot_colour (tarot_id INTEGER, colour_id INTEGER, PRIMARY KEY(tarot_id, colour_id),"
                         " FOREIGN KEY (tarot_id) REFERENCES tarot(id))");
    statements.push_back("CREATE TABLE IF NOT EXISTS tarot_god (tarot_id INTEGER, god_id INTEGER, PRIMARY KEY(tarot_id, god_id),"
                         " FOREIGN KEY (tarot_id) REFERENCES tarot(id))");
    statements.push_back("CREATE TABLE IF NOT EXISTS tarot_herb (tarot_id INTEGER, herb_id INTEGER, PRIMARY KEY(tarot_id, herb_id),"
                         " FOREIGN KEY (tarot_id) REFERENCES tarot(id))");
    statements.push_back("CREATE TABLE IF NOT EXISTS tarot_tree (tarot_id INTEGER, tree_id INTEGER, PRIMARY KEY(tarot_id, tree_id),"
                         " FOREIGN KEY (tarot_id) REFERENCES tarot(id))");

    for (QString &sql: statements) {
        QSqlQuery query;
        query.prepare(sql);
        query.exec();
    }
}

void DBInitializer::createCrystals()
{
    std::vector<QString> statements {};

    statements.push_back(
        "CREATE TABLE IF NOT EXISTS crystals (id INTEGER PRIMARY KEY, name VARCHAR(255), meaning TEXT, "
        "planet_id INTEGER, polarity_id INTEGER, zodiac_id INTEGER);");
    statements.push_back("CREATE TABLE IF NOT EXISTS crystal_animal (crystal_id INTEGER, animal_id INTEGER, PRIMARY KEY(crystal_id, animal_id),"
                         " FOREIGN KEY (crystal_id) REFERENCES crystal(id))");
    statements.push_back("CREATE TABLE IF NOT EXISTS crystal_colour (crystal_id INTEGER, colour_id INTEGER, PRIMARY KEY(crystal_id, colour_id),"
                         " FOREIGN KEY (crystal_id) REFERENCES crystal(id))");
    statements.push_back("CREATE TABLE IF NOT EXISTS crystal_god (crystal_id INTEGER, god_id INTEGER, PRIMARY KEY(crystal_id, god_id),"
                         " FOREIGN KEY (crystal_id) REFERENCES crystal(id))");
    statements.push_back("CREATE TABLE IF NOT EXISTS crystal_herb (crystal_id INTEGER, herb_id INTEGER, PRIMARY KEY(crystal_id, herb_id),"
                         " FOREIGN KEY (crystal_id) REFERENCES crystal(id))");
    statements.push_back("CREATE TABLE IF NOT EXISTS crystal_tree (crystal_id INTEGER, tree_id INTEGER, PRIMARY KEY(crystal_id, tree_id),"
                         " FOREIGN KEY (crystal_id) REFERENCES crystal(id))");

    for (QString &sql: statements) {
        QSqlQuery query;
        query.prepare(sql);
        query.exec();
    }
}

void DBInitializer::createSpellbook()
{
    std::vector<QString> statements {};

    statements.push_back("CREATE TABLE IF NOT EXISTS runespells (id INTEGER PRIMARY KEY, title TEXT, description TEXT)");
    statements.push_back("CREATE TABLE IF NOT EXISTS glyphs (id INTEGER PRIMARY KEY, name TEXT, runespell INTEGER, x_pos INTEGER, y_pos INTEGER, width INTEGER, height INTEGER)");
    statements.push_back("CREATE TABLE IF NOT EXISTS tags (id INTEGER PRIMARY KEY, tag VARCHAR(255), runespell INTEGER)");

    QSqlQuery query;

    for (QString &sql: statements) {
        query.prepare(sql);
        query.exec();
    }
}
