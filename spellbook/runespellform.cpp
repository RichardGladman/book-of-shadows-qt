#include "runespellform.h"
#include "ui_runespellform.h"

#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QMessageBox>
#include "resizablepixmap.h"
#include "runespellmodel.h"
#include "tagmodel.h"

RuneSpellForm::RuneSpellForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RuneSpellForm)
{
    ui->setupUi(this);

    view = new QGraphicsView(this);
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


void RuneSpellForm::on_uruzButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/uruz.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_thurisazButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/thurisaz.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_ansuzButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/ansuz.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_raidoButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/raido.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_kaunazButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/kaunaz.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_geboButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/gebo.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_wunjoButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/wunjo.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_hagalazButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/hagalaz.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_nauthizButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/nauthiz.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_isaButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/isa.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_jeraButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/jera.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_eihwazButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/wihwaz.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_perthoButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/pertho.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_algizButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/algiz.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_sowuloButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/sowulo.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_teiwazButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/teiwaz.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_berkanaButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/berkana.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_ehwazButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/ehwaz.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_mannazButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/mannaz.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_laguzButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/laguz.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_inguzButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/inguz.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_othilaButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/othila.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_dagazButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/dagaz.png"));
    scene->addItem(pixmap);
}


void RuneSpellForm::on_closeButton_clicked()
{
    reject();
}


void RuneSpellForm::on_saveButton_clicked()
{
    QString name = ui->nameLineEdit->text();
    QString description = ui->descriptionEditBox->toPlainText();
    QString tags = ui->tagsLineEdit->text();
    QList<QGraphicsItem *> glyphs = view->items();

    if (name.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Name must be entered");
        return;
    }

    RunespellModel model { name, description };

    QStringList tag_strings = tags.split(',');
    for (QString &t: tag_strings) {
        model.add_tag(TagModel {0, t, 0});
    }
}

