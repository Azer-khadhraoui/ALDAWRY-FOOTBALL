#include "../teamheaders/tododialog.h"
#include "ui_tododialog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

TodoDialog::TodoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TodoDialog)
{
    ui->setupUi(this);
    setWindowTitle("Add To-Do");

    // Populate the team ID combo box
    populateTeamComboBox();

    // Set default status to "Pending"
    ui->statusLineEdit->setText("Pending");
    ui->statusLineEdit->setReadOnly(true); // Make status read-only

    // Set current date as default for dateTimeEdit
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
}

TodoDialog::~TodoDialog()
{
    delete ui;
}

void TodoDialog::populateTeamComboBox()
{
    ui->teamComboBox->clear();
    QSqlQuery query("SELECT ID_TEAM, TEAM_NAME FROM HOTSTUFF.EQUIPE");
    while (query.next()) {
        int teamId = query.value(0).toInt();
        QString teamName = query.value(1).toString();
        ui->teamComboBox->addItem(QString("%1 - %2").arg(teamId).arg(teamName), teamId);
    }
}

void TodoDialog::on_saveButton_clicked()
{
    int teamId = ui->teamComboBox->currentData().toInt();
    QString todoText = ui->todoLineEdit->text().trimmed();
    QString status = ui->statusLineEdit->text();
    QDateTime dateTodo = ui->dateTimeEdit->dateTime();

    if (todoText.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "To-Do description cannot be empty!");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO TODO (IDTODO, IDTEAM, TODO, STATS, DATETODO) "
                  "VALUES (TODO_SEQ.NEXTVAL, :idteam, :todo, :stats, :datetodo)");
    query.bindValue(":idteam", teamId);
    query.bindValue(":todo", todoText);
    query.bindValue(":stats", status);
    query.bindValue(":datetodo", dateTodo);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "To-Do added successfully!");
        emit todoAdded();
        accept();
    } else {
        QMessageBox::critical(this, "Error", "Failed to add To-Do: " + query.lastError().text());
        qDebug() << "SQL Error:" << query.lastError().text();
    }
}

void TodoDialog::on_cancelButton_clicked()
{
    reject();
}
