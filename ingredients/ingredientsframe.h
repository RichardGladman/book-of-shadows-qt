#pragma once

#include <QFrame>
#include <qobject.h>
#include <qtmetamacros.h>

namespace Ui {
class IngredientsFrame;
}

class IngredientsFrame : public QFrame
{
    Q_OBJECT

public:
    explicit IngredientsFrame(QWidget *parent = nullptr);
    ~IngredientsFrame();

private:
	QString m_search_for;

    Ui::IngredientsFrame *ui;
	void loadData();

private slots:
    void handleAddClicked();
    void handleEditClicked();
    void handleViewClicked();
    void handleDeleteClicked();
    void handleSearchClicked();
	
};
