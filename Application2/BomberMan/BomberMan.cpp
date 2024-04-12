#include "BomberMan.h"

BomberMan::BomberMan(QWidget *parent)
    : QMainWindow(parent)
{

    // Load the image
    QPixmap backgroundImage(QString::fromStdString(GetSvg("Background")));

    setWindowTitle("Bomberman");
    resize(800, 600);

    application = new Application(this);
    menuHandler = new QMenuHandler(this, application->GetHandler());

    appLoopThread = new ApplicationThread(application);
    appLoopThread->start();
    connect(this, &QMainWindow::close, this, &BomberMan::Closing);
}

void BomberMan::Closing()
{
    appLoopThread->terminate();
}

BomberMan::~BomberMan()
{}
