#include "competition.h"

competition::competition(int id,QString name, QString type, QDate date_debut, QDate date_fin, int nb_teams, QString reward) {
    this->id = id;
    this->name = name;
    this->type = type;
    this->date_debut = date_debut;
    this->date_fin = date_fin;
    this->nb_teams = nb_teams;
    this->reward = reward;
}
bool competition::add_competition() {
    QSqlQuery query;
    query.prepare("INSERT INTO competition (COMP_NAME, COMP_TYPE, START_DATE, END_DATE, NB_TEAMS, REWARD) VALUES (:name, :type, :date_debut, :date_fin, :nb_teams, :reward)");
    query.bindValue(":name", name);
    query.bindValue(":type", type);
    query.bindValue(":date_debut", date_debut);
    query.bindValue(":date_fin", date_fin);
    query.bindValue(":nb_teams", nb_teams);
    query.bindValue(":reward", reward);
    return query.exec();
}
competition competition::get_competition(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM competition WHERE ID_COMPETITION = :id");
    query.bindValue(":id", id);
    query.exec();
    competition c;
    while(query.next()) {
        c.set_id(query.value(0).toInt());
        c.set_name(query.value(1).toString());
        c.set_type(query.value(2).toString());
        c.set_date_debut(query.value(3).toDate());
        c.set_date_fin(query.value(4).toDate());
        c.set_nb_teams(query.value(5).toInt());
        c.set_reward(query.value(6).toString());
    }
    return c;
}
bool competition::update_competition(int id) {
    QSqlQuery query;
    query.prepare("UPDATE competition SET comp_name = :name, comp_type = :type, start_date = :date_debut, end_date = :date_fin, nb_teams = :nb_teams, reward = :reward WHERE id_competition = :id");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":type", type);
    query.bindValue(":date_debut", date_debut);
    query.bindValue(":date_fin",date_fin);
    query.bindValue(":nb_teams",nb_teams);
    query.bindValue(":reward", reward);
    return query.exec();
}
bool competition::delete_competition(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM competition WHERE id_competition = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlQueryModel* competition::show_competitions() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM competition");
    if (model->lastError().isValid()) {
        qDebug() << "Error executing query:" << model->lastError();
        return nullptr;  // Return null if the query failed
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Start Date"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("End Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Number of Teams"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Reward"));
    return model;
}
bool competition::exist_competition(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM competition WHERE id_competition = :id");
    query.bindValue(":id", id);
    query.exec();
    return query.next();
}
QSqlQueryModel* competition::show_competitions_by_name(QString name) {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM competition WHERE comp_name LIKE '%" + name + "%'");
    if (model->lastError().isValid()) {
        qDebug() << "Error executing query:" << model->lastError();
        return nullptr;  // Return null if the query failed
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Start Date"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("End Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Number of Teams"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Reward"));
    return model;
}
QSqlQueryModel* competition::show_competitions_by_date() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM competition ORDER BY start_date");
    if (model->lastError().isValid()) {
        qDebug() << "Error executing query:" << model->lastError();
        return nullptr;  // Return null if the query failed
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Start Date"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("End Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Number of Teams"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Reward"));
    return model;
}
QSqlQueryModel* competition::show_competitions_by_nb_teams() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM competition ORDER BY nb_teams");
    if (model->lastError().isValid()) {
        qDebug() << "Error executing query:" << model->lastError();
        return nullptr;  // Return null if the query failed
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Start Date"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("End Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Number of Teams"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Reward"));
    return model;
}
QSqlQueryModel* competition::show_competitions_by_type(QString type) {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM competition WHERE comp_type LIKE '%" + type + "%'");
    if (model->lastError().isValid()) {
        qDebug() << "Error executing query:" << model->lastError();
        return nullptr;  // Return null if the query failed
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Start Date"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("End Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Number of Teams"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Reward"));
    return model;
}
