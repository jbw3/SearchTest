#include <QKeyEvent>
#include "searchbar.h"

SearchBar::SearchBar(QWidget* parent/* = 0*/) :
    QLineEdit(parent)
{
}


void SearchBar::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        emit enterKeyPressed();
    }
    else
    {
        QLineEdit::keyPressEvent(event);
    }
}
