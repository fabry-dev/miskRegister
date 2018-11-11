#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <qobject.h>
#include "qlabel.h"
#include "picbutton.h"
#include "qstatemachine.h"
#include "qlineedit.h"
#include "qfontdatabase.h"
#include "keyboard.h"
#include <QtSql>
#include <QSqlQuery>



class lineEdit2: public QLineEdit
{
    Q_OBJECT
public:
    lineEdit2(QWidget *parent = nullptr):QLineEdit(parent)
    {installEventFilter(this);}

protected:
    bool eventFilter(QObject *object, QEvent *event)
    {
        if (event->type() == QEvent::FocusIn)
        {
            emit clicked();
        }
        return false;
    }



signals:
    void clicked();
};






class mainWindow : public QLabel
{
    Q_OBJECT
public:
    explicit mainWindow(QWidget *parent = nullptr,QString PATH="");
private:
    QString PATH;
    QPixmap bgPix;
    QFont font;
    std::vector<lineEdit2 *>les;
    std::vector<QRegularExpression> exprs;
    lineEdit2* activeLine;
    keyboard *k;
    void insertUser(QString name,QString email,QString phone,QString achievement);
    void createTable();
    void initDb();
    void getUsers();
protected:
    void mousePressEvent(QMouseEvent *ev);


private slots:
    void assignLine();
    void checkResults();
    void censure(QString txt);

};

#endif // MAINWINDOW_H
