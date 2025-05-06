#ifndef ADDCOMPETITIONWINDOW_H
#define ADDCOMPETITIONWINDOW_H
#include <QWidget>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class AddCompetitionForm;
}
QT_END_NAMESPACE

class AddCompetitionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddCompetitionWindow(QWidget *parent = nullptr);
    ~AddCompetitionWindow(); // Declaration only

private slots:
    void on_pushButton_submit_clicked();

private:
    Ui::AddCompetitionForm *ui;
};

#endif // ADDCOMPETITIONWINDOW_H
