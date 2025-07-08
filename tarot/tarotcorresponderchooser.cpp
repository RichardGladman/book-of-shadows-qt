#include "tarotcorresponderchooser.h"
#include "ui_tarotcorresponderchooser.h"


#include <QListWidget>
#include <QSqlQuery>

#include "tarotform.h"

#include "../animals/animalmodel.h"
#include "../colours/colourmodel.h"
#include "../gods/godmodel.h"
#include "../herbs/herbmodel.h"
#include "../trees/treemodel.h"

TarotCorresponderChooser::TarotCorresponderChooser(TarotForm *parent, std::string corresponder)
    : QDialog(parent)
    , ui(new Ui::TarotCorresponderChooser)
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

TarotCorresponderChooser::~TarotCorresponderChooser()
{
    delete ui;
}

void TarotCorresponderChooser::on_closeButton_clicked()
{
    reject();
}


void TarotCorresponderChooser::on_addButton_clicked()
{
    QListWidget *listWidget = m_parent->getListView(m_corresponder);
    new QListWidgetItem {ui->corresponderCombo->currentText(), listWidget};
    ui->corresponderCombo->removeItem(ui->corresponderCombo->currentIndex());
}
