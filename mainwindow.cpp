#include "mainwindow.h"










mainWindow::mainWindow(QWidget *parent, QString PATH) : QLabel(parent),PATH(PATH)
{
    showFullScreen();
    resize(1920,1080);
    bgPix.load(PATH+"background.png");
    thankyouPix.load(PATH+"thankyou.png");
      initPix.load(PATH+"start.png");

    initDb();

    int id = QFontDatabase::addApplicationFont(PATH+"police.otf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(family,32);

    for(int i = 0;i<5;i++)
    {
        lineEdit2 *le;
        le = new lineEdit2(this);
        le->setAlignment(Qt::AlignVCenter);
        le->resize(765,70);
        le->setFont(font);
        le->setStyleSheet("* { color : black;background-color:white; border: 2px solid black;}");
        le->show();
        les.push_back(le);
        connect(le,SIGNAL(clicked()),this,SLOT(assignLine()));

    }

    les[0]->move(30,70);
    exprs.push_back(QRegularExpression(""));
    les[1]->move(30,210);
    exprs.push_back(QRegularExpression("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$"));
    les[2]->move(30,350);
    exprs.push_back(QRegularExpression("^[0-9]{2,12}$"));
    les[3]->move(1120,70);
    les[3]->resize(570,70);
    exprs.push_back(QRegularExpression(""));
    les[4]->move(1120,210);
    les[4]->resize(570,70);
    exprs.push_back(QRegularExpression(""));

    te = new textEdit2(this);
    te->show();
    te->setStyleSheet("* { color : black;background-color:white; border: 2px solid black;}");
    te->move(1120,350);
    te->resize(770,180);
    connect(te,SIGNAL(clicked()),this,SLOT(assignZone()));
    te->setFont(font);

    rb1 = new QRadioButton(this);
    rb1->move(1330,168);

    rb1->show();
    rb2 = new QRadioButton(this);
    rb2->move(1520,168);
    rb2->show();

    rb1->setStyleSheet("    QRadioButton{width:50;}");
    connect(rb1,SIGNAL(clicked(bool)),this,SLOT(getRb1()));
    connect(rb2,SIGNAL(clicked(bool)),this,SLOT(getRb2()));

    rb1->toggle();
    rb1->setStyleSheet("QRadioButton::indicator { width: 35px; height: 35px;}");
    rb1->adjustSize();
    rb2->setStyleSheet("QRadioButton::indicator { width: 35px; height: 35px;}");
    rb2->adjustSize();
    k = new keyboard(this,PATH);
    k->move((width()-k->width())/2,height()-k->height());
    k->show();


    activeLine = les[0];
    connect(k,SIGNAL(nuTxt(QString)),this,SLOT(censure(QString)));

    go = new picButton(this,0,PATH+"SEND.png",PATH+"SEND2.png","");
    connect(go,SIGNAL(clicked(QString)),this,SLOT(checkResults()));

    go->move(1650,980);

    start = new picButton(this,0,PATH+"go.png",PATH+"go2.png","");
    connect(start,SIGNAL(clicked(QString)),this,SLOT(goMenu()));

    start->move((width()-start->width())/2,800);


    reset();

}


void mainWindow::reset()
{
    setPixmap(initPix);
    k->hide();
    rb1->hide();
    rb2->hide();
    te->hide();
    go->hide();
    for (auto le:les)
        le->hide();
    start->show();

}
void mainWindow::goMenu()
{
    setPixmap(bgPix);
    k->show();
    rb1->show();
    rb2->show();
    te->show();
    go->show();
    for (auto le:les)
        le->show();
    start->hide();
}





void mainWindow::getRb1()
{

    rb1->setChecked(rb2->isChecked());
    les[4]->setDisabled(false);

}

void mainWindow::getRb2()
{
    rb2->setChecked(rb1->isChecked());
    les[4]->setText("");
    les[4]->setDisabled(true);
    activeLine=les[3];
    k->reset(activeLine->text());
}



void mainWindow::censure(QString txt)
{
    int  lineNb = 0;


    if(activeLine!=NULL)
    {
        for(int i = 0;i<les.size();i++)
        {
            if(les[i]==activeLine)
            {

                lineNb = i;
                break;

            }

        }


        QRegularExpressionMatch match = exprs[lineNb].match(txt, 0, QRegularExpression::PartialPreferCompleteMatch);


        if( ((match.hasPartialMatch())||(match.hasMatch())||(txt=="")))
        {

            activeLine->setText(txt);
        }
        else
            k->reset(activeLine->text());

    }
    else
    {
        te->setText(txt);
        te->moveCursor ( QTextCursor::End );
    }


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

    getUsers();
}

void mainWindow::createTable()
{

    QSqlQuery query("CREATE TABLE players (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, email TEXT, phone TEXT, achievement TEXT, fullName TEXT, country TEXT, date TIMESTAMP)");

    bool success = query.exec();

    if(!success)
    {
        qDebug() << query.lastError();
    }
    else qDebug() << "table created";

}


void mainWindow::assignLine()
{

    activeLine = (lineEdit2*)sender();
    k->reset(activeLine->text());
}

void mainWindow::assignZone()
{
    activeLine = NULL;
    k->reset(te->toPlainText());


}

void mainWindow::checkResults()
{

    for(int i = 0;i<les.size()-1;i++)
    {
        QLineEdit *l=les[i];
        if(l->text().size()<1)
            return;
    }

    QString name,email,phone,achievement,fullName,country;
    name = les[0]->text();
    email = les[1]->text();
    phone = les[2]->text();


    country = les[3]->text();
    fullName = les[4]->text();
    achievement = te->toPlainText();

    for(auto l:les)
    {
        l->setText("");
    }
    te->setText("");

    insertUser(name,email,phone,achievement,fullName,country);

    setPixmap(thankyouPix);
    k->hide();
    rb1->hide();
    rb2->hide();
    te->hide();
    go->hide();
    for (auto le:les)
        le->hide();
    QTimer::singleShot(3000,this,SLOT(reset()));

}

void mainWindow::getUsers()
{
    QSqlQuery query;
    query.prepare("SELECT id,name,email,phone,achievement,fullName,country,date FROM players");
    query.exec();

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString email = query.value(2).toString();
        QString phone = query.value(3).toString();
        QString achievement = query.value(4).toString();
        QString fullName = query.value(5).toString();
        QString country = query.value(6).toString();
        QDateTime date = query.value(7).toDateTime();
        qDebug()<<id<<name<<email<<phone<<achievement<<fullName<<country<<date;
    }
}

void mainWindow::mousePressEvent(QMouseEvent *ev)
{
    qDebug()<<ev->pos();

}

void mainWindow::insertUser(QString name, QString email, QString phone, QString achievement, QString fullName, QString country)
{





    QDateTime timestamp = QDateTime::currentDateTime();

    QSqlQuery query;
    query.prepare("INSERT INTO players (name, email, phone,achievement,fullName,country, date) VALUES (:name,:email,:phone,:achievement,:fullname,:country,:datetime)");

    query.bindValue(":name", name);
    query.bindValue(":email", email);
    query.bindValue(":phone", phone);
    query.bindValue(":achievement", achievement);
    query.bindValue(":fullname", fullName);
    query.bindValue(":country", country);
    query.bindValue(":datetime", timestamp.toString("yyyy-MM-dd hh:mm:ss"));


    bool success = query.exec();
    if(!success)
    {
        qDebug() << query.lastError();
    }


}
