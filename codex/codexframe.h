#pragma once

#include <QFrame>
#include <qtmetamacros.h>

namespace Ui {
class CodexFrame;
}

class CodexFrame : public QFrame
{
    Q_OBJECT

public:
    explicit CodexFrame(QWidget *parent = nullptr);
    ~CodexFrame();

private:
    Ui::CodexFrame *ui;

private slots:
    void handleAddClicked();
};
