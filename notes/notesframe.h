#ifndef NOTESFRAME_H
#define NOTESFRAME_H

#include <QFrame>

namespace Ui {
class NotesFrame;
}

class NotesFrame : public QFrame
{
    Q_OBJECT

public:
    explicit NotesFrame(QWidget *parent = nullptr);
    ~NotesFrame();

private slots:
    void on_viewButton_clicked();

    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_deleteButton_clicked();

    void on_search_button_clicked();

    void on_noteTable_doubleClicked(const QModelIndex &index);

private:
    Ui::NotesFrame *ui;

    QString m_search_for;

    void loadData();
};

#endif // NOTESFRAME_H
