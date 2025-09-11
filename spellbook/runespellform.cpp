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
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/fehu.png"), "fehu");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_uruzButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/uruz.png"), "uruz");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_thurisazButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/thurisaz.png"), "thurisaz");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_ansuzButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/ansuz.png"), "ansuz");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_raidoButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/raido.png"), "raido");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_kaunazButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/kaunaz.png"), "kaunaz");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_geboButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/gebo.png"), "gebo");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_wunjoButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/wunjo.png"), "wunjo");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_hagalazButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/hagalaz.png"), "hagalaz");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_nauthizButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/nauthiz.png"), "nauthiz");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_isaButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/isa.png"), "isa");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_jeraButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/jera.png"), "jera");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_eihwazButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/eihwaz.png"), "eihwaz");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_perthoButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/pertho.png"), "pertho");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_algizButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/algiz.png"), "algiz");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_sowuloButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/sowulo.png"), "sowulo");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_teiwazButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/teiwaz.png"), "teiwaz");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_berkanaButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/berkana.png"), "berkana");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_ehwazButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/ehwaz.png"), "ehwaz");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_mannazButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/mannaz.png"), "mannaz");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_laguzButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/laguz.png"), "laguz");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_inguzButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/inguz.png"), "inguz");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_othilaButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/othila.png"), "othila");
    scene->addItem(pixmap);
}


void RuneSpellForm::on_dagazButton_clicked()
{
    ResizablePixmap *pixmap = new ResizablePixmap(QPixmap(":/glyphs/dagaz.png"), "dagaz");
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

    foreach (QGraphicsItem *glyph, glyphs) {
        ResizablePixmap *pixmap = qgraphicsitem_cast<ResizablePixmap *>(glyph);
        if (pixmap) {
            GlyphModel glyph_model {0, pixmap->glyph(), 0, pixmap->rect().left(), pixmap->rect().top(), pixmap->rect().width(), pixmap->rect().height()};
            model.add_glyph(glyph_model);
        }
    }

    if (model.save()) {
        if (m_id == 0) {
            ui->nameLineEdit->clear();
            ui->descriptionEditBox->clear();
            ui->tagsLineEdit->clear();
        } else {
            QMessageBox::information(this, "Success", "Runespell has been saved");
        }
    } else {
        QMessageBox::critical(this, "Error", "Runespell not saved");
    }
}

