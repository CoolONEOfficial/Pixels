#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <time.h>
#include <stdlib.h>
#include <QTimer>
#include <QMouseEvent>


int Widget::masExit[7][7]={ {0,0,0,0,0,0,0},
                  {0,1,0,0,0,1,0},
                  {0,0,1,0,1,0,0},
                  {0,0,0,1,0,0,0},
                  {0,0,1,0,1,0,0},
                  {0,1,0,0,0,1,0},
                  {0,0,0,0,0,0,0} };

int Widget::masMaximize[7][7]={ {0,0,0,0,0,0,0},
                          {0,1,1,1,1,1,0},
                          {0,1,1,1,1,1,0},
                          {0,1,0,0,0,1,0},
                          {0,1,0,0,0,1,0},
                          {0,1,1,1,1,1,0},
                          {0,0,0,0,0,0,0} };

int Widget::masMinimize[7][7]={ {0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0},
                                {0,1,1,1,1,1,0},
                                {0,1,1,1,1,1,0},
                                {0,0,0,0,0,0,0} };

int Widget::masP[7][7]={ {0,0,0,0,0,0,0},
                                {0,1,1,1,1,1,0},
                                {0,1,1,0,0,1,0},
                                {0,1,1,1,1,1,0},
                                {0,1,1,0,0,0,0},
                                {0,1,1,0,0,0,0},
                                {0,0,0,0,0,0,0} };

int Widget::masI[7][7]={ {0,0,0,0,0,0,0},
                                {0,0,1,1,1,0,0},
                                {0,0,0,1,0,0,0},
                                {0,0,0,1,0,0,0},
                                {0,0,0,1,0,0,0},
                                {0,0,1,1,1,0,0},
                                {0,0,0,0,0,0,0} };

int Widget::masX[7][7]={ {0,0,0,0,0,0,0},
                                {0,1,1,0,1,1,0},
                                {0,0,1,1,1,0,0},
                                {0,0,0,1,0,0,0},
                                {0,0,1,1,1,0,0},
                                {0,1,1,0,1,1,0},
                                {0,0,0,0,0,0,0} };

int Widget::masE[7][7]={ {0,0,0,0,0,0,0},
                                {0,1,1,1,1,1,0},
                                {0,1,1,0,0,0,0},
                                {0,1,1,1,1,1,0},
                                {0,1,1,0,0,0,0},
                                {0,1,1,1,1,1,0},
                                {0,0,0,0,0,0,0} };

int Widget::masL[7][7]={ {0,0,0,0,0,0,0},
                                {0,1,1,0,0,0,0},
                                {0,1,1,0,0,0,0},
                                {0,1,1,0,0,0,0},
                                {0,1,1,0,0,0,0},
                                {0,1,1,1,1,1,0},
                                {0,0,0,0,0,0,0} };

int Widget::masS[7][7]={ {0,0,0,0,0,0,0},
                                {0,1,1,1,1,1,0},
                                {0,1,1,0,0,0,0},
                                {0,1,1,1,1,1,0},
                                {0,0,0,0,1,1,0},
                                {0,1,1,1,1,1,0},
                                {0,0,0,0,0,0,0} };

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    effect = true;

    ui->setupUi(this);

    showFullScreen();

    for(int x = 0; x<dMas; x++)
    {
        for(int y = 0; y<dMas; y++)
        {
            mas[x][y] = QColor(0,0,0);
        }
    }

    startTimer(20);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::DrawMas(QPainter &p,int mas[7][7],int line)
{
    int cellSizeX = width()/dMas;
    int cellSizeY = height()/dMas;

    p.setBrush(QColor(255,255,255));

    for(int x = 0; x<7; x++)
    {
        for(int y = 0; y<7; y++)
        {
            if(mas[y][x] == 1)
            {
                p.drawRect(width()-(cellSizeX*line)+(x*cellSizeX/7),
                               (cellSizeY/7)*y,
                               cellSizeX/7,
                               cellSizeY/7);
            }
        }
    }

}

void Widget::paintEvent(QPaintEvent *)
{
    int cellSizeX = width()/dMas;
    int cellSizeY = height()/dMas;

    QPainter p(this);

    p.setRenderHints(QPainter::Antialiasing,true);

    for(int x = 0; x<dMas; x++)
    {
        for(int y = 0; y<dMas; y++)
        {
            p.setBrush(mas[x][y]);
            p.drawRect(x * cellSizeX,
                       y * cellSizeY,
                       cellSizeX,
                       cellSizeY);
        }
    }

    p.setBrush(Qt::black);
    p.drawRect(0,height()-4,width(),4);

    DrawMas(p,masExit,1);
    DrawMas(p,masMaximize,2);
    DrawMas(p,masMinimize,3);

    DrawMas(p,masP,20);
    DrawMas(p,masI,19);
    DrawMas(p,masX,18);
    DrawMas(p,masE,17);
    DrawMas(p,masL,16);
    DrawMas(p,masS,15);
}

void Widget::timerEvent(QTimerEvent *)
{
    QColor hsv;

    int h,s,v;

    for(int x = 0; x<dMas; x++)
    {
        for(int y = 0; y<dMas; y++)
        {
            hsv = mas[x][y].toHsv();
            h = hsv.hue();
            s = hsv.saturation();
            v = hsv.value();
            v-=6;
            if(v<0)
                v = 0;
            hsv.setHsv(h,s,v);
            mas[x][y] = hsv.toRgb();
        }
    }

    if(random!=-1 && effect)
    {
        timerRandom++;

        if(timerRandom > random)
        {
            timerRandom = 0;
            int x = 1+rand()%(dMas-2);
            int y = 1+rand()%(dMas-2);
            int r = rand()%255;
            int g = rand()%255;
            int b = rand()%255;
            mas[x][y] = QColor(r,g,b);
            mas[x+1][y] = QColor(r/2,g/2,b/2);
            mas[x][y+1] = QColor(r/2,g/2,b/2);
            mas[x-1][y] = QColor(r/2,g/2,b/2);
            mas[x][y-1] = QColor(r/2,g/2,b/2);
        }
    }

    update();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    int cellSizeX = width()/dMas;
    int cellSizeY = height()/dMas;

    moveX = event->x();
    moveY = event->y();

    int cellX = moveX/cellSizeX;
    int cellY = moveY/cellSizeY;

    if(cellY!=oldPos.y() || cellX!=oldPos.x())
    {
        if(cellX>=0 && cellX<dMas && cellY>=0 && cellY<dMas)
        {
            QColor color;


            if(cellX == dMas-1 && cellY == 0 )
                color = QColor(255,0,0);
            else
            if(cellX == dMas-2 && cellY == 0 )
                color = QColor(255,255,255);
            else
            if(cellX == dMas-3 && cellY == 0 )
                color = QColor(255,255,255);
            else
                color = QColor(100+rand()%156,100+rand()%156,100+rand()%156);

            mas[cellX][cellY] = color;
        }


    }

    oldPos.setX(cellX);
    oldPos.setY(cellY);

    update();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    int cellSizeX = width()/dMas;
    int cellSizeY = height()/dMas;

    if(event->x()>width()-cellSizeX && event->y()<cellSizeY)
    {
        close();
        return;
    }

    if(event->x()>width()-(cellSizeX*2) && event->y()<cellSizeY)
    {
        showFullScreen();
        return;
    }

    if(event->x()>width()-(cellSizeX*3) && event->y()<cellSizeY)
    {
        showMaximized();
        return;
    }
}
