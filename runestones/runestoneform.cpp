#include "runestoneform.h"
#include "ui_runestoneform.h"

#include <QMessageBox>
#include <QSqlQuery>

#include "../polarity/polaritymodel.h"
#include "../planets/planetmodel.h"
#include "runestonemodel.h"
#include "../zodiac/zodiacmodel.h"

#include "../settings/settingsmodel.h"
#include "../util/compare.h"

#include "runestonecorresponderchooser.h"

extern SettingsModel settings;

RunestoneForm::RunestoneForm(QWidget *parent, int id, QString mode)
    : QDialog(parent)
    , ui(new Ui::RunestoneForm)
{
    ui->setupUi(this);

    m_id = id;

    QSqlQuery query = PolarityModel::list();
    while (query.next()) {
        ui->polarityCombo->addItem(query.value(1).toString(), query.value(0).toInt());
    }

    query = PlanetModel::list();
    while (query.next()) {
        ui->planetCombo->addItem(query.value(1).toString(), query.value(0).toInt());
    }

    query = ZodiacModel::list();
    while (query.next()) {
        ui->zodiacCombo->addItem(query.value(1).toString(), query.value(0).toInt());
    }

    if (id != 0) {
        RunestoneModel model = RunestoneModel::load(id);

        ui->nameTextField->setText(model.name());
        ui->descriptionTextEdit->setPlainText(model.description());

        int index = ui->polarityCombo->findData(model.polarity().id());
        ui->polarityCombo->setCurrentIndex(index);

        index = ui->planetCombo->findData(model.planet().id());
        ui->planetCombo->setCurrentIndex(index);

        index = ui->zodiacCombo->findData(model.zodiac().id());
        ui->zodiacCombo->setCurrentIndex(index);

        for (AnimalModel &animal: model.animals()) {
            ui->animalList->addItem(animal.name());
            default_animals.append(animal.name());
        }
        
        for (ColourModel &colour: model.colours()) {
            ui->colourList->addItem(colour.name());
            default_colours.append(colour.name());
        }
        
        for (GodModel &god: model.gods()) {
            ui->godList->addItem(god.name());
            default_gods.append(god.name());
        }
        
        for (HerbModel &herb: model.herbs()) {
            ui->herbList->addItem(herb.name());
            default_herbs.append(herb.name());
        }
        
        for (TreeModel &tree: model.trees()) {
            ui->treeList->addItem(tree.name());
            default_trees.append(tree.name());
        }
    }

    default_name = ui->nameTextField->text();
    default_description = ui->descriptionTextEdit->toPlainText();

    default_polarity = ui->polarityCombo->currentData().toInt();
    default_planet = ui->planetCombo->currentData().toInt();
    default_zodiac = ui->zodiacCombo->currentData().toInt();

    if (mode == "view") {
        ui->saveButton->setDisabled(true);
        ui->saveButton->setVisible(false);
    }
}

RunestoneForm::~RunestoneForm()
{
    delete ui;
}

QListWidget* RunestoneForm::getListView(std::string view)
{
    if (view == "Animal") {
        return ui->animalList;
    } else if (view == "Colour") {
        return ui->colourList;
    } else if (view == "God") {
        return ui->godList;
    } else if (view == "Herb") {
       return ui->herbList;
    } else if (view == "Tree") {
        return ui->treeList;
    }

    return nullptr;
}

void RunestoneForm::on_addAnimalButton_clicked()
{
    RunestoneCorresponderChooser *chooser = new RunestoneCorresponderChooser(this, "Animal");
    chooser->setWindowTitle("Choose Animals");
    chooser->exec();
}


void RunestoneForm::on_addColourButton_clicked()
{
    RunestoneCorresponderChooser *chooser = new RunestoneCorresponderChooser(this, "Colour");
    chooser->setWindowTitle("Choose Colours");
    chooser->exec();
}


void RunestoneForm::on_addGodButton_clicked()
{
    RunestoneCorresponderChooser *chooser = new RunestoneCorresponderChooser(this, "God");
    chooser->setWindowTitle("Choose Gods");
    chooser->exec();
}


void RunestoneForm::on_Herb_clicked()
{
    RunestoneCorresponderChooser *chooser = new RunestoneCorresponderChooser(this, "Herb");
    chooser->setWindowTitle("Choose Herbs");
    chooser->exec();
}


void RunestoneForm::on_addTreeButton_clicked()
{
    RunestoneCorresponderChooser *chooser = new RunestoneCorresponderChooser(this, "Tree");
    chooser->setWindowTitle("Choose Trees");
    chooser->exec();
}


void RunestoneForm::on_removeTreeButton_clicked()
{
    QListWidgetItem *item = ui->treeList->takeItem(ui->treeList->currentRow());
    delete item;
}


void RunestoneForm::on_removeHerbButton_clicked()
{
    QListWidgetItem *item = ui->herbList->takeItem(ui->herbList->currentRow());
    delete item;
}


void RunestoneForm::on_removeGodButton_clicked()
{
    QListWidgetItem *item = ui->godList->takeItem(ui->godList->currentRow());
    delete item;
}


void RunestoneForm::on_removeColourButton_clicked()
{
    QListWidgetItem *item = ui->colourList->takeItem(ui->colourList->currentRow());
    delete item;
}


void RunestoneForm::on_removeAnimalButton_clicked()
{
    QListWidgetItem *item = ui->animalList->takeItem(ui->animalList->currentRow());
    delete item;
}


void RunestoneForm::on_closeButton_clicked()
{
    QString name = ui->nameTextField->text();
    QString description = ui->descriptionTextEdit->toPlainText();
    int planetId = ui->planetCombo->currentData().toInt();
    int polarityId = ui->polarityCombo->currentData().toInt();
    int zodiacId = ui->zodiacCombo->currentData().toInt();

    QList<QListWidgetItem*> animals = ui->animalList->findItems("*", Qt::MatchWildcard);
    QList<QListWidgetItem*> colours = ui->colourList->findItems("*", Qt::MatchWildcard);
    QList<QListWidgetItem*> gods = ui->godList->findItems("*", Qt::MatchWildcard);
    QList<QListWidgetItem*> herbs = ui->herbList->findItems("*", Qt::MatchWildcard);
    QList<QListWidgetItem*> trees = ui->treeList->findItems("*", Qt::MatchWildcard);

    if (settings.show_warnings() && (name != default_name || description != default_description || planetId != default_planet || 
        polarityId != default_polarity ||zodiacId != default_zodiac || !Compare::areEqual(animals, default_animals) ||
        !Compare::areEqual(colours, default_colours) || !Compare::areEqual(gods, default_gods) ||
        !Compare::areEqual(herbs, default_herbs) || !Compare::areEqual(trees, default_trees))) {
        QMessageBox::StandardButton button = QMessageBox::warning(this, "Unsaved Changes",
                             "You have unsaved changes, if you continue they will be lost. Do you want to continue?",
                                QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::No) {
            return;
        }   
    }

    reject();
}


void RunestoneForm::on_saveButton_clicked()
{
    QString name = ui->nameTextField->text();
    QString description = ui->descriptionTextEdit->toPlainText();
    int planetId = ui->planetCombo->currentData().toInt();
    int polarityId = ui->polarityCombo->currentData().toInt();
    int zodiacId = ui->zodiacCombo->currentData().toInt();

    if (name.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Name must not be empty");
        return;
    }

    RunestoneModel model {m_id, name, description, planetId, polarityId, zodiacId};

    if (model.save()) {
        saveCorresponders(model);

        if (m_id == 0) {
            ui->nameTextField->clear();
            ui->descriptionTextEdit->clear();
            ui->planetCombo->clear();
            ui->polarityCombo->clear();
            ui->zodiacCombo->clear();
            ui->animalList->clear();
            ui->colourList->clear();
            ui->godList->clear();
            ui->herbList->clear();
            ui->treeList->clear();
        } else {
            QMessageBox::information(this, "Success", "Runestone saved");
        }
    } else {
        QMessageBox::critical(this, "Error", "Runestone not saved");
    }
}

void RunestoneForm::saveCorresponders(RunestoneModel model)
{
    QList<QString> corresponders;

    for (int i=0; i<ui->animalList->count(); ++i) {
        corresponders.append(ui->animalList->item(i)->text());
    }

    model.saveAnimals(corresponders);

    corresponders.clear();
        for (int i=0; i<ui->colourList->count(); ++i) {
        corresponders.append(ui->colourList->item(i)->text());
    }

    model.saveColours(corresponders);

    corresponders.clear();
    for (int i=0; i<ui->godList->count(); ++i) {
        corresponders.append(ui->godList->item(i)->text());
    }

    model.saveGods(corresponders);

    corresponders.clear();
    for (int i=0; i<ui->herbList->count(); ++i) {
        corresponders.append(ui->herbList->item(i)->text());
    }

    model.saveHerbs(corresponders);

    corresponders.clear();
    for (int i=0; i<ui->treeList->count(); ++i) {
        corresponders.append(ui->treeList->item(i)->text());
    }

    model.saveTrees(corresponders);
}
