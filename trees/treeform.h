#ifndef TREEFORM_H
#define TREEFORM_H

#include <QDialog>

namespace Ui {
class TreeForm;
}

class TreeForm : public QDialog
{
    Q_OBJECT

public:
    explicit TreeForm(QWidget *parent = nullptr, int id = 0, QString mode = "edit");
    ~TreeForm();

private slots:
    void on_saveButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::TreeForm *ui;

    int m_id {};

    QString m_default_name;
    QString m_default_description;
};

#endif // TREEFORM_H
