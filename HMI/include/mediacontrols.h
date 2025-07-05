#pragma once

#include <QWidget>
#include <QPushButton>

class MediaControls : public QWidget {
    Q_OBJECT

public:
    MediaControls(QWidget *parent = nullptr);

private slots:
    void play();
    void pause();
    void next();
    void previous();

private:
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *nextButton;
    QPushButton *prevButton;

    void sendCommand(const QString& cmd, const QString& value = "");
};
