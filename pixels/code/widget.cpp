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

int Widget::masSettings[7][7]={ {0,0,0,0,0,0,0},
                          {0,0,1,1,1,1,0},
                          {0,1,0,0,0,0,0},
                          {0,0,1,1,1,0,0},
                          {0,0,0,0,0,1,0},
                          {0,1,1,1,1,0,0},
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
    // Start effect
    effect = true;

    // Clear all slots
    for(int x = 0; x<dMas; x++)
    {
        for(int y = 0; y<dMas; y++)
        {
            mas[x][y] = QColor(0,0,0);
        }
    }

    ui->setupUi(this);

    showFullScreen();

    // ide settings
    setSettingsVisible(false);

    // Timers
    timerRandomId = startTimer(1000/(dMas*2));
    timerUpdateId = startTimer(1000/60);

    update();
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
    int cellSizeX = width() / dMas;
    int cellSizeY = height() / dMas;

    QPainter p(this);

    p.setRenderHints(QPainter::Antialiasing);

    // Background
    p.setBrush(Qt::black);
    p.drawRect(0, 0, width(), height());

    // Grind
    if(ui->checkBox_grid->isChecked())
    {
        // Draw
        QPen pen;
        pen.setColor(Qt::white);
        p.setPen(pen);

        for(int x = 0; x<dMas; x++)
        {
            p.drawLine(x * cellSizeX, 0, x * cellSizeX, height());
        }

        for(int y = 0; y<dMas; y++)
        {
            p.drawLine(0, y * cellSizeY, width(), y * cellSizeY);
        }
    }

    // Pixels
    for(int x = 0; x<dMas; x++)
    {
        for(int y = 0; y<dMas; y++)
        {
            if(mas[x][y].saturation() > 0)
            {
                QColor bColor = mas[x][y];
                addDark(bColor, ui->slider_bright->maximum() - ui->slider_bright->value());

                // Set color
                p.setBrush(bColor);

                int shiftX = ((ui->slider_width->value()/10.0) * cellSizeX);
                int shiftY = ((ui->slider_height->value()/10.0) * cellSizeY);
                int width = cellSizeX + shiftX*2;
                int height = cellSizeY + shiftY*2;

                // Draw
                p.setPen(Qt::NoPen);
                p.drawRect(x * cellSizeX - shiftX,
                           y * cellSizeY - shiftY,
                           width,
                           height);
            }
        }
    }

    if(!ui->pushButton_back->isVisible())
    {
        p.setPen(Qt::SolidLine);

        // Draw images
        DrawMas(p,masExit,1);
        DrawMas(p,masSettings, 2);

        if(dMas >= 9)
        {
            DrawMas(p,masP, dMas);
            DrawMas(p,masI, dMas-1);
            DrawMas(p,masX, dMas-2);
            DrawMas(p,masE, dMas-3);
            DrawMas(p,masL, dMas-4);
            DrawMas(p,masS, dMas-5);
        }
    }
}

void Widget::timerEvent(QTimerEvent *event)
{
    // Timer random
    if(event->timerId() == timerRandomId)
    {
        // To black all colors
        for(int x = 0; x<dMas; x++)
        {
            for(int y = 0; y<dMas; y++)
            {
                addDark(mas[x][y], ui->slider_speed->value());
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
    }

    // Timer Update
    if(event->timerId() == timerUpdateId)
    {
        update();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    int cellSizeX = width()/dMas;
    int cellSizeY = height()/dMas;

    moveX = event->x();
    moveY = event->y();

    int cellX = moveX/cellSizeX;
    int cellY = moveY/cellSizeY;

    if(cellY != oldPos.y() || cellX != oldPos.x())
    {
        if(cellX>=0 && cellX<dMas && cellY>=0 && cellY<dMas)
        {
            QColor color;

            if(cellX == dMas-1 && cellY == 0 )
                color = QColor(255,0,0);
            else
                color = QColor(100+rand()%156, 100+rand()%156, 100+rand()%156);

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

    if(event->x()>width()-cellSizeX &&
       event->y()<cellSizeY)
    {
        close();
    }

    else if(event->x() > width() - cellSizeX*2 &&
             event->x() < width() - cellSizeX &&
             event->y() < cellSizeY)
    {
        setSettingsVisible(true);
    }
}

void Widget::addDark(QColor &cColor, int dark)
{
    QColor hsv = cColor.toHsv();
    int h = hsv.hue();
    int s = hsv.saturation();
    int v = hsv.value() - dark;

    if(v < 0)
        v = 0;

    if(v > 255)
        v = 255;

    hsv.setHsv(h,s,v);

    cColor = hsv.toRgb();
}

void Widget::setSettingsVisible(bool visible)
{
    ui->checkBox_effect->setVisible(visible);
    ui->checkBox_grid->setVisible(visible);

    ui->label->setVisible(visible);
    ui->label_bright->setVisible(visible);
    ui->label_height->setVisible(visible);
    ui->label_speed->setVisible(visible);
    ui->label_width->setVisible(visible);

    ui->pushButton_back->setVisible(visible);

    ui->slider_bright->setVisible(visible);
    ui->slider_height->setVisible(visible);
    ui->slider_speed->setVisible(visible);
    ui->slider_width->setVisible(visible);
}

void Widget::on_checkBox_effect_clicked(bool checked)
{
    effect = checked;
}

void Widget::on_pushButton_back_released()
{
    setSettingsVisible(false);
}
