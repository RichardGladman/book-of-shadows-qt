#include "runestonecorresponderchooser.h"
#include "ui_runestonecorresponderchooser.h"

#include <QListView>
#include <QSqlQuery>

#include "runestoneform.h"

#include "../animals/animalmodel.h"
#include "../colours/colourmodel.h"
#include "../gods/godmodel.h"
#include "../herbs/herbmodel.h"
#include "../trees/treemodel.h"

RunestoneCorresponderChooser::RunestoneCorresponderChooser(RunestoneForm *parent, std::string corresponder)
    : QDialog(parent)
    , ui(new Ui::RunestoneCorresponderChooser)
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

RunestoneCorresponderChooser::~RunestoneCorresponderChooser()
{
    delete ui;
}

void RunestoneCorresponderChooser::on_closeButton_clicked()
{
    reject();
}


void RunestoneCorresponderChooser::on_addButton_clicked()
{
    QListWidget *listWidget = m_parent->getListView(m_corresponder);
    new QListWidgetItem {ui->corresponderCombo->currentText(), listWidget};
    ui->corresponderCombo->removeItem(ui->corresponderCombo->currentIndex());
}

