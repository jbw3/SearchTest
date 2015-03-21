#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QStringListModel>
#include <QTime>

inline bool isReservedChar(const QChar& ch)
{
    return (ch == '.' || ch == '*' || ch == '\\' || ch == '+' || ch == '?' || ch == '^' || ch == '$' ||
            ch == '|' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}');
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    regEx.setPatternOptions(QRegularExpression::CaseInsensitiveOption);

    populateList();

    listModel = new QStringListModel(this);
    listModel->setStringList(stringList);
    ui->listView->setModel(listModel);
    ui->listView->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->selectAllCheckBox->setTristate(true);

    connect(ui->searchBar, SIGNAL(textEdited(QString)), this, SLOT(updateResults(QString)));
    connect(ui->searchBar, SIGNAL(enterKeyPressed()), this, SLOT(selectAll()));

    //connect(ui->listView, SIGNAL(clicked(QModelIndex)), this, SLOT(updateCheckBox()));
    connect(ui->listView, SIGNAL(activated(QModelIndex)), this, SLOT(updateCheckBox()));
    connect(ui->listView, SIGNAL(pressed(QModelIndex)), this, SLOT(updateCheckBox()));

    connect(ui->selectAllCheckBox, SIGNAL(clicked()), this, SLOT(updateListView()));
    //connect(ui->listView, SIGNAL(pressed(QModelIndex)), this, SLOT(updateCheckBox()));
    //connect(ui->listView, SIGNAL(activated(QModelIndex)), this, SLOT(updateCheckBox()));

    updateResults("");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::populateList()
{
    stringList << "Al"
               << "Alan"
               << "Albert"
               << "Bill"
               << "Billy"
               << "Jack"
               << "Jim"
               << "Jimmy"
               << "John"
               << "john.wilkes"
               << "johnbwilkes"
               << "Jon"
               << "Jonathan"
               << "Lee"
               << "Zack"
               << "X()"
               << "X{"
               << "{ xyz }";

    for (int i = 0; i < 1000; ++i)
    {
        stringList.append(QString("This is test number ") + QString::number(i));
    }
}

void Dialog::updateRegEx(const QString& searchStr)
{
    QString regExStr;
    foreach (QChar ch, searchStr)
    {
        regExStr.append(".*");
        if (isReservedChar(ch))
        {
            regExStr.append('\\');
        }
        regExStr.append(ch);
    }
    regExStr.append(".*");

    regEx.setPattern(regExStr);
}

void Dialog::updateResults(QString searchText)
{
    QTime time;
    time.start();

    if (searchText.isEmpty())
    {
        listModel->setStringList(stringList);
    }
    else
    {
        updateRegEx(searchText);

        QStringList tempList;
        QRegularExpressionMatch match;
        foreach (QString str, stringList)
        {
            match = regEx.match(str);
            if (match.hasMatch())
            {
                tempList.append(str);
            }
        }

        listModel->setStringList(tempList);
    }

    updateCheckBox();

    int msec = time.elapsed();
    qDebug() << msec << "ms";
}

void Dialog::selectAll()
{
    ui->listView->selectAll();
    updateCheckBox();
    ui->listView->setFocus();
}

void Dialog::updateCheckBox()
{
    int count = ui->listView->selectionModel()->selectedIndexes().length();
    if (count == 0)
    {
        ui->selectAllCheckBox->setCheckState(Qt::Unchecked);
    }
    else if (count == listModel->stringList().length())
    {
        ui->selectAllCheckBox->setCheckState(Qt::Checked);
    }
    else
    {
        ui->selectAllCheckBox->setCheckState(Qt::PartiallyChecked);
    }
}

void Dialog::updateListView()
{
    qDebug() << __FUNCTION__;

    switch (ui->selectAllCheckBox->checkState())
    {
    case Qt::Unchecked:
        ui->listView->clearSelection();
        break;
    case Qt::PartiallyChecked:
        ui->selectAllCheckBox->setCheckState(Qt::Checked);
    case Qt::Checked:
        ui->listView->selectAll();
        break;
    default:
        qDebug() << "ERROR: Unknown check button state!";
        break;
    }

    ui->listView->setFocus();
}
