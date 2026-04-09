#ifndef CODEXFORM_H
#define CODEXFORM_H

#include <QDialog>

namespace Ui {
class CodexForm;
}

class CodexForm : public QDialog {
	Q_OBJECT

public:
	explicit CodexForm(QWidget *parent = nullptr);
	~CodexForm();

private:
	Ui::CodexForm *ui;
};

#endif // CODEXFORM_H
