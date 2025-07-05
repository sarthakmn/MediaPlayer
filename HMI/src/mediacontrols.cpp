#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <unistd.h>
#include <devghev.hpp>

#include "include/mediacontrols.h"

MediaControls::MediaControls(QWidget *parent)
    : QWidget(parent)
{
    playButton = new QPushButton("▶ Play");
    pauseButton = new QPushButton("⏸ Pause");
    nextButton = new QPushButton("⏭ Next");
    prevButton = new QPushButton("⏮ Previous");
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(prevButton);
    layout->addWidget(playButton);
    layout->addWidget(pauseButton);
    layout->addWidget(nextButton);
    setLayout(layout);
    connect(playButton, &QPushButton::clicked, this, &MediaControls::play);
    connect(pauseButton, &QPushButton::clicked, this, &MediaControls::pause);
    connect(nextButton, &QPushButton::clicked, this, &MediaControls::next);
    connect(prevButton, &QPushButton::clicked, this, &MediaControls::previous);

    // Initialize devghev for "cmd" topic
    devghev::init("cmd");
}

void MediaControls::sendCommand(const QString& cmd, const QString& value)
{
    devghev::Message msg;
    msg.id = 1;
    msg.type = devghev::MessageType::CUSTOM;
    msg.timestamp = 0;
    msg.sender_pid = getpid();

    std::string payload = "cmd=" + cmd.toStdString();
    if (!value.isEmpty())
        payload += ";value=" + value.toStdString();

    msg.payload_size = payload.size();
    strncpy(msg.payload, payload.c_str(), devghev::MAX_PAYLOAD);

    devghev::send("cmd", msg);
}

void MediaControls::play() {
    qDebug() << "🎵 Play clicked";
    sendCommand("play");
}
void MediaControls::pause() {
    qDebug() << "⏸ Pause clicked";
    sendCommand("pause");
}
void MediaControls::next() {
    qDebug() << "⏭ Next clicked";
    sendCommand("next");
}
void MediaControls::previous() {
    qDebug() << "⏮ Previous clicked";
    sendCommand("prev");
}
// Add similar slots for volume up/down if needed
// ...existing code...