#include "mainwindow.h"
#include "ui_mainwindow.h"

#define SAVE_at_POWER_ON false
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
    //headLH(startSave);
    bodyTopLH(startSave);
    bodyMidLH(startSave);
    bodyBotLH(startSave);

    if(startSave)
    {
        led->saveLedsConfigAtPowerOn();
        qDebug() <<"Led saved at power ON";
    }
}

void MainWindow::headLH(bool startSave)
{
    int delayBetweenFlash = 5000;

    led->resetBlinkSeq(0);
    //White
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(0,0,80)), 450);
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(0,0,255)), 100);
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(0,0,0)), 700);
    led->addRgbMoveToBlinkSeq(0, 0, delayBetweenFlash-1250);

    //Green
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(120,255,80)), 450);
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(120,255,255)), 100);
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(120,255,0)), 700);
    led->addRgbMoveToBlinkSeq(0, 0, delayBetweenFlash-1250);

    //Red
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(0,255,80)), 450);
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(0,255,255)), 100);
    led->addRgbMoveToBlinkSeq(0, QColor_to_Y(QColor::fromHsv(0,255,0)), 700);
    led->addRgbMoveToBlinkSeq(0, 0, delayBetweenFlash-1250);

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
    led->resetBlinkSeq(1);
    led->addRgbMoveToBlinkSeq(1, 0x03091F, 0);
    led->addRgbMoveToBlinkSeq(1, 0x1C49FF, 5000);
    led->addRgbMoveToBlinkSeq(1, 0x16B2FF, 1000);
    led->addRgbMoveToBlinkSeq(1, 0xA89EFF, 1000);


    led->addRgbMoveToBlinkSeq(1, 0x03091F, 5000);


    led->linkLedToBlinkSeq(1, 1, 1, 0);
    led->startBlinkSeq(1);

    if(startSave)
    {
        led->linkLedToBlinkSeqAtPowerOn(1,1,1,0);
        led->set_blinkSeqStateAtPowerOn(1,1);
        led->saveBlinkSeq(1);
    }
}

void MainWindow::bodyMidLH(bool startSave)
{


    if(startSave)
    {
        led->linkLedToBlinkSeqAtPowerOn(2,1,2,0);
        led->set_blinkSeqStateAtPowerOn(2,1);
        led->saveBlinkSeq(2);
    }
}

void MainWindow::bodyBotLH(bool startSave)
{

    if(startSave)
    {
        led->linkLedToBlinkSeqAtPowerOn(3,1,3,0);
        led->set_blinkSeqStateAtPowerOn(3,1);
        led->saveBlinkSeq(3);
    }
}

MainWindow::~MainWindow()
{
    if(led != NULL)
    {
        led->set_rgbColor(0,200,0);
    }
    delete ui;
}

