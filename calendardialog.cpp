#include "calendardialog.h"
#include "ui_calendardialog.h"
#include <QSqlError>
#include <QMessageBox>
#include <QTextCharFormat>

CalendarDialog::CalendarDialog(int comp_id, int year, int month, QWidget *parent)
    : QDialog(parent)
    , m_comp_id(comp_id)
    , m_year(year)
    , m_month(month)
{
    setWindowTitle(QString("Calendar for %1 %2").arg(QLocale().monthName(month)).arg(year));
    setFixedSize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);

    m_calendarWidget = new QCalendarWidget(this);
    m_calendarWidget->setMinimumDate(QDate(year, month, 1));
    m_calendarWidget->setMaximumDate(QDate(year, month, QDate(year, month, 1).daysInMonth()));
    m_calendarWidget->setGridVisible(true);
    layout->addWidget(m_calendarWidget);

    // Set stylesheet for calendar
    m_calendarWidget->setStyleSheet(
        "QCalendarWidget { background-color: #2D3748; color: #FFFFFF; }"
        "QCalendarWidget QAbstractItemView:enabled { color: #FFFFFF; }"
        "QCalendarWidget QAbstractItemView:disabled { color: #4A4E58; }"
        "QCalendarWidget QWidget#qt_calendar_navigationbar { background-color: #F5A623; color: #1A2633; }"
        );

    // Connect date click signal
    connect(m_calendarWidget, &QCalendarWidget::clicked, this, &CalendarDialog::onDateClicked);

    // Highlight days with matches
    highlightMatchDays();
}

void CalendarDialog::highlightMatchDays()
{
    QSqlQuery query;
    query.prepare("SELECT date_m FROM match WHERE id_competition = :comp_id "
                  "AND EXTRACT(YEAR FROM date_m) = :year AND EXTRACT(MONTH FROM date_m) = :month");
    query.bindValue(":comp_id", m_comp_id);
    query.bindValue(":year", m_year);
    query.bindValue(":month", m_month);

    if (query.exec()) {
        while (query.next()) {
            QDate date = query.value(0).toDate();
            if (date.isValid()) {
                m_matchDates.append(date);
            }
        }
    } else {
        QMessageBox::critical(this, "Database Error", "Failed to retrieve match dates: " + query.lastError().text());
        return;
    }

    // Highlight match days
    QTextCharFormat highlightFormat;
    highlightFormat.setBackground(QColor("#5a7091"));
    highlightFormat.setForeground(Qt::white);

    for (const QDate &date : m_matchDates) {
        m_calendarWidget->setDateTextFormat(date, highlightFormat);
    }
}

void CalendarDialog::onDateClicked(const QDate &date)
{
    // Check if the clicked date has matches
    if (m_matchDates.contains(date)) {
        // Open MatchesDialog for the specific day
        MatchesDialog *dialog = new MatchesDialog(m_comp_id, date, this);
        dialog->exec();
        delete dialog;
    }
}
