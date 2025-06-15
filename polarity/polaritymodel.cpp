#include "polaritymodel.h"

#include <QFile>

QSqlQuery PolarityModel::list()
{
    QSqlQuery query;

    query.prepare("SELECT id, name FROM polarities ORDER BY name");
    query.exec();

    return query;
}

PolarityModel PolarityModel::load(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM polarities WHERE id=?");
    query.addBindValue(id);

    if (query.exec()) {
        if (query.next()) {
            PolarityModel polarity {query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString()};
            return polarity;
        }
    }

    return PolarityModel {0, "", "", ""};
}

PolarityModel PolarityModel::load(QString name)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM polarities WHERE name=?");
    query.addBindValue(name);

    if (query.exec()) {
        if (query.next()) {
            PolarityModel polarity {query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString()};
            return polarity;
        }
    }

    return PolarityModel {0, "", "", ""};
}

PolarityModel::PolarityModel(QString name, QString meaning) : PolarityModel {0, name, meaning, ""} {

}

PolarityModel::PolarityModel(QString name, QString meaning, QString image) : PolarityModel {0, name, meaning, image} {

}

PolarityModel::PolarityModel(int id, QString name, QString meaning, QString image) : m_id {id}, m_name {name}, m_meaning {meaning}, m_image {image} {

}

PolarityModel::PolarityModel(const PolarityModel &source) : PolarityModel {source.m_id, source.m_name, source.m_meaning, source.m_image} {

}

bool PolarityModel::save()
{
    QString sql;

    if (m_id == 0) {
        sql = "INSERT INTO polarities(name, meaning, image) VALUES(?, ?, ?)";
    } else {
        sql = "UPDATE polarities SET name=?, meaning=?, image=? WHERE id=?";
    }

    QSqlQuery query;
    query.prepare(sql);

    query.addBindValue(m_name);
    query.addBindValue(m_meaning);
    query.addBindValue(m_image);

    if (m_id != 0) {
        query.addBindValue(m_id);
    }

    return query.exec();
}

void PolarityModel::remove()
{
    if (!m_image.isEmpty()) {
        QFile file(m_image);
        file.remove();
    }

    QString sql = "DELETE FROM polarities WHERE id=?";

    QSqlQuery query;
    query.prepare(sql);

    query.addBindValue(m_id);

    query.exec();
}


int PolarityModel::id() const {
    return m_id;
}

QString PolarityModel::name() const {
    return m_name;
}

QString PolarityModel::meaning() const {
    return m_meaning;
}

QString PolarityModel::image() const {
    return m_image;
}

void PolarityModel::id(const int id) {
    m_id = id;
}

void PolarityModel::name(const QString &name) {
    m_name = name;
}

void PolarityModel::meaning(const QString &meaning) {
    m_meaning = meaning;
}

void PolarityModel::image(const QString &image) {
    m_image = image;
}

bool PolarityModel::operator==(const PolarityModel &rhs) const {
    return this->m_id == rhs.m_id && this->m_name == rhs.m_name && this->m_meaning == rhs.m_meaning && this->m_image == rhs.m_image;
}
