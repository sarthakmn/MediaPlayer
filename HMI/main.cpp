#include <QApplication>
#include <iostream>

#include "include/mediacontrols.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MediaControls controls;
    controls.setWindowTitle("Media Player Controls");
    controls.resize(400, 100);
    controls.show();

    return app.exec();
}
