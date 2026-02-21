#ifndef DBINITIALIZER_H
#define DBINITIALIZER_H

#include <QString>
#include <QWindow>

class DBInitializer
{
public:
    DBInitializer();

    void createDataStore(const QString &base);
    void createDatabaseTables();

private:
    void createPolarity();
    void createColours();
    void createGods();
    void createHerbs();
    void createPlanets();
    void createAnimals();
    void createTrees();
    void createZodiac();
    void createNotes();
    void createRunestones();
    void createTarot();
    void createCrystals();
    void createSpellbook();
    void createCodex();
};

#endif // DBINITIALIZER_H
