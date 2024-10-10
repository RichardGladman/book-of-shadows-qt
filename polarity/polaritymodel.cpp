#include "polaritymodel.h"

PolarityModel::PolarityModel(QString name, QString meaning) : PolarityModel {0, name, meaning, ""} {

}

PolarityModel::PolarityModel(QString name, QString meaning, QString image) : PolarityModel {0, name, meaning, image} {

}

PolarityModel::PolarityModel(int id, QString name, QString meaning, QString image) : m_id {id}, m_name {name}, m_image {image} {

}

PolarityModel::PolarityModel(const PolarityModel &source) : PolarityModel {source.m_id, source.m_name, source.m_meaning, source.m_image} {

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
