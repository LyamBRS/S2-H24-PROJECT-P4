/**
 * @file QAppWindow.h
 * @author LyamBRS
 * @brief
 * @version 0.1
 * @date 2024-04-09
 * @copyright Copyright (c) 2024
 */

#pragma once

 // - INCLUDES - //
#include <QtWidgets>
#include "../Application/AppHandler.h"
#include "../Application/Application.h"

// - DEFINES - //

// - GLOBALS - //

// - CLASS - //

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

class QAppWindow : public QMainWindow
{

public:
	QAppWindow();

	QMainWindow* GetWindow();

public slots:
	void Closing();

private:
    ApplicationThread* appLoopThread;
    QMenuHandler* menuHandler;
    Application* application;
};