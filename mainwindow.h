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
#include "qtextedit.h"
#include "qradiobutton.h"

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

class textEdit2: public QTextEdit
{
    Q_OBJECT
public:
    textEdit2(QWidget *parent = nullptr):QTextEdit(parent)
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
    QPixmap bgPix,thankyouPix,initPix;
    QFont font;
    textEdit2 *te;
    std::vector<lineEdit2 *>les;
    std::vector<QRegularExpression> exprs;
    lineEdit2* activeLine;
    keyboard *k;
    void insertUser(QString name, QString email, QString phone, QString achievement, QString fullName, QString country);
    void createTable();
    void initDb();
    void getUsers();
    QRadioButton *rb1,*rb2;
     picButton *go,*start;
protected:
    void mousePressEvent(QMouseEvent *ev);


private slots:
    void assignLine();
    void checkResults();
    void censure(QString txt);
    void assignZone();
    void getRb1(void);
    void getRb2(void);
    void reset();
    void goMenu();

};

#endif // MAINWINDOW_H
