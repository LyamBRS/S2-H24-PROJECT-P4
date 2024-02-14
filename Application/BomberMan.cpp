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

int main( int argc, char ** argv )
{
	QApplication app(argc, argv);
	return app.exec();
}
