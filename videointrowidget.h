#ifndef VIDEOINTROWIDGET_H
#define VIDEOINTROWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>

class VideoIntroWidget : public QWidget {
    Q_OBJECT
public:
    explicit VideoIntroWidget(QWidget *parent = nullptr);

private slots:
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;
    QAudioOutput *audioOutput;
};

#endif // VIDEOINTROWIDGET_H
