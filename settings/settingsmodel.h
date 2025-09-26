#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include <QString>

class SettingsModel
{
public:
    SettingsModel();
    SettingsModel(const QString &data_directory, const bool show_warnings);

    QString data_directory();
    bool show_warnings();

    void data_directory(QString &data_directory);
    void show_warnings(bool show_warnings);

    void load();
    void save();

private:
    QString m_data_directory;
    bool m_show_warnings;
};

#endif // SETTINGSMODEL_H
