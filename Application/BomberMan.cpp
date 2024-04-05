/**
 * @file BomberMan.cpp
 * @author LyamBRS
 * @brief
 * Is the application's basic launching program.
 * Basically like a main.cpp
 * @version 0.1
 * @date 2024-02-11
 * @copyright Copyright (c) 2024
 */

#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include <Windows.h>
#include "Files/Application/Application.h"
#include "Files/QMenus/QMainMenu.h"


#include <iostream>
#include <thread>
#include <mutex>

class SharedClass {
public:
    int sharedData;
    std::mutex mutex;

    SharedClass() : sharedData(0) {}

    void modifyData(int newValue) {
        std::lock_guard<std::mutex> lock(mutex);
        sharedData = newValue;
    }

    int readData() {
        std::lock_guard<std::mutex> lock(mutex);
        return sharedData;
    }
};

class ThreadedClass {
private:
    SharedClass sharedObject;
    std::thread myThread;

public:
    ThreadedClass() : myThread(&ThreadedClass::threadFunction, this, 42) {}

    ~ThreadedClass() {
        // Make sure to join the thread in the destructor
        if (myThread.joinable()) {
            myThread.join();
        }
    }

    void threadFunction(int newValue) {
        // Writing to the shared class
        sharedObject.modifyData(newValue);

        // Reading from the shared class
        int readValue = sharedObject.readData();
        std::cout << "Thread ID: " << std::this_thread::get_id() << ", Read Value: " << readValue << std::endl;
    }

    // Access the shared data from outside the class
    int getSharedData() {
        return sharedObject.readData();
    }
};

class RatApplicationPeriodicTimerHandler : public QObject
{
    QTimer* timer;
    Application* appRef;

private slots:
    void Loop()
    {
        //appRef->TemporaryLoop();
    }
public:
    RatApplicationPeriodicTimerHandler(Application* newAppRef) : QObject()
    {
        appRef = newAppRef;
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &RatApplicationPeriodicTimerHandler::Loop);
        timer->setInterval(1);
        timer->start();
    }
};


int main( int argc, char ** argv )
{
	QApplication app(argc, argv);
	Application application = Application();

    QMainWindow window;
    window.setWindowTitle("Bomberman");
    window.resize(800, 600);
    window.show();

    QMainMenu menu(&window);
    menu.OnEnter();

    // Set for periodic app updat

    RatApplicationPeriodicTimerHandler thisHadToBeThisComplex = RatApplicationPeriodicTimerHandler(&application);

	return app.exec();
}
