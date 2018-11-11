#ifndef keyboard_H
#define keyboard_H

#include <QWidget>
#include <qobject.h>
#include "qlabel.h"
#include "picbutton.h"
#include "qstatemachine.h"
#include "qlineedit.h"
#include "qfontdatabase.h"

class keyboard : public QLabel
{
    Q_OBJECT
public:
    explicit keyboard(QWidget *parent = nullptr,QString PATH="");
private:
    QString PATH;
    QPixmap bgPix;
    void generateKeyboard();
    std::vector<picButton*> keys;
    QString buf;
protected:
    void mousePressEvent(QMouseEvent *ev);

private slots:
    void getKey(QString c);

public slots:
        void reset(QString);

signals:
    void nuTxt(QString txt);
};

#endif // keyboard_H
