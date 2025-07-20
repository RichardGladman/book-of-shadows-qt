#include "runespellform.h"
#include "ui_runespellform.h"

#include <QGraphicsView>
#include "resizablepixmap.h"

RuneSpellForm::RuneSpellForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RuneSpellForm)
{
    ui->setupUi(this);

    QGraphicsView *view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);

    view->setScene(scene);
    ui->sceneLayout->addWidget(view);
}

RuneSpellForm::~RuneSpellForm()
{
    delete ui;
}

void RuneSpellForm::on_fehuButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/fehu.png"));
    scene->addItem(pixmap);
}

