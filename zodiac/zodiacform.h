#ifndef ZODIACFORM_H
#define ZODIACFORM_H

#include <QDialog>

namespace Ui {
class ZodiacForm;
}

class ZodiacForm : public QDialog
{
    Q_OBJECT

public:
    explicit ZodiacForm(QWidget *parent = nullptr, int id=0, QString mode="edit");
    ~ZodiacForm();

private slots:
    void on_saveButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::ZodiacForm *ui;

    int m_id {};

    QString m_default_name;
    QString m_default_description;
};

#endif // ZODIACFORM_H
