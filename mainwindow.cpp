#include "mainwindow.h"










mainWindow::mainWindow(QWidget *parent, QString PATH) : QLabel(parent),PATH(PATH)
{
    showFullScreen();
    resize(1080,1920);
    bgPix.load(PATH+"background.png");
    setPixmap(bgPix);


    initDb();

    int id = QFontDatabase::addApplicationFont(PATH+"font.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(family,50);

    for(int i = 0;i<4;i++)
    {
        lineEdit2 *le;
        le = new lineEdit2(this);
        le->resize(780,110);
        le->setFont(font);
        le->setStyleSheet("* { color : white;background-color:transparent; }");
        le->show();
        les.push_back(le);
        connect(le,SIGNAL(clicked()),this,SLOT(assignLine()));

    }

    les[0]->move(150,175);
    les[1]->move(150,495);
    les[2]->move(150,820);
    les[3]->move(150,1155);


    k = new keyboard(this,PATH);
    k->move(0,height()-k->height());
    k->show();
    connect(k,SIGNAL(nuTxt(QString)),les[0],SLOT(setText(QString)));


    picButton *go = new picButton(this,0,PATH+"submit.png",PATH+"submit2"
                                                                ".png","");
    connect(go,SIGNAL(clicked(QString)),this,SLOT(checkResults()));
    go->show();
    go->move((width()-go->width())/2,1300);



}




void mainWindow::initDb()
{

    const QString DRIVER("QSQLITE");
    QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
    db.setHostName("hostname");
    db.setDatabaseName(PATH+"miskdb");
    db.setUserName("user");
    db.setPassword("password");

    if(!db.open())
        qWarning() << "ERROR: " << db.lastError();

    qDebug()<<db.tables();

    //qDebug()<<db.record("players");
    //dropTable();
    //createTable();
    createTable();

    //getUsers();
}


void mainWindow::createTable()
{

    QSqlQuery query("CREATE TABLE players (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, email TEXT, phone TEXT, achievement TEXT, date TIMESTAMP)");

    bool success = query.exec();

    if(!success)
    {
        qDebug() << query.lastError();
    }
    else qDebug() << "table created";

}



void mainWindow::assignLine()
{

    lineEdit2* line = (lineEdit2*)sender();
    disconnect(k,0,0,0);

    connect(k,SIGNAL(nuTxt(QString)),line,SLOT(setText(QString)));
    k->reset(line->text());
}


void mainWindow::checkResults()
{

    for(auto l:les)
    {
        if(l->text().size()<1)
            return;
    }

    QString name,email,phone,achievement;
    name = les[0]->text();
    email = les[1]->text();
    phone = les[2]->text();
    achievement = les[3]->text();

    for(auto l:les)
    {
       l->setText("");
    }

    insertUser(name,email,phone,achievement);

}


void mainWindow::getUsers()
{
    QSqlQuery query;
    query.prepare("SELECT id,name,email,phone,achievement,date FROM players");
    query.exec();

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString email = query.value(2).toString();
        QString phone = query.value(3).toString();
        QString achievement = query.value(4).toString();
        QDateTime date = query.value(5).toDateTime();
        qDebug()<<id<<name<<email<<phone<<achievement<<date;
    }
}

void mainWindow::mousePressEvent(QMouseEvent *ev)
{
    qDebug()<<ev->pos();

}

void mainWindow::insertUser(QString name,QString email,QString phone,QString achievement)
{



qDebug()<<name<<email<<phone<<achievement;


QDateTime timestamp = QDateTime::currentDateTime();

QSqlQuery query;
query.prepare("INSERT INTO players (name, email, phone,achievement, date) VALUES (:name,:email,:phone,:achievement,:datetime)");

query.bindValue(":name", name);
query.bindValue(":email", email);
query.bindValue(":phone", phone);
query.bindValue(":achievement", achievement);
query.bindValue(":datetime", timestamp.toString("yyyy-MM-dd hh:mm:ss"));


bool success = query.exec();
if(!success)
{
    qDebug() << query.lastError();
}


}
