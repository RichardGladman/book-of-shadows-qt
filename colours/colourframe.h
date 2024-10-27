#ifndef COLOURFRAME_H
#define COLOURFRAME_H

#include <QFrame>

namespace Ui {
class ColourFrame;
}

class ColourFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ColourFrame(QWidget *parent = nullptr);
    ~ColourFrame();

private slots:
    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_viewButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::ColourFrame *ui;

    void loadData();
};

#endif // COLOURFRAME_H
