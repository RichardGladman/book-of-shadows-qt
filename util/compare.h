#pragma once

#include <QList>
#include <QListWidgetItem>

class Compare {
public:
    static bool areEqual(QList<QListWidgetItem*> items, QList<QString> defaults);
};