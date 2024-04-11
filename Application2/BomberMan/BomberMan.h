#pragma once

#include <QtWidgets/QMainWindow>
#include <QThread>
#include "ui_BomberMan.h"
#include "Files/Application/AppHandler.h"
#include "Files/Application/Application.h"

class ApplicationThread : public QThread {
public:
    Application* appRef;
    ApplicationThread(Application* realAppRef)
    {
        appRef = realAppRef;
    }

    ApplicationThread() {}

    void run() override
    {
        appRef->TemporaryLoop();
    }
};

class BomberMan : public QMainWindow
{
    Q_OBJECT

public:
    BomberMan(QWidget *parent = nullptr);
    ~BomberMan();

public slots:
    void Closing();

private:
    Ui::BomberManClass ui;
    ApplicationThread* appLoopThread;
    QMenuHandler* menuHandler;
    Application* application;
};
