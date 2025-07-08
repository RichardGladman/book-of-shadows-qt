#include "crystalcorresponderchooser.h"
#include "ui_crystalcorresponderchooser.h"


#include <QListWidget>
#include <QSqlQuery>

#include "crystalform.h"

#include "../animals/animalmodel.h"
#include "../colours/colourmodel.h"
#include "../gods/godmodel.h"
#include "../herbs/herbmodel.h"
#include "../trees/treemodel.h"

CrystalCorresponderChooser::CrystalCorresponderChooser(CrystalForm *parent, std::string corresponder)
    : QDialog(parent)
    , ui(new Ui::CrystalCorresponderChooser)
{
    ui->setupUi(this);

    QSqlQuery query;

    if (corresponder == "Animal") {
        query = AnimalModel::list();
    } else if (corresponder == "Colour") {
        query = ColourModel::list();
    } else if (corresponder == "God") {
        query = GodModel::list();
    } else if (corresponder == "Herb") {
        query = HerbModel::list();
    } else if (corresponder == "Tree") {
        query = TreeModel::list();
    }

    QListWidget *widget = parent->getListView(corresponder);

    while (query.next()) {
        if (widget->findItems(query.value(1).toString(), Qt::MatchFlag::MatchFixedString).isEmpty()) {
            ui->corresponderCombo->addItem(query.value(1).toString(), query.value(0).toInt());
        }
    }

    m_parent = parent;
    m_corresponder = corresponder;
}

CrystalCorresponderChooser::~CrystalCorresponderChooser()
{
    delete ui;
}

void CrystalCorresponderChooser::on_closeButton_clicked()
{
    reject();
}


void CrystalCorresponderChooser::on_addButton_clicked()
{
    QListWidget *listWidget = m_parent->getListView(m_corresponder);
    new QListWidgetItem {ui->corresponderCombo->currentText(), listWidget};
    ui->corresponderCombo->removeItem(ui->corresponderCombo->currentIndex());
}

