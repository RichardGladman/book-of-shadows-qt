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
    statements.push_back("CREATE TABLE IF NOT EXISTS runestone_animal (runestone_id INTEGER, animal_id INTEGER, PRIMARY KEY(runestone_id, animal_id));");
    statements.push_back("CREATE TABLE IF NOT EXISTS runestone_colour (runestone_id INTEGER, colour_id INTEGER, PRIMARY KEY(runestone_id, colour_id));");
    statements.push_back("CREATE TABLE IF NOT EXISTS runestone_god (runestone_id INTEGER, god_id INTEGER, PRIMARY KEY(runestone_id, god_id));");
    statements.push_back("CREATE TABLE IF NOT EXISTS runestone_herb (runestone_id INTEGER, herb_id INTEGER, PRIMARY KEY(runestone_id, herb_id));");
    statements.push_back("CREATE TABLE IF NOT EXISTS runestone_tree (runestone_id INTEGER, tree_id INTEGER, PRIMARY KEY(runestone_id, tree_id));");

    for (QString &sql: statements) {
        QSqlQuery query;
        query.prepare(sql);
        query.exec();
    }
}
