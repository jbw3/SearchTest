#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QRegularExpression>

namespace Ui
{
class Dialog;
}
class QStringListModel;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget* parent = 0);
    ~Dialog();

private:
    Ui::Dialog* ui;
    QStringList stringList;
    QStringListModel* listModel;
    QRegularExpression regEx;

    void populateList();
    void updateRegEx(const QString& searchStr);

private slots:
    void updateResults(QString searchText);
    void selectAll();
    void updateCheckBox();
    void updateListView();
};

#endif // DIALOG_H
