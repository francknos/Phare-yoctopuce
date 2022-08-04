#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Yocotpuce/yocto_api.h>
#include <Yocotpuce/yocto_colorledcluster.h>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

inline int QColor_to_Y(QColor c)
{
    return c.name().remove("#").toInt(0,16);
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void CreateLedRoutineLightHouse(bool startSave=false);
    void headLH(bool startSave=false);
    void bodyTopLH(bool startSave=false);
    void bodyMidLH(bool startSave=false);
    void bodyBotLH(bool startSave=false);

    void teteMort(void);
    QColor same(int c=0);

private:
    Ui::MainWindow *ui;
    YColorLedCluster *led;
};
#endif // MAINWINDOW_H
