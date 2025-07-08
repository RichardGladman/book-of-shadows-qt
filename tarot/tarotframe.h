#ifndef TAROTFRAME_H
#define TAROTFRAME_H

#include <QFrame>

namespace Ui {
class TarotFrame;
}

class TarotFrame : public QFrame
{
    Q_OBJECT

public:
    explicit TarotFrame(QWidget *parent = nullptr);
    ~TarotFrame();

private slots:
    void on_searchButton_clicked();
    void on_viewButton_clicked();
    void on_addButton_clicked();
    void on_editButton_clicked();
    void on_deleteButton_clicked();

private:
    Ui::TarotFrame *ui;

    void loadData(const QString &term = "");
};

#endif // TAROTFRAME_H
