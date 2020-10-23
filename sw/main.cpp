#include "bluetooth_helper.h"
#include "ui.h"

#include <QApplication>
#include <QtCore>
#include <QtGlobal>

#include <cstdint>
#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "Hello world. " << QT_VERSION_STR << std::endl;

    QApplication app(argc, argv);

    UI ui;
    return app.exec();
}
