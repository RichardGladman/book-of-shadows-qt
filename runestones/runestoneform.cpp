#include "runestoneform.h"
#include "ui_runestoneform.h"

#include <QSqlQuery>

#include "../polarity/polaritymodel.h"
#include "../planets/planetmodel.h"
#include "../zodiac/zodiacmodel.h"

#include "corresponderchooser.h"

RunestoneForm::RunestoneForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RunestoneForm)
{
    ui->setupUi(this);

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
    CorresponderChooser *chooser = new CorresponderChooser(this, "Animal");
    chooser->setWindowTitle("Choose Animals");
    chooser->exec();
}


void RunestoneForm::on_addColourButton_clicked()
{
    CorresponderChooser *chooser = new CorresponderChooser(this, "Colour");
    chooser->setWindowTitle("Choose Colours");
    chooser->exec();
}


void RunestoneForm::on_addGodButton_clicked()
{
    CorresponderChooser *chooser = new CorresponderChooser(this, "God");
    chooser->setWindowTitle("Choose Gods");
    chooser->exec();
}


void RunestoneForm::on_Herb_clicked()
{
    CorresponderChooser *chooser = new CorresponderChooser(this, "Herb");
    chooser->setWindowTitle("Choose Herbs");
    chooser->exec();
}


void RunestoneForm::on_addTreeButton_clicked()
{
    CorresponderChooser *chooser = new CorresponderChooser(this, "Tree");
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
    reject();
}

