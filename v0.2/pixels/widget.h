#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QPainter>
#include <time.h>
#include <QTimer>
#include <QMouseEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

    static const int dMas = 20;
    static const int random = 20;

    QColor mas[dMas][dMas];

    static int masExit[7][7];
    static int masMaximize[7][7];
    static int masMinimize[7][7];

    static int masP[7][7];
    static int masI[7][7];
    static int masX[7][7];
    static int masE[7][7];
    static int masL[7][7];
    static int masS[7][7];

    int r,g,b;
    QPoint oldPos;
    int timerRandom;
    int moveX,moveY;
    bool effect;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void DrawMas(QPainter &p, int mas[7][7], int line);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);

private:
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    Ui::Widget *ui;
};

#endif // WIDGET_H
