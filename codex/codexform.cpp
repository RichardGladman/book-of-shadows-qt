#include "codexform.h"
#include "codexmodel.h"
#include "ui_codexform.h"
#include "../settings/settingsmodel.h"

#include <QMessageBox>
#include <qmessagebox.h>

extern SettingsModel settings;

CodexForm::CodexForm(QWidget *parent, int id, QString mode) :
	QDialog(parent), ui(new Ui::CodexForm) 
{
	ui->setupUi(this);
	
	connect(ui->saveButton, &QPushButton::clicked, this, &CodexForm::handleSaveButtonClicked);
	connect(ui->closeButton, &QPushButton::clicked, this, &CodexForm::handleCloseButtonClicked);
	
	if (id != 0) {
		CodexModel model = CodexModel::load(id);
		ui->nameLineEdit->setText(model.name());
		ui->descriptionTextEdit->setPlainText(model.description());
		
		m_default_name = model.name();
		m_default_description = model.description();
		
		m_id = id;
	}
	
	if (mode == "view") {
		ui->nameLineEdit->setEnabled(false);
		ui->descriptionTextEdit->setEnabled(false);
		ui->saveButton->setEnabled(false);
		ui->saveButton->setVisible(false);
	}
}

CodexForm::~CodexForm() { delete ui; }

void CodexForm::handleCloseButtonClicked()
{
	if (settings.show_warnings() &&
			(m_default_name != ui->nameLineEdit->text() || 
				m_default_description != ui->descriptionTextEdit->toPlainText())) {
				QMessageBox::StandardButton button = QMessageBox::warning(this, tr("Unsaved Changes"),
					tr("You have unsaved changes. If you continue, they will be lost. Do you want to continue?"),
					QMessageBox::Yes | QMessageBox::No);
					
		if (button == QMessageBox::No) {
			return;
		}
		
		reject();
	}
}

void CodexForm::handleSaveButtonClicked()
{
	QString name = ui->nameLineEdit->text();
	QString description = ui->descriptionTextEdit->toPlainText();
	
	if (name.isEmpty())  {
		QMessageBox::critical(this, tr("Input Error"), tr("Name must not be empty"));
	}

	if (description.isEmpty())  {
		QMessageBox::critical(this, tr("Input Error"), tr("Description must not be empty"));
	}
	
	CodexModel model {m_id, name, description};
	
	if (model.save()) {
		if (m_id == 0) {
			ui->nameLineEdit->clear();
			ui->descriptionTextEdit->clear();
		} else {
			QMessageBox::information(this, tr("Success"), tr("Codex entry saved"));
		}
	} else {
		QMessageBox::critical(this, tr("Error"), tr("Codex entry NOT saved"));
	}
}