#include "dbinitializer.h"

#include <QDir>
#include <QtDebug>
#include <QSqlQuery>

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
