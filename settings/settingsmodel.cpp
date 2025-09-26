#include "settingsmodel.h"
#include <QSettings>

SettingsModel::SettingsModel() : SettingsModel { "", true } {}

SettingsModel::SettingsModel(const QString &data_directory, const bool show_warnings) :
    m_data_directory {data_directory}, m_show_warnings {show_warnings} {}

QString SettingsModel::data_directory()
{
    return m_data_directory;
}

bool SettingsModel::show_warnings()
{
    return m_show_warnings;
}

void SettingsModel::data_directory(QString &data_directory)
{
    m_data_directory = data_directory;
}

void SettingsModel::show_warnings(bool show_warnings)
{
    m_show_warnings = show_warnings;
}

void SettingsModel::load()
{
    QSettings settings("TheFifthContinent", "BookOfShadows");

    settings.beginGroup("Paths");
    m_data_directory = settings.value("datadir").toString();
    settings.endGroup();

    settings.beginGroup("Flags");
    m_show_warnings = settings.value("warnings").toBool();
    settings.endGroup();
}

void SettingsModel::save()
{
    QSettings settings("TheFifthContinent", "BookOfShadows");

    settings.beginGroup("Paths");
    settings.setValue("datadir", m_data_directory);
    settings.endGroup();

    settings.beginGroup("Flags");
    settings.setValue("warnings", m_show_warnings);
    settings.endGroup();
}
