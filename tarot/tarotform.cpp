#include "tarotform.h"
#include "ui_tarotform.h"


#include <QMessageBox>
#include <QSqlQuery>

#include "../polarity/polaritymodel.h"
#include "../planets/planetmodel.h"
#include "tarotmodel.h"
#include "../zodiac/zodiacmodel.h"

#include "tarotcorresponderchooser.h"

TarotForm::TarotForm(QWidget *parent, int id, QString mode)
    : QDialog(parent)
    , ui(new Ui::TarotForm)
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
        TarotModel model = TarotModel::load(id);

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

TarotForm::~TarotForm()
{
    delete ui;
}

QListWidget* TarotForm::getListView(std::string view)
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

void TarotForm::on_addAnimalButton_clicked()
{
    TarotCorresponderChooser *chooser = new TarotCorresponderChooser(this, "Animal");
    chooser->setWindowTitle("Choose Animals");
    chooser->exec();
}


void TarotForm::on_addColourButton_clicked()
{
    TarotCorresponderChooser *chooser = new TarotCorresponderChooser(this, "Colour");
    chooser->setWindowTitle("Choose Colours");
    chooser->exec();
}


void TarotForm::on_addGodButton_clicked()
{
    TarotCorresponderChooser *chooser = new TarotCorresponderChooser(this, "God");
    chooser->setWindowTitle("Choose Gods");
    chooser->exec();
}


void TarotForm::on_Herb_clicked()
{
    TarotCorresponderChooser *chooser = new TarotCorresponderChooser(this, "Herb");
    chooser->setWindowTitle("Choose Herbs");
    chooser->exec();
}


void TarotForm::on_addTreeButton_clicked()
{
    TarotCorresponderChooser *chooser = new TarotCorresponderChooser(this, "Tree");
    chooser->setWindowTitle("Choose Trees");
    chooser->exec();
}


void TarotForm::on_removeTreeButton_clicked()
{
    QListWidgetItem *item = ui->treeList->takeItem(ui->treeList->currentRow());
    delete item;
}


void TarotForm::on_removeHerbButton_clicked()
{
    QListWidgetItem *item = ui->herbList->takeItem(ui->herbList->currentRow());
    delete item;
}


void TarotForm::on_removeGodButton_clicked()
{
    QListWidgetItem *item = ui->godList->takeItem(ui->godList->currentRow());
    delete item;
}


void TarotForm::on_removeColourButton_clicked()
{
    QListWidgetItem *item = ui->colourList->takeItem(ui->colourList->currentRow());
    delete item;
}


void TarotForm::on_removeAnimalButton_clicked()
{
    QListWidgetItem *item = ui->animalList->takeItem(ui->animalList->currentRow());
    delete item;
}


void TarotForm::on_closeButton_clicked()
{
    reject();
}


void TarotForm::on_saveButton_clicked()
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

    TarotModel model {m_id, name, description, planetId, polarityId, zodiacId};

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
            QMessageBox::information(this, "Success", "Tarot saved");
        }
    } else {
        QMessageBox::critical(this, "Error", "Tarot not saved");
    }
}

void TarotForm::saveCorresponders(TarotModel model)
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
