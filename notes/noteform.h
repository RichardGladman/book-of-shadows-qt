#ifndef NOTEFORM_H
#define NOTEFORM_H

#include <QDialog>

namespace Ui {
class NoteForm;
}

class NoteForm : public QDialog
{
    Q_OBJECT

public:
    explicit NoteForm(QWidget *parent = nullptr, int id = 0, QString mode = "edit");
    ~NoteForm();

private slots:
    void on_saveButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::NoteForm *ui;

    int m_id {};

    QString m_default_title;
    QString m_default_text;
};

#endif // NOTEFORM_H
