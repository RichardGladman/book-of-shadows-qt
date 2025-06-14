#include "corresponderchooser.h"
#include "ui_corresponderchooser.h"

#include <QListView>
#include <QSqlQuery>

#include "runestoneform.h"

#include "../animals/animalmodel.h"
#include "../colours/colourmodel.h"
#include "../gods/godmodel.h"
#include "../herbs/herbmodel.h"
#include "../trees/treemodel.h"

CorresponderChooser::CorresponderChooser(RunestoneForm *parent, std::string corresponder)
    : QDialog(parent)
    , ui(new Ui::CorresponderChooser)
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

    while (query.next()) {
        ui->corresponderCombo->addItem(query.value(1).toString(), query.value(0).toInt());
    }

    m_parent = parent;
    m_corresponder = corresponder;
}

CorresponderChooser::~CorresponderChooser()
{
    delete ui;
}

void CorresponderChooser::on_closeButton_clicked()
{
    reject();
}


void CorresponderChooser::on_addButton_clicked()
{
    QListWidget *listWidget = m_parent->getListView(m_corresponder);
    QListWidgetItem item = QListWidgetItem {ui->corresponderCombo->currentData().toString(), listWidget};

 }

