#ifndef CALENDARDIALOG_H
#define CALENDARDIALOG_H

#include <QDialog>
#include <QCalendarWidget>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QDate>
#include "matchesdialog.h"

class CalendarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarDialog(int comp_id, int year, int month, QWidget *parent = nullptr);

private slots:
    void onDateClicked(const QDate &date);

private:
    void highlightMatchDays();

    int m_comp_id;
    int m_year;
    int m_month;
    QCalendarWidget *m_calendarWidget;
    QVector<QDate> m_matchDates;
};

#endif // CALENDARDIALOG_H
