#include "keyboard.h"

QStringList keysStr = (QStringList)"0"<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<""
                                     <<"Q"<<"W"<<"E"<<"R"<<"T"<<"Y"<<"U"<<"I"<<"O"<<"P"<<"DELL"
                                    <<"A"<<"S"<<"D"<<"F"<<"G"<<"H"<<"J"<<"K"<<"L"<<"Enter"<<""
                                   <<"Z"<<"X"<<"C"<<"V"<<"B"<<"N"<<"M"<<"POINT"<<"@"<<""<<""
                                  <<"-"<<"_"<<"ESPACE"<<"_"<<"-";


keyboard::keyboard(QWidget *parent, QString PATH) : QLabel(parent),PATH(PATH)
{

    resize(1080,500);
    bgPix.load(PATH+"backgroundKeyboard.png");

    setPixmap(bgPix);



    setStyleSheet("* { color : white;background-color: rgba(0, 0, 0, 0); }");

    generateKeyboard();
    reset("");
}




void keyboard::generateKeyboard()
{
    int w0 = 85;
    int w;
    int h = 85;
    int spaceX = 10;
    int spaceY = 10;
    int startX,startY;
    int bonusX = 0;
    int offsetx = 65;
    int offsety = 20;
    for (int i = 0;i<keysStr.size();i++)
    {




        if(i<11)
        {
            startX = offsetx;
            startY = offsety;
        }
        else if(i<22)
        {
            startX = offsetx-w0/2;
            startY = offsety+h+spaceY;
        }
        else if(i<33)
        {
            startX = offsetx;
            startY = offsety+2*(h+spaceY);
        }
        else if(i<44)
        {
            startX = offsetx+w0/2;
            startY = offsety+3*(h+spaceY);
        }
        else if(i<=51)
        {
            startX = offsetx+w0/2;
            startY = offsety+4*(h+spaceY);
        }


        if(keysStr[i]=="Enter")
        {
            w = 100;
        }
        else if (keysStr[i]=="ESPACE")
        {
            w = w0*5+4*spaceX;
        }
        else w = w0;

        if(i>46)
            bonusX =4*(spaceX+w0);
        else
            bonusX = 0;


        if(keysStr[i]!="")
        {
            picButton * p = new picButton(this,w,PATH+"keysOff/"+keysStr[i]+".png",PATH+"keysOn/"+keysStr[i]+".png",keysStr[i]);
            connect(p,SIGNAL(clicked(QString)),this,SLOT(getKey(QString)));
            p->show();
            p->move(startX+(w0+spaceX)*(i%11)+bonusX,startY);
            keys.push_back(p);
        }





    }


}


void keyboard::reset(QString nubuf)
{
    buf=nubuf;
}



#define MAX_SIZE 30

void keyboard::getKey(QString c)
{
    if(c=="DELL")
    {
        if(buf.size()>0)
        {
            buf = buf.remove(buf.size()-1,1);
            emit nuTxt(buf);
        }

    }
    else if(c=="Enter")
    {

    }
    else if(c=="POINT")
    {
        if(buf.size()<MAX_SIZE)
        {
            buf.append(".");
            emit nuTxt(buf);
        }

    }
    else if(c=="ESPACE")
    {


    }

    else
    {
        if(buf.size()<MAX_SIZE)
        {
            buf.append(c.toLower());
            emit nuTxt(buf);
        }

    }
}


void keyboard::mousePressEvent(QMouseEvent *ev)
{
    qDebug()<<ev->pos();

}
