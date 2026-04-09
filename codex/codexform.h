#ifndef CODEXFORM_H
#define CODEXFORM_H

#include <QDialog>
#include <qobject.h>

namespace Ui {
class CodexForm;
}

class CodexForm : public QDialog {
	Q_OBJECT

public:
	explicit CodexForm(QWidget *parent = nullptr, int id = 0, QString mode = "edit");
	~CodexForm();

private:
	Ui::CodexForm *ui;
	
	int m_id {};
	
	QString m_default_name;
	QString m_default_description;
	
private slots:
	void handleSaveButtonClicked();
	void handleCloseButtonClicked();
};

#endif // CODEXFORM_H
