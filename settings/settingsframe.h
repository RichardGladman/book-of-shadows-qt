#ifndef SETTINGSFRAME_H
#define SETTINGSFRAME_H

#include <QFrame>

namespace Ui {
class SettingsFrame;
}

class SettingsFrame : public QFrame
{
    Q_OBJECT

public:
    explicit SettingsFrame(QWidget *parent = nullptr);
    ~SettingsFrame();

private:
    Ui::SettingsFrame *ui;

private slots:
    void on_directoryButton_clicked();
    void on_saveButton_clicked();
};

#endif // SETTINGSFRAME_H
