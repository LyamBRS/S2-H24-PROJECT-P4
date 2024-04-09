/**
 * @file QAppWindow.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-04-05
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "QAppWindow.h"

// - CLASS - //
QAppWindow::QAppWindow()
{
    setWindowTitle("Bomberman");
    resize(800, 600);

    application = new Application(this);
    menuHandler = new QMenuHandler(this, application->GetHandler());

    appLoopThread = new ApplicationThread(application);
    appLoopThread->start();
    connect(this, &QMainWindow::close, this, &QAppWindow::Closing);
}

void QAppWindow::Closing()
{
    appLoopThread->terminate();
}