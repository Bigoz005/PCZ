#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include "pillaritem.h"
#include "shootitem.h"
#include "birditem.h"
#include <QSoundEffect>
#include <QSound>

class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Scene(QObject *parent = nullptr);

    void addBird();
    void AddBullet();

    void startGame();
    void destroyBullet();

    bool getGameOn() const;
    void setGameOn(bool value);

    void incrementScore();

    void setScore(int value);

signals:

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    void showGameOverGraphics();
    void hideGameOverGraphics();
    void cleanPillars();
    void cleanBullets();
    void setUpPillarTimer();
    void freezeAllInPlace();

    QTimer * pillarTimer;
    BirdItem * bird;
    bool gameOn;

    int score;
    int bestScore;

    QSoundEffect * hitEffect;
    QSoundEffect * scoreEffect;

    QGraphicsPixmapItem * gameOverPix;
    QGraphicsTextItem * scoreTextItem;

};

#endif // SCENE_H
