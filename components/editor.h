#ifndef EDITOR_H
#define EDITOR_H

#include <QFrame>

namespace Ui {
class Editor;
}

class Editor : public QFrame
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);
    ~Editor();

private slots:

    void on_copyButton_clicked();
    void on_cutButton_clicked();
    void on_pasteButton_clicked();
    void on_undoButton_clicked();
    void on_redoButton_clicked();

private:
    Ui::Editor *ui;
};

#endif // EDITOR_H
