#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QWidget>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QLabel>
#include <QMovie>

namespace Ui {
class newwindow;
}

class newwindow : public QWidget
{
    Q_OBJECT

public:
    explicit newwindow(QWidget *parent = 0);
    virtual void paintEvent(QPaintEvent *); //畫面繪製
    virtual void keyPressEvent(QKeyEvent *event); //鍵盤輸入
    void Init(); //初始化畫面
    ~newwindow();

private slots:
    void windowUpdate(); //隨著時間刷新畫面

private:
    Ui::newwindow *ui;
    int score; //得分
    int combo; //combo數
    int timecount; //顯示計時器參數
    int timedisplay; //顯示計時器數字
    int x[500]; //記錄第i個鼓的x座標
    int style[500]; //紀錄第i個鼓是哪一種
    int starti, stopi; //鼓目前畫面上有starti~stopi
    int allowdrum; //避免鼓太過重疊
    int presswrong; //是否按錯或是空按
    int pressok; //顯示"可"
    int pressyes; //顯示"良"
    int pressballoon; //紀錄打幾下氣球
    int bombdisplaytime; //控制氣球爆炸後顯示多久
    int combo20; //20combo+5sec
    bool missyellowd; //錯過連打
    bool pressyellowd; //有打到連打
    bool gamepause; //暫停
    QTimer *gameTimer; //計時器
    QMediaPlayer * rdrum; //音效
    QMediaPlayer * bdrum;
    QMediaPlayer * cdrum;
    QMediaPlayer * combomusic;
    QMediaPlayer * johncena;
    QMediaPlayer * bgm;
    QMovie *johncenagif;

};

#endif // NEWWINDOW_H
