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

