#include "newwindow.h"
#include "ui_newwindow.h"
#include <QPainter>
#include <time.h>
#include <QtCore>
#include <Qtgui>
#include <QTimer>
#include <QString>
#include <QMessageBox>
#include <QTextStream>
#include <QLCDNumber>
#include <QPixmap>


newwindow::newwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newwindow)
{
    ui->setupUi(this);
    rdrum = new QMediaPlayer(); //音效
    rdrum->setMedia(QUrl("qrc:/pics/rsound.wav"));
    bdrum = new QMediaPlayer();
    bdrum->setMedia(QUrl("qrc:/pics/bsound.wav"));
    cdrum = new QMediaPlayer();
    cdrum->setMedia(QUrl("qrc:/pics/combomusic.wav"));
    combomusic = new QMediaPlayer();
    combomusic->setMedia(QUrl("qrc:/pics/combo.wav"));
    combomusic->setVolume(70);
    johncena = new QMediaPlayer();
    johncena->setMedia(QUrl("qrc:/pics/johncenamusic.wav"));
    johncena->setVolume(150);
    bgm = new QMediaPlayer();
    bgm->setMedia(QUrl("qrc:/pics/FB.mp3"));
    bgm->setVolume(80);
    johncenagif = new QMovie(":/pics/johngif.gif");//動圖
    ui->label_6->setMovie(johncenagif);
    Init(); //初始化遊戲介面
}

void newwindow::Init()
{
    bgm->play(); //背景音樂
    score = 0; //初始化得分
    combo = 0; //初始combo
    timecount = -300; //初始化顯示計時器參數，-30為開始前倒數3秒
    timedisplay = 30; //初始化秒數為30秒
    this->ui->lcdNumber->display(timedisplay);
    srand(time(NULL));
    for(int i=1;i<500;i++)
    {
        x[i]=450; //初始化每個鼓生成位置
        style[i]=rand()%4; //隨機每次產生的鼓是哪一種
        if(rand()%20==0) //約每20個鼓出現一個連打or氣球
        {
            if(rand()%2==0)style[i]=4;
            else style[i]=5;
        }
    }
    starti=1; //初始化沒有鼓生成
    stopi=1;
    allowdrum=0;
    presswrong=0; //初始化圖片顯示參數
    pressok=0;
    pressyes=0;
    pressballoon=0;
    bombdisplaytime=0;
    combo20=0;
    missyellowd=false;
    pressyellowd=false;
    gamepause=false;
    gameTimer = new QTimer(this); //初始化計時器
    connect(gameTimer,SIGNAL(timeout()),this,SLOT(windowUpdate())); //隨時間更新畫面
    gameTimer->start(10); //區間設為100毫秒，即每秒刷新10次畫面
}

void newwindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, 600, 400, QPixmap(":/pics/bg.png")); //背景
    painter.drawPixmap(100,107,100,100,QPixmap(":/pics/target.png")); //準心
    if(combo>99) painter.drawPixmap(192,42,100,100,QPixmap(":/pics/combo100.png")); //combo
    else if(combo>0) painter.drawPixmap(170,40,180,100,QPixmap(":/pics/combo.png"));
    if(combo>0 && combo<10) //combo數字
    {
        switch(combo)
        {
            case 1: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-1.png")); break;
            case 2: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-2.png")); break;
            case 3: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-3.png")); break;
            case 4: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-4.png")); break;
            case 5: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-5.png")); break;
            case 6: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-6.png")); break;
            case 7: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-7.png")); break;
            case 8: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-8.png")); break;
            case 9: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-9.png")); break;
        }
    }
    else if(combo>0 && combo>=10 && combo<100)
    {
        switch(combo/10)
        {
            case 1: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-1.png")); break;
            case 2: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-2.png")); break;
            case 3: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-3.png")); break;
            case 4: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-4.png")); break;
            case 5: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-5.png")); break;
            case 6: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-6.png")); break;
            case 7: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-7.png")); break;
            case 8: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-8.png")); break;
            case 9: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-9.png")); break;
        }
        switch(combo%10)
        {
            case 0: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-0.png")); break;
            case 1: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-1.png")); break;
            case 2: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-2.png")); break;
            case 3: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-3.png")); break;
            case 4: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-4.png")); break;
            case 5: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-5.png")); break;
            case 6: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-6.png")); break;
            case 7: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-7.png")); break;
            case 8: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-8.png")); break;
            case 9: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-9.png")); break;
        }
    }
    else if(combo>0 && combo>=100)
    {

        switch(combo/100)
        {
            case 1: painter.drawPixmap(196,65,30,70,QPixmap(":/pics/default-1.png")); break;
            case 2: painter.drawPixmap(196,65,30,70,QPixmap(":/pics/default-2.png")); break;
            case 3: painter.drawPixmap(196,65,30,70,QPixmap(":/pics/default-3.png")); break;
            case 4: painter.drawPixmap(196,65,30,70,QPixmap(":/pics/default-4.png")); break;
            case 5: painter.drawPixmap(196,65,30,70,QPixmap(":/pics/default-5.png")); break;
            case 6: painter.drawPixmap(196,65,30,70,QPixmap(":/pics/default-6.png")); break;
            case 7: painter.drawPixmap(196,65,30,70,QPixmap(":/pics/default-7.png")); break;
            case 8: painter.drawPixmap(196,65,30,70,QPixmap(":/pics/default-8.png")); break;
            case 9: painter.drawPixmap(196,65,30,70,QPixmap(":/pics/default-9.png")); break;
        }
        switch((combo/10)%10)
        {
            case 0: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-0.png")); break;
            case 1: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-1.png")); break;
            case 2: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-2.png")); break;
            case 3: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-3.png")); break;
            case 4: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-4.png")); break;
            case 5: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-5.png")); break;
            case 6: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-6.png")); break;
            case 7: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-7.png")); break;
            case 8: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-8.png")); break;
            case 9: painter.drawPixmap(226,65,30,70,QPixmap(":/pics/default-9.png")); break;
        }
        switch(combo%10)
        {
            case 0: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-0.png")); break;
            case 1: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-1.png")); break;
            case 2: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-2.png")); break;
            case 3: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-3.png")); break;
            case 4: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-4.png")); break;
            case 5: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-5.png")); break;
            case 6: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-6.png")); break;
            case 7: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-7.png")); break;
            case 8: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-8.png")); break;
            case 9: painter.drawPixmap(256,65,30,70,QPixmap(":/pics/default-9.png")); break;
        }
    }
    srand(time(0));
    for(int i=stopi-1; i>=starti; i--) //由後往前生成，避免覆蓋擋住
    {
        switch(style[i])//生成鼓
        {
            case 1: painter.drawPixmap(x[i],130,50,50,QPixmap(":/pics/srd.png")); break;
            case 2: painter.drawPixmap(x[i],130,50,50,QPixmap(":/pics/sbd.png")); break;
            case 3: painter.drawPixmap(x[i],107,90,90,QPixmap(":/pics/brd.png")); break;
            case 0: painter.drawPixmap(x[i],107,90,90,QPixmap(":/pics/bbd.png")); break;
            case 4: painter.drawPixmap(x[i],125,280,60,QPixmap(":/pics/yellowd.png")); break;
            case 5:
                if(pressballoon<6)
                    painter.drawPixmap(x[i],100,180,110,QPixmap(":/pics/bullon_1.png"));
                else if(pressballoon<12)
                    painter.drawPixmap(x[i],100,180,110,QPixmap(":/pics/bullon_2.png"));
                else if(pressballoon<18)
                    painter.drawPixmap(x[i],100,180,110,QPixmap(":/pics/bullon_3.png"));
                else if(pressballoon<24)
                    painter.drawPixmap(x[i],100,180,110,QPixmap(":/pics/bullon_4.png"));
                else if(pressballoon<29)
                    painter.drawPixmap(x[i],100,180,110,QPixmap(":/pics/bullon_5.png"));
                else if(pressballoon<30)
                    painter.drawPixmap(x[i],100,180,110,QPixmap(":/pics/bullon_6.png"));
                break;
        }
    }
    switch((timecount/20)%4)  //左邊鼓動畫
    {
        case 0: painter.drawPixmap(0,105,110,90,QPixmap(":/pics/a1.png")); break;
        case 1: painter.drawPixmap(0,105,110,90,QPixmap(":/pics/a2.png")); break;
        case 2: painter.drawPixmap(0,105,110,90,QPixmap(":/pics/a3.png")); break;
        case 3: painter.drawPixmap(0,105,110,90,QPixmap(":/pics/a2.png")); break;
    }
    if(presswrong>0) //按錯或空按顯示"不可"
    {
        painter.drawPixmap(66,72,165,165,QPixmap(":/pics/no.png"));
        combo = 0; //有出錯，combo斷
        presswrong--;
    }
    if(pressok>0) //顯示"可"
    {
        if(pressok>140) painter.drawPixmap(66,72,165,165,QPixmap(":/pics/ok.png"));
        switch((pressok/11)%15) //+1分動畫
        {
            case 0: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus1_1.png"));break;
            case 14: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus1_2.png"));break;
            case 13: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus1_3.png"));break;
            case 12: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus1_4.png"));break;
            case 11: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus1_5.png"));break;
            case 10: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus1_6.png"));break;
            case 9: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus1_7.png"));break;
            case 8: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus1_8.png"));break;
            case 7: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus1_9.png"));break;
            case 6: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus1_10.png"));break;
            case 5: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus1_11.png"));break;
            case 4: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus1_12.png"));break;
            case 3: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus1_13.png"));break;
            case 2: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus1_14.png"));break;
            case 1: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus1_15.png"));break;
        }
        if(pressok==175)
        {
            combo++;
            if(combo%20==0) //每20combo+5秒
            {
                timedisplay=timedisplay+5;
                combo20=352;
                combomusic->play();
                this->ui->lcdNumber->display(timedisplay);
            }
        }
        pressok--;
    }
    if(pressyes>0) //顯示"良"
    {
        if(pressyes>150) painter.drawPixmap(66,72,165,165,QPixmap(":/pics/yes.png"));
        switch((pressyes/11)%15) //+1分動畫
        {
            case 0: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus2_1.png"));break;
            case 14: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus2_2.png"));break;
            case 13: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus2_3.png"));break;
            case 12: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus2_4.png"));break;
            case 11: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus2_5.png"));break;
            case 10: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus2_6.png"));break;
            case 9: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus2_7.png"));break;
            case 8: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus2_8.png"));break;
            case 7: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus2_9.png"));break;
            case 6: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus2_10.png"));break;
            case 5: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus2_11.png"));break;
            case 4: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus2_12.png"));break;
            case 3: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus2_13.png"));break;
            case 2: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus2_14.png"));break;
            case 1: painter.drawPixmap(110,0,70,130,QPixmap(":/pics/plus2_15.png"));break;
        }
        if(pressyes==175)
        {
            combo++;
            if(combo%20==0) //每20combo+5秒
            {
                timedisplay=timedisplay+5;
                combo20=352;
                combomusic->play();
                this->ui->lcdNumber->display(timedisplay);
            }
        }
        pressyes--;
    }
    if(combo20>0) //顯示20combo+5秒
    {
        if(combo20>176) painter.drawPixmap(20,175,180,80,QPixmap(":/pics/plus5sec.png"));
        switch((combo20/11)%16)
        {
            case 0: painter.drawPixmap(280,-10,80,130,QPixmap(":/pics/dancer_2a1.png"));break;
            case 1: painter.drawPixmap(280,-10,80,130,QPixmap(":/pics/dancer_2a2.png"));break;
            case 2: painter.drawPixmap(280,-10,80,130,QPixmap(":/pics/dancer_2a3.png"));break;
            case 3: painter.drawPixmap(280,-10,80,130,QPixmap(":/pics/dancer_2a4.png"));break;
            case 4: painter.drawPixmap(280,-10,80,130,QPixmap(":/pics/dancer_2a5.png"));break;
            case 5: painter.drawPixmap(280,-10,80,130,QPixmap(":/pics/dancer_2a6.png"));break;
            case 6: painter.drawPixmap(280,-10,80,130,QPixmap(":/pics/dancer_2a7.png"));break;
            case 7: painter.drawPixmap(280,-10,80,130,QPixmap(":/pics/dancer_2a8.png"));break;
            case 8: painter.drawPixmap(280,-10,80,130,QPixmap(":/pics/dancer_2a9.png"));break;
            case 9: painter.drawPixmap(280,-10,80,130,QPixmap(":/pics/dancer_2a10.png"));break;
            case 10: painter.drawPixmap(280,-10,80,130,QPixmap(":/pics/dancer_2a11.png"));break;
            case 11: painter.drawPixmap(280,-10,80,130,QPixmap(":/pics/dancer_2a12.png"));break;
            case 12: painter.drawPixmap(280,-10,80,130,QPixmap(":/pics/dancer_2a13.png"));break;
            case 13: painter.drawPixmap(280,-10,80,130,QPixmap(":/pics/dancer_2a14.png"));break;
            case 14: painter.drawPixmap(280,-10,80,130,QPixmap(":/pics/dancer_2a15.png"));break;
            case 15: painter.drawPixmap(280,-10,80,130,QPixmap(":/pics/dancer_2a16.png"));break;
        }
        combo20--;
    }
    if(pressballoon==31) //爆炸了
    {
        this->ui->label_6->show();
        johncenagif->start();
        johncena->play();
        if(bombdisplaytime==0) gameTimer->stop(); //爆炸第一時間，暫停計時
        bombdisplaytime++;
        update();
        if(bombdisplaytime==520) //控制爆炸畫面停留時間
        {
            johncenagif->stop();
            this->ui->label_6->hide();
            pressballoon=0;//爆炸結束，回復原本狀態
            bombdisplaytime=0;
            gameTimer->start(10);
            starti++; //氣球消失
            bgm->play();
        }
    }
    if(timecount<0) //開始前倒數3秒
    {
        if(timecount < -200)
            painter.drawPixmap(200, 0, 150, 260, QPixmap(":/pics/count3.png"));
        else if(timecount < -100)
            painter.drawPixmap(200, 0, 150, 260, QPixmap(":/pics/count2.png"));
        else
            painter.drawPixmap(200, 0, 150, 260, QPixmap(":/pics/count1.png"));
    }
    if(gamepause) //暫停
    {
        painter.drawPixmap(250, 65, 240 ,180, QPixmap(":/pics/pause.png"));
    }
}

void newwindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_A: //A消紅色鼓
        if(gamepause)
        {
            gamepause=false;
            gameTimer->start(10);
            bgm->play();
        }
        else if(!missyellowd && x[starti]<175 && style[starti]==4) //連打進入判定
        {
            score++;
            pressok=175; //顯示"可"
            pressyellowd=true;
            cdrum->play();
        }
        else if(pressballoon==31) ; //氣球已經爆炸，這時候按按鍵無效
        else if(x[starti]<175 && style[starti]==5) //氣球進入判定
        {
            bgm->pause();
            if(pressballoon%4==0) //按4下才加一分
            {
                score++;
                pressok=175; //顯示"可"
            }
            pressballoon++; //每按一下，參數紀錄+1
            cdrum->play();
        }
        else
        {
            if(x[starti]<175 && (style[starti]==1||style[starti]==3)) //紅色鼓進入判定範圍
            {
                if(style[starti]==1) //小鼓進入判定
                {
                    if(x[starti]<175 && x[starti]>140)
                    {
                        starti++; //該鼓消失
                        score++; //加一分
                        pressok=175; //顯示"可"
                    }
                    else if(x[starti]<=140 && x[starti]>120)
                    {
                        starti++; //該鼓消失
                        score=score+2; //加兩分
                        pressyes=175; //顯示"良"
                    }
                    else
                    {
                        starti++; //該鼓消失
                        score++; //加一分
                        pressok=175; //顯示"可"
                    }
                }
                else //大鼓進入判定
                {
                    if(x[starti]<175 && x[starti]>120)
                    {
                        starti++; //該鼓消失
                        score++; //加一分
                        pressok=175; //顯示"可"
                    }
                    else if(x[starti]<=120 && x[starti]>100)
                    {
                        starti++; //該鼓消失
                        score=score+2; //加兩分
                        pressyes=175; //顯示"良"
                    }
                    else
                    {
                        starti++; //該鼓消失
                        score++; //加一分
                        pressok=175; //顯示"可"
                    }
                }
            }
            else if(x[starti]<175 && (style[starti]==0||style[starti]==2)) //按A消藍色鼓(錯誤)
            {
                starti++; //該鼓消失
                presswrong=15; //顯示"不可"
            }
            else //判定範圍內無鼓
                presswrong=15; //顯示"不可"
            rdrum->play();
        }
            break;

        case Qt::Key_L: //L消藍色鼓
        if(gamepause)
        {
            gamepause=false;
            gameTimer->start(10);
            bgm->play();
        }
        else if(!missyellowd && x[starti]<175 && style[starti]==4) //連打進入判定
        {
            score++;
            pressok=175; //顯示"可"
            pressyellowd=true;
            cdrum->play();
        }
        else if(pressballoon==31) ; //氣球已經爆炸，這時候按按鍵無效
        else if(x[starti]<175 && style[starti]==5) //氣球進入判定
        {
            bgm->pause();
            if(pressballoon%4==0) //按4下才加一分
            {
                score++;
                pressok=175; //顯示"可"
            }
            pressballoon++; //每按一下，參數紀錄+1
            cdrum->play();
        }
        else
        {
            if(x[starti]<175 && (style[starti]==0||style[starti]==2)) //藍色鼓進入判定範圍
            {
                if(style[starti]==2) //小鼓進入判定
                {
                    if(x[starti]<175 && x[starti]>140)
                    {
                        starti++; //該鼓消失
                        score++; //加一分
                        pressok=175; //顯示"可"
                    }
                    else
                    {
                        starti++; //該鼓消失
                        score=score+2; //加兩分
                        pressyes=175; //顯示"良"
                    }
                }
                else //大鼓進入判定
                {
                    if(x[starti]<175 && x[starti]>120)
                    {
                        starti++; //該鼓消失
                        score++; //加一分
                        pressok=175; //顯示"可"
                    }
                    else
                    {
                        starti++; //該鼓消失
                        score=score+2; //加兩分
                        pressyes=175; //顯示"良"
                    }
                }
            }
            else if(x[starti]<135 && (style[starti]==1||style[starti]==3)) //按L消紅色鼓(錯誤)
            {
                starti++; //該鼓消失
                presswrong=15; //顯示"不可"
            }
            else //判定範圍內無鼓
                presswrong=15; //顯示"不可"
            bdrum->play();
        }
            break;

        case Qt::Key_P: //P 暫停
        if(timecount>0) //開始遊戲才能暫停
        {
            gameTimer->stop();
            gamepause=true;
            bgm->pause();
            update(); //把timer暫停了，所以要call來重新繪圖
        }

        default: break;
    }
}

void newwindow::windowUpdate()
{
    timecount++; //每次timeout加一
    this->ui->lcdNumber_2->display(score); //每次更新分數顯示
    if(x[starti]<100 && (style[starti]==1||style[starti]==2||style[starti]==5)) //沒按到小鼓or氣球
    {
        starti++; //該鼓消失
        presswrong=15; //顯示不可
    }
    else if(x[starti]<80 && (style[starti]==0||style[starti]==3)) //沒按到大鼓或連打
    {
        starti++; //該鼓消失
        presswrong=15; //顯示不可
    }
    else if(!pressyellowd && x[starti]>98 && x[starti]<100 && style[starti]==4) //沒按到連打
    {
        presswrong=170; //顯示不可
        missyellowd=true;
    }
    else if(x[starti]<-100) //連打消失
    {
        starti++;
        missyellowd=false;
        pressyellowd=false;
    }
    if(pressballoon==0) //吹氣球時後面鼓面暫停
    {
        for(int i=starti; i<stopi; i++) //已生成的鼓往左移動
        {
           x[i] = x[i] - 1;
        }
    }
    srand(time(NULL));
    if(allowdrum>0 && pressballoon==0) allowdrum--;
    else if(pressballoon==0 && timecount>0 && ((rand()*timecount-1)%29==0)) //隨機生成鼓
    {
        if(style[stopi]==0||style[stopi]==3) //下一個是大鼓
        {
            if(style[stopi+1]==1||style[stopi+1]==2) allowdrum=74;//且接著是小鼓
            else if(style[stopi+1]==4) allowdrum=110;//且接著是連打
            else if(style[stopi+1]==5) allowdrum=80;//且接著是氣球
            else allowdrum=40; //且接著是大鼓
        }
        else if(style[stopi]==4) allowdrum=300; //下一個是連打
        else if(style[stopi]==5) allowdrum=120; //下一個是氣球
        else //下一個是小鼓
        {
            if(style[stopi+1]==0||style[stopi+1]==3) allowdrum=35; //且下一個是大鼓
            else if(style[stopi+1]==4) allowdrum=60;//且接著是連打
            else if(style[stopi+1]==5) allowdrum=80;//且接著是氣球
            else allowdrum=20; //且接著小鼓
        }
        stopi++;
    }
    if(timecount>0 && timecount%100 == 0) //每一秒計時器顯示變動
    {
        this->ui->lcdNumber->display(--timedisplay);
    }
    if(timedisplay == 0) //時間到，結束
    {
        bgm->stop(); //音樂關掉
        QString printout;
        QTextStream(&printout) << "Your score : " << score <<"\n\nPlay again ??";
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Game over",printout,QMessageBox::Yes|QMessageBox::No);
        if(reply == QMessageBox::No) close();
        else  //Play again
        {
            gameTimer->stop();
            Init();
        }
    }
    update();
}

newwindow::~newwindow()
{
    delete ui;
}
