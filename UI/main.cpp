#include <QApplication>
#include "mediacontrols.h"
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MediaControls controls;
    controls.setWindowTitle("Media Player Controls");
    controls.resize(400, 100);
    controls.show();

    return app.exec();
}
