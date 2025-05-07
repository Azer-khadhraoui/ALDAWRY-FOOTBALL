#include "addtododialog.h"

AddTodoDialog::AddTodoDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Add To-Do Task");

    // Initialize UI elements
    taskEdit = new QLineEdit(this);
    taskEdit->setPlaceholderText("Enter task description");
    dateEdit = new QDateTimeEdit(this);
    dateEdit->setCalendarPopup(true);
    dateEdit->setDateTime(QDateTime::currentDateTime());
    saveButton = new QPushButton("Save", this);
    cancelButton = new QPushButton("Cancel", this);

    // Create labels
    QLabel *taskLabel = new QLabel("Task:", this);
    QLabel *dateLabel = new QLabel("Due Date:", this);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(taskLabel);
    layout->addWidget(taskEdit);
    layout->addWidget(dateLabel);
    layout->addWidget(dateEdit);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);
    layout->setSpacing(10);
    layout->setContentsMargins(20, 20, 20, 20);

    // Styling
    setStyleSheet(R"(
        QDialog {
            background-color: #22252D;
            border-radius: 10px;
            color: #FFFFFF;
        }
        QLabel {
            background-color: transparent;
            color: #FFFFFF;
            font: 14pt "Arial";
        }
        QLineEdit, QDateTimeEdit {
            background-color: #2D3748;
            color: #FFFFFF;
            border: 1px solid #4A4E58;
            border-radius: 5px;
            padding: 5px;
            font: 12pt "Arial";
        }
        QLineEdit:focus, QDateTimeEdit:focus {
            border: 1px solid #F5A623;
        }
        QPushButton {
            background-color: #F5A623;
            color: #1A2633;
            border: 1px solid #4A4E58;
            border-radius: 5px;
            padding: 8px;
            font: 12pt "Arial";
        }
        QPushButton:hover {
            background-color: #ffdba2;
        }
        QPushButton:pressed {
            background-color: #d68f1e;
        }
    )");

    // Connect buttons
    connect(saveButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    // Set dialog size
    resize(350, 250);
}

QString AddTodoDialog::getTask() const {
    return taskEdit->text().trimmed();
}

QDateTime AddTodoDialog::getDate() const {
    return dateEdit->dateTime();
}
