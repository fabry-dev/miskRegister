#include "picbutton.h"

picButton::picButton(QWidget *parent, uint w, QString file, QString clickFile, QString msg):QLabel(parent),msg(msg)
{
    pic.load(file);
    if(clickFile!="")
        onpic.load(clickFile);
    else
        onpic=pic.copy();

    if(w>0)
    {
        pic = pic.scaledToWidth(w);
        onpic = onpic.scaledToWidth(w);
    }

    resize(pic.size());
    setPixmap(pic);

}


void picButton::resetClick()
{
    setPixmap(pic);
}


void picButton::mousePressEvent(QMouseEvent *ev)
{

    setPixmap(onpic);
}



void picButton::mouseReleaseEvent(QMouseEvent *event)
{

    QTimer::singleShot(150,this,SLOT(resetClick()));
    emit clicked(msg);
}
