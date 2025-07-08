#include "crystalform.h"
#include "ui_crystalform.h"

#include <QMessageBox>
#include <QSqlQuery>

#include "../polarity/polaritymodel.h"
#include "../planets/planetmodel.h"
#include "crystalmodel.h"
#include "../zodiac/zodiacmodel.h"

#include "crystalcorresponderchooser.h"

CrystalForm::CrystalForm(QWidget *parent, int id, QString mode)
    : QDialog(parent)
    , ui(new Ui::CrystalForm)
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
        CrystalModel model = CrystalModel::load(id);

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
        }

        for (ColourModel &colour: model.colours()) {
            ui->colourList->addItem(colour.name());
        }

        for (GodModel &god: model.gods()) {
            ui->godList->addItem(god.name());
        }

        for (HerbModel &herb: model.herbs()) {
            ui->herbList->addItem(herb.name());
        }

        for (TreeModel &tree: model.trees()) {
            ui->treeList->addItem(tree.name());
        }
    }

    if (mode == "view") {
        ui->saveButton->setDisabled(true);
        ui->saveButton->setVisible(false);
    }
}

CrystalForm::~CrystalForm()
{
    delete ui;
}

QListWidget* CrystalForm::getListView(std::string view)
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

void CrystalForm::on_addAnimalButton_clicked()
{
    CrystalCorresponderChooser *chooser = new CrystalCorresponderChooser(this, "Animal");
    chooser->setWindowTitle("Choose Animals");
    chooser->exec();
}


void CrystalForm::on_addColourButton_clicked()
{
    CrystalCorresponderChooser *chooser = new CrystalCorresponderChooser(this, "Colour");
    chooser->setWindowTitle("Choose Colours");
    chooser->exec();
}


void CrystalForm::on_addGodButton_clicked()
{
    CrystalCorresponderChooser *chooser = new CrystalCorresponderChooser(this, "God");
    chooser->setWindowTitle("Choose Gods");
    chooser->exec();
}


void CrystalForm::on_Herb_clicked()
{
    CrystalCorresponderChooser *chooser = new CrystalCorresponderChooser(this, "Herb");
    chooser->setWindowTitle("Choose Herbs");
    chooser->exec();
}


void CrystalForm::on_addTreeButton_clicked()
{
    CrystalCorresponderChooser *chooser = new CrystalCorresponderChooser(this, "Tree");
    chooser->setWindowTitle("Choose Trees");
    chooser->exec();
}


void CrystalForm::on_removeTreeButton_clicked()
{
    QListWidgetItem *item = ui->treeList->takeItem(ui->treeList->currentRow());
    delete item;
}


void CrystalForm::on_removeHerbButton_clicked()
{
    QListWidgetItem *item = ui->herbList->takeItem(ui->herbList->currentRow());
    delete item;
}


void CrystalForm::on_removeGodButton_clicked()
{
    QListWidgetItem *item = ui->godList->takeItem(ui->godList->currentRow());
    delete item;
}


void CrystalForm::on_removeColourButton_clicked()
{
    QListWidgetItem *item = ui->colourList->takeItem(ui->colourList->currentRow());
    delete item;
}


void CrystalForm::on_removeAnimalButton_clicked()
{
    QListWidgetItem *item = ui->animalList->takeItem(ui->animalList->currentRow());
    delete item;
}


void CrystalForm::on_closeButton_clicked()
{
    reject();
}


void CrystalForm::on_saveButton_clicked()
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

    CrystalModel model {m_id, name, description, planetId, polarityId, zodiacId};

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
            QMessageBox::information(this, "Success", "Crystal saved");
        }
    } else {
        QMessageBox::critical(this, "Error", "Crystal not saved");
    }
}

void CrystalForm::saveCorresponders(CrystalModel model)
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
