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
#include "Files/Application/Application.h"


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


int main( int argc, char ** argv )
{
	//QApplication app(argc, argv);
	Application application = Application();

	application.TemporaryLoop();

	//return app.exec();
	return 0;
}
