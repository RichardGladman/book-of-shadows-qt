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

private:
    Ui::NotesFrame *ui;

    void loadData();
};

#endif // NOTESFRAME_H
