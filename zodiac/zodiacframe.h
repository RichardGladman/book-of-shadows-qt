#ifndef ZODIACFRAME_H
#define ZODIACFRAME_H

#include <QFrame>

namespace Ui {
class ZodiacFrame;
}

class ZodiacFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ZodiacFrame(QWidget *parent = nullptr);
    ~ZodiacFrame();

private slots:
    void on_viewButton_clicked();
    void on_addButton_clicked();
    void on_editButton_clicked();
    void on_deleteButton_clicked();

private:
    Ui::ZodiacFrame *ui;

    void loadData();
};

#endif // ZODIACFRAME_H
