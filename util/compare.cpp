#include "compare.h"

bool Compare::areEqual(QList<QListWidgetItem*> items, QList<QString> defaults) {
    if (items.length() != defaults.length()) {
        return false;
    }

    for (int i = 0; i < items.length(); ++i) {
        if (items[i]->text() != defaults[i]) {
            return false;
        }
    }

    return true;
}