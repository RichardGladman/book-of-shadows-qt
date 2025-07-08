#include "noteform.h"
#include "ui_noteform.h"

#include "notemodel.h"

#include <QMessageBox>

NoteForm::NoteForm(QWidget *parent, int id, QString mode)
    : QDialog(parent)
    , ui(new Ui::NoteForm)
{
    ui->setupUi(this);

    if (id != 0) {
        NoteModel model = NoteModel::load(id);
        ui->titleLineEdit->setText(model.title());
        ui->textTextEdit->setPlainText(model.text());
        m_id = id;
    }

    if (mode == "view") {
        ui->titleLineEdit->setEnabled(false);
        ui->textTextEdit->setEnabled(false);
        ui->saveButton->setVisible(false);
        ui->saveButton->setEnabled(false);
    }
}

NoteForm::~NoteForm()
{
    delete ui;
}

void NoteForm::on_saveButton_clicked()
{
    QString title = ui->titleLineEdit->text();
    QString text = ui->textTextEdit->toPlainText();

    if (title.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Title must not be empty");
        return;
    }

    NoteModel model {m_id, title, text};

    if (model.save()) {
        if (m_id == 0) {
            ui->titleLineEdit->clear();
            ui->textTextEdit->clear();
        } else {
            QMessageBox::information(this, "Success", "Note saved");
        }
    } else {
        QMessageBox::critical(this, "Error", "Note not saved");
    }
}


void NoteForm::on_closeButton_clicked()
{
    reject();
}
