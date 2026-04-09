#include "codexform.h"
#include "ui_codexform.h"

CodexForm::CodexForm(QWidget *parent) :
	QDialog(parent), ui(new Ui::CodexForm) {
	ui->setupUi(this);
}

CodexForm::~CodexForm() { delete ui; }
