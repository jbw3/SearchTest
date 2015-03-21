#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QLineEdit>

class SearchBar : public QLineEdit
{
    Q_OBJECT
public:
    explicit SearchBar(QWidget* parent = 0);

signals:
    void enterKeyPressed();

protected:
    virtual void keyPressEvent(QKeyEvent* event);
};

#endif // SEARCHBAR_H
