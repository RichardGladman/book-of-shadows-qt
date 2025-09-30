#include "noteform.h"
#include "ui_noteform.h"

#include "notemodel.h"
#include "../settings/settingsmodel.h"

#include <QMessageBox>

extern SettingsModel settings;

NoteForm::NoteForm(QWidget *parent, int id, QString mode)
    : QDialog(parent)
    , ui(new Ui::NoteForm), m_default_title {""}, m_default_text {""}
{
    ui->setupUi(this);

    if (id != 0) {
        NoteModel model = NoteModel::load(id);
        ui->titleLineEdit->setText(model.title());
        ui->textTextEdit->setPlainText(model.text());
        m_id = id;
        m_default_title = model.title();
        m_default_text = model.text();
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
    if (settings.show_warnings() && (m_default_title != ui->titleLineEdit->text() ||
                                     m_default_text != ui->textTextEdit->toPlainText())) {
        QMessageBox::StandardButton button = QMessageBox::warning(this, "Unsaved Changes",
                    "You have unsaved changes, if you continue they will be lost. Do you want to continue?",
                    QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::No) {
            return;
        }
    }

    reject();
}
