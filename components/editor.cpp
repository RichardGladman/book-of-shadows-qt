#include "editor.h"
#include "ui_editor.h"

Editor::Editor(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::Editor)
{
    ui->setupUi(this);
}

Editor::~Editor()
{
    delete ui;
}


void Editor::on_copyButton_clicked()
{
    ui->textEdit->copy();
}


void Editor::on_cutButton_clicked()
{
    ui->textEdit->cut();
}


void Editor::on_pasteButton_clicked()
{
    ui->textEdit->paste();
}


void Editor::on_undoButton_clicked()
{
    ui->textEdit->undo();
}


void Editor::on_redoButton_clicked()
{
    ui->textEdit->redo();
}

