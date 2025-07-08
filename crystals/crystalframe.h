#ifndef CRYSTALFRAME_H
#define CRYSTALFRAME_H

#include <QFrame>

namespace Ui {
class CrystalFrame;
}

class CrystalFrame : public QFrame
{
    Q_OBJECT

public:
    explicit CrystalFrame(QWidget *parent = nullptr);
    ~CrystalFrame();

private slots:
    void on_searchButton_clicked();
    void on_viewButton_clicked();
    void on_addButton_clicked();
    void on_editButton_clicked();
    void on_deleteButton_clicked();

private:
    Ui::CrystalFrame *ui;

    void loadData(const QString &term = "");
};

#endif // CRYSTALFRAME_H
