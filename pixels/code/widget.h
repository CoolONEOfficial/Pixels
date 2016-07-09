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

#ifdef ANDROID
    static const int dMas = 8;
#else
    static const int dMas = 15;
#endif

    static const int random = dMas;

    QColor mas[dMas][dMas];

    static int masExit[7][7];
    static int masSettings[7][7];

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

    int timerUpdateId;
    int timerRandomId;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void DrawMas(QPainter &p, int mas[7][7], int line);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);

private slots:
    void on_checkBox_effect_clicked(bool checked);

    void on_pushButton_back_released();

private:
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void addDark(QColor &cColor, int dark);
    void setSettingsVisible(bool visible);

    Ui::Widget *ui;
};

#endif // WIDGET_H
