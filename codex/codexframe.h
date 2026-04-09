#pragma once

#include <QFrame>
#include <qobject.h>
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
	QString m_search_for;

    Ui::CodexFrame *ui;
	void loadData();

private slots:
    void handleAddClicked();
    void handleEditClicked();
    void handleViewClicked();
    void handleDeleteClicked();
    void handleSearchClicked();
	
};
