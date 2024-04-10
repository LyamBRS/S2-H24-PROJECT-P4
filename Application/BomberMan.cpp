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
#include "Files/QMenus/Handler.h"


#include <iostream>
#include <thread>
#include <mutex>

Application* application;

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

class ApplicationThread : public QThread {
public:
    void run() override
    {
        //met ton code a excuter ici
        application->TemporaryLoop();
    }
};

int main( int argc, char ** argv )
{
	QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle("Bomberman");
    window.resize(800, 600);
    window.show();

    //QMainWindow::connect(&window, &QMainWindow::, &window, &exit);

	application = new Application(&window);
    QMenuHandler menuHandler = QMenuHandler(&window, application->GetHandler());

    ApplicationThread thread;
    thread.start();
	return app.exec();
}
