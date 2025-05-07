#include "videointrowidget.h"
#include "./userheaders/mainwindow.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QAudioOutput>
#include <QVersionNumber>
#include <QMessageBox>
#include <QAudioDevice>

VideoIntroWidget::VideoIntroWidget(QWidget *parent) : QWidget(parent) {
    // Initialize media player and video widget
    mediaPlayer = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    audioOutput = nullptr; // Initialize to nullptr

    // Check Qt version for audio output setup
    QVersionNumber qtVersion = QVersionNumber::fromString(QT_VERSION_STR);
    qDebug() << "Qt version:" << qtVersion.toString();

    if (qtVersion.majorVersion() >= 6) {
        // Qt 6: Explicitly set up QAudioOutput
        audioOutput = new QAudioOutput(this);
        if (audioOutput) {
            qDebug() << "Audio output device:" << audioOutput->device().description();
            mediaPlayer->setAudioOutput(audioOutput);
            audioOutput->setVolume(1.0); // Full volume, adjust as needed
        } else {
            qDebug() << "Failed to create QAudioOutput";
        }
    } else {
        // Qt 5: Audio output is implicit
        qDebug() << "Using Qt 5, no explicit QAudioOutput needed";
    }

    // Set up layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(videoWidget);
    setLayout(layout);

    // Assign video output to the video widget
    mediaPlayer->setVideoOutput(videoWidget);

    // Load video file

    mediaPlayer->setSource(QUrl("qrc:/video/opening.mp4"));

    // Connect media status signal to handle video completion
    connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &VideoIntroWidget::onMediaStatusChanged);

    // Connect error signal for debugging and fallback
    connect(mediaPlayer, &QMediaPlayer::errorOccurred, this, [this](QMediaPlayer::Error error, const QString &errorString) {
        qDebug() << "MediaPlayer error:" << error << errorString;
        QMessageBox::warning(this, "Video Error", "Failed to play intro video: " + errorString);
        close();
        MainWindow *mainWindow = new MainWindow();
        mainWindow->showMaximized();
    });

    // Play the video (includes audio if present)
    qDebug() << "Starting video playback";
    mediaPlayer->play();

    // Optional: Set window properties
    setWindowTitle("Intro Video");
    showMaximized();
}

void VideoIntroWidget::onMediaStatusChanged(QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::EndOfMedia) {
        qDebug() << "Video playback finished, showing MainWindow maximized";
        // Video finished, close this widget
        close();

        // Show the MainWindow maximized
        MainWindow *mainWindow = new MainWindow();
        mainWindow->showMaximized();
    }
}

