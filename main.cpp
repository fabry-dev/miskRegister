#include "qfile.h"
#include "qdebug.h"
#include <QApplication>
#include "mainwindow.h"
#include "qwindow.h"
#include "qscreen.h"


#define PATH_DEFAULT "/home/fred/Dropbox/Taf/Cassiopee/miskRegister/files/"



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QString PATH;
    QStringList params = a.arguments();

    if(params.size()>1)
        PATH = params[1];
    else
        PATH=PATH_DEFAULT;
    bool HIDE_CURSOR=false;

    QFile file(PATH+"config.cfg");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"no config file";

    }
    else
    {

        QTextStream in(&file);

        QString  line;
        QString paramName,paramValue;
        QStringList params;

        while(!in.atEnd()) {
            line = in.readLine();
            line = (line.split("#"))[0];
            params = line.split("=");
            if(params.size()>=2)
            {
                paramName = params[0];
                paramValue = params[1];

                if (paramName.mid(0,6)=="CURSOR")
                    HIDE_CURSOR = (paramValue=="NO");
                else
                {
                    qDebug()<<"unknown parameter:"<<paramName<<" - "<<paramValue;
                }
            }
        }
        file.close();

    }


    if (HIDE_CURSOR)
    {
        QCursor cursor(Qt::BlankCursor);
        a.setOverrideCursor(cursor);
        a.changeOverrideCursor(cursor);
    }



    QScreen* screen1 = a.screens().at(0);
    mainWindow *mw = new mainWindow(NULL,PATH);
    mw->setGeometry(screen1->geometry().x(),screen1->geometry().y(),1080,1920);


    return a.exec();
}

