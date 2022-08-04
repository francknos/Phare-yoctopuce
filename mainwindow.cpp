#include "mainwindow.h"
#include "ui_mainwindow.h"

#define SAVE_at_POWER_ON true
#define RESET_SATART_SEQUENCE false

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    led = NULL;
    string errmsg;
    if(YAPI::RegisterHub("usb", errmsg) == YAPI::SUCCESS)
        qDebug() << "YAPI Open";

    led = yFirstColorLedCluster();

    if(led != NULL)
    {
        qDebug() << "Led found";
        led->set_rgbColor(0,200, 0x000000);
        CreateLedRoutineLightHouse(SAVE_at_POWER_ON);
    }

    if(RESET_SATART_SEQUENCE)
    {
        led->resetBlinkSeq(0);
        led->resetBlinkSeq(1);
        led->resetBlinkSeq(2);
        led->resetBlinkSeq(3);
        led->saveBlinkSeq(0);
        led->saveBlinkSeq(1);
        led->saveBlinkSeq(2);
        led->saveBlinkSeq(3);
        led->saveLedsConfigAtPowerOn();
    }
}

void MainWindow::CreateLedRoutineLightHouse(bool startSave)
{
    headLH(startSave);
    bodyTopLH(startSave);
    bodyMidLH(startSave);
    bodyBotLH(startSave);

    if(startSave)
    {
        led->saveLedsConfigAtPowerOn();
        led->module()->setLuminosity(0);
        led->module()->saveToFlash();
        qDebug() <<"Led saved at power ON";
    }
}

void MainWindow::headLH(bool startSave)
{
    static int delayBetweenFlash = 7000;

    led->resetBlinkSeq(0);
    //White
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(0,0,80)), 500);
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(0,0,255)), 100);
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(0,0,0)), 600);
    led->addRgbMoveToBlinkSeq(0, 0, delayBetweenFlash-1200);

    //Green
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(120,255,80)), 500);
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(120,255,255)), 100);
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(120,255,0)), 600);
    led->addRgbMoveToBlinkSeq(0, 0, delayBetweenFlash-1200);

    //Red
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(0,255,80)), 500);
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(0,255,255)), 100);
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(0,255,0)), 600);
    led->addRgbMoveToBlinkSeq(0, 0, delayBetweenFlash-1200);

    //White
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(0,0,80)), 500);
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(0,0,255)), 100);
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(0,0,0)), 600);
    led->addRgbMoveToBlinkSeq(0, 0, delayBetweenFlash-1200);

    led->linkLedToBlinkSeq(0, 1, 0, 0);
    led->startBlinkSeq(0);

    if(startSave)
    {
        led->linkLedToBlinkSeqAtPowerOn(0,1,0,0);
        led->set_blinkSeqStateAtPowerOn(0,1);
        led->saveBlinkSeq(0);
    }
}

void MainWindow::bodyTopLH(bool startSave)
{
    int idSec = 2;
    led->resetBlinkSeq(idSec);

    led->addRgbMoveToBlinkSeq(idSec, 0x00071F, 0);
    led->addRgbMoveToBlinkSeq(idSec, 0x0033FF, 5000);
    led->addRgbMoveToBlinkSeq(idSec, 0x16B2FF, 1000);
    led->addRgbMoveToBlinkSeq(idSec, 0xD100D6, 1000);
    led->addRgbMoveToBlinkSeq(idSec, 0x00061F, 5000);
    led->addRgbMoveToBlinkSeq(idSec, 0x0D00DB, 3000);
    led->addRgbMoveToBlinkSeq(idSec, 0xDB00D8, 6000);

    led->addRgbMoveToBlinkSeq(idSec, 0xFFFFFF, 500);
    led->addRgbMoveToBlinkSeq(idSec, 0xFFFFFF, 100);
    led->addRgbMoveToBlinkSeq(idSec, 0x00AAFF, 400);
    led->addRgbMoveToBlinkSeq(idSec, 0x03091F, 4000); //20000-15600 - 400

    led->linkLedToBlinkSeq(idSec, 1, idSec, 0);
    led->startBlinkSeq(idSec);

    if(startSave)
    {
        led->linkLedToBlinkSeqAtPowerOn(idSec,1,idSec,0);
        led->set_blinkSeqStateAtPowerOn(idSec,1);
        led->saveBlinkSeq(idSec);
    }
}

void MainWindow::bodyMidLH(bool startSave)
{
    int idSec = 1;
    led->resetBlinkSeq(idSec);

    led->addRgbMoveToBlinkSeq(idSec, 0x00071F, 0);
    led->addRgbMoveToBlinkSeq(idSec, 0x0033FF, 5000);
    led->addRgbMoveToBlinkSeq(idSec, 0x0009FF, 1000);
    led->addRgbMoveToBlinkSeq(idSec, 0x00AAFF, 1000);
    led->addRgbMoveToBlinkSeq(idSec, 0x0C007D, 1000);
    led->addRgbMoveToBlinkSeq(idSec, 0x00071F, 5000);
    led->addRgbMoveToBlinkSeq(idSec, 0x004B69, 6000);
    led->addRgbMoveToBlinkSeq(idSec, 0x000C36, 1750);

    led->addRgbMoveToBlinkSeq(idSec, 0xFFFFFF, 500);
    led->addRgbMoveToBlinkSeq(idSec, 0xFFFFFF, 200);
    led->addRgbMoveToBlinkSeq(idSec, 0x007FBF, 1250);

    led->addRgbMoveToBlinkSeq(idSec, 0xD100D6, 3300);

    led->linkLedToBlinkSeq(idSec, 1, idSec, 0);
    led->startBlinkSeq(idSec);

    if(startSave)
    {
        led->linkLedToBlinkSeqAtPowerOn(idSec,1,idSec,0);
        led->set_blinkSeqStateAtPowerOn(idSec,1);
        led->saveBlinkSeq(idSec);
    }
}

void MainWindow::bodyBotLH(bool startSave)
{
    int idSec = 3;
    led->resetBlinkSeq(idSec);

    led->addRgbMoveToBlinkSeq(idSec, 0x03091F, 0);
    led->addRgbMoveToBlinkSeq(idSec, 0x1C49FF, 5000);
    led->addRgbMoveToBlinkSeq(idSec, 0x16B2FF, 1000);
    led->addRgbMoveToBlinkSeq(idSec, 0xA89EFF, 1000);
    led->addRgbMoveToBlinkSeq(idSec, 0xD100D6, 5000);
    led->addRgbMoveToBlinkSeq(idSec, 0x00071F, 2000);
    led->addRgbMoveToBlinkSeq(idSec, 0x0D001F, 6000);

    led->addRgbMoveToBlinkSeq(idSec, 0xFFFFFF, 500);
    led->addRgbMoveToBlinkSeq(idSec, 0xFFFFFF, 300);
    led->addRgbMoveToBlinkSeq(idSec, 0x00AAFF, 2000);
    led->addRgbMoveToBlinkSeq(idSec, 0x03091F, 3200);


    led->linkLedToBlinkSeq(idSec, 1, idSec, 0);
    led->startBlinkSeq(idSec);

    if(startSave)
    {
        led->linkLedToBlinkSeqAtPowerOn(idSec,1,idSec,0);
        led->set_blinkSeqStateAtPowerOn(idSec,1);
        led->saveBlinkSeq(idSec);
    }
}

void MainWindow::teteMort()
{
    led->resetBlinkSeq(0);
    led->resetBlinkSeq(1);
    led->resetBlinkSeq(2);

    //Fond blanc aspect bougie
    led->addRgbMoveToBlinkSeq(0,QColor_to_Y(same()),100);
    led->addRgbMoveToBlinkSeq(0,QColor_to_Y(same(45)),400);
    led->addRgbMoveToBlinkSeq(0,QColor_to_Y(same()),600);
    led->addRgbMoveToBlinkSeq(0,QColor_to_Y(same(35)),200);
    led->addRgbMoveToBlinkSeq(0,QColor_to_Y(same(-45)),1200);
    led->addRgbMoveToBlinkSeq(0,QColor_to_Y(same(-35)),3000);
    led->addRgbMoveToBlinkSeq(0,QColor_to_Y(same(+35)),400);
    led->addRgbMoveToBlinkSeq(0,QColor_to_Y(same()),400);
    led->addRgbMoveToBlinkSeq(0,QColor_to_Y(same(40)),200);
    led->addRgbMoveToBlinkSeq(0,QColor_to_Y(same(-25)),400);



    /* OEIL GAUCHE */
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(Qt::black)),0);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(Qt::black)),2000);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(Qt::black)),10000);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(255,0,0)),100);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(140,0,0)),200);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(255,0,0)),100);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(Qt::black)),500);


    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(Qt::black)),2000);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(Qt::black)),10000);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(255,0,0)),100);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(144,0,0)),200);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(255,0,0)),100);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(Qt::black)),500);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(Qt::black)),500);

    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(Qt::black)), 5000);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(Qt::black)), 5000);


    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(Qt::red)), 200);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(QColor(100,0,0))), 1000);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(Qt::red)), 300);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(QColor(100,0,0))), 1000);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(QColor(20,0,0))),250);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(Qt::red)),50);
    led->addRgbMoveToBlinkSeq(1,QColor_to_Y(QColor(Qt::black)),250);




    /*Oeil droit */
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(Qt::black)),0);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(Qt::black)),2000);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(Qt::black)),10000);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(255,0,0)),100);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(140,0,0)),200);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(255,0,0)),100);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(Qt::black)),500);


    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(Qt::black)),2000);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(Qt::black)),10000);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(Qt::black)),200);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(255,0,0)),100);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(144,0,0)),200);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(255,0,0)),100);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(Qt::black)),500);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(Qt::black)),300);


    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(Qt::black)),1000);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(Qt::red)),2000);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(Qt::black)),2000);

    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(Qt::black)), 5000);


    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(Qt::black)),100);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(Qt::red)), 200);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(QColor(100,0,0))), 1000);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(Qt::black)),600);
    led->addRgbMoveToBlinkSeq(2,QColor_to_Y(QColor(Qt::black)),1150);

    led->linkLedToBlinkSeq(0,1,0,0);
    led->startBlinkSeq(0);
    led->linkLedToBlinkSeq(1,1,1,0);
    led->startBlinkSeq(1);
    led->linkLedToBlinkSeq(2,1,2,0);
    led->startBlinkSeq(2);


    /* SAUVEGARDE POUR LE AUTO START*/
    bool SAVE = 0;

    if(SAVE)
    {
        qDebug() << "Save at Start TETE MORT";
        led->set_blinkSeqStateAtPowerOn(0,1);
        led->saveBlinkSeq(0);
        led->linkLedToBlinkSeqAtPowerOn(0,1,0,0);

        led->set_blinkSeqStateAtPowerOn(1,1);
        led->saveBlinkSeq(1);
        led->linkLedToBlinkSeqAtPowerOn(1,1,1,0);

        led->set_blinkSeqStateAtPowerOn(2,1);
        led->saveBlinkSeq(2);
        led->linkLedToBlinkSeqAtPowerOn(2,1,2,0);

        led->saveLedsConfigAtPowerOn();
    }
}

QColor MainWindow::same(int c)
{
    int baseR = 108;
    int baseV = 109;
    int baseB = 41;

    baseB = baseR = baseV = 210;

    return QColor(baseR+c,baseV+c,baseB+c);
}

MainWindow::~MainWindow()
{
    if(led != NULL)
    {
        led->set_rgbColor(0,200,0);
    }
    delete ui;
}

