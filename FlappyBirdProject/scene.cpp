#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QSound>

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    gameOn(false), score(0), bestScore(0)
{
    //player = new QMediaPlayer();

    //hitEffect->setSource(QUrl::fromLocalFile(":/sounds/hit_sound.mp3"));
    //scoreEffect->setSource(QUrl::fromLocalFile(":/sounds/click.mp3"));

    //hitEffect->setVolume(0.5f);
    //scoreEffect->setVolume(0.5f);

    setUpPillarTimer();
}

void Scene::addBird()
{
    bird = new BirdItem(QPixmap(":/images/bird1.png"));
    addItem(bird);
}

void Scene::startGame()
{
    //Pillars
    if(!pillarTimer->isActive()){
        //Bird
        bird->startFlying();
        bird->birdWingsTimer->start(80);

        cleanPillars();
        cleanBullets();
        setScore(0);
        setGameOn(true);
        hideGameOverGraphics();
        pillarTimer->start(1000);
    }
}

void Scene::setUpPillarTimer()
{
    pillarTimer = new QTimer(this);
    connect(pillarTimer, &QTimer::timeout, [=](){

        PillarItem * pillarItem = new PillarItem();
        connect(pillarItem, &PillarItem::collideFail,[=](){
           pillarTimer->stop();
           freezeAllInPlace();
           setGameOn(false);
           showGameOverGraphics();
        });

        connect(pillarItem, &PillarItem::collideShoot, [=](){
            delete(pillarItem->collidingBullet);
            pillarItem->collidingBullet = nullptr;
        });

        addItem(pillarItem);
    });
}


void Scene::AddBullet()
{
    if(pillarTimer->isActive()){
        ShootItem * bulletItem = new ShootItem(bird);
        bulletItem->setZValue(2);
        addItem(bulletItem);
    }
}

void Scene::freezeAllInPlace()
{
    //Freeze bird
    bird->freezeInPlace();

    //Freeze pillars
    QList<QGraphicsItem*> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems){
        PillarItem * pillar = dynamic_cast<PillarItem *>(item);
        if(pillar){
           pillar->freezeInPlace();
        }
    }

    //Freeze bullets
    QList<QGraphicsItem*> bulletItems = items();
    foreach(QGraphicsItem *item, bulletItems){
        ShootItem * bullet = dynamic_cast<ShootItem *>(item);
        if(bullet){
           bullet->freezeInPlace();
        }
    }
    //hitEffect->play();
}

void Scene::setScore(int value)
{
    score = value;
}

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool value)
{
    gameOn = value;
}

void Scene::incrementScore()
{
    score++;

    //scoreEffect->play();

    if(score > bestScore){
        bestScore = score;
    }

    qDebug() << "Score: " << score;
    qDebug() << "Best score: " << bestScore;
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){
        if(gameOn){
            AddBullet();
            qDebug() << "SHOOT";
        }
    }

    if(event->key() == Qt::Key_S){
        if(gameOn){
            bird->shootUp();
            qDebug() << "JUMP";
        }
    }

    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        if(gameOn){
            bird->shootUp();
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void Scene::showGameOverGraphics()
{
    gameOverPix = new QGraphicsPixmapItem(QPixmap(":/images/Game_over.png"));
    gameOverPix->setZValue(100);
    addItem(gameOverPix);
    gameOverPix->setPos(QPointF(0,0) - QPointF(gameOverPix->boundingRect().width()/2,
                                               gameOverPix->boundingRect().height()/2));

    scoreTextItem = new QGraphicsTextItem();

    QString string = "Score: " + QString::number(score)
            + " Best Score: " + QString::number(bestScore);

    QFont mFont("Times New Roman", 25, QFont::Bold);

    scoreTextItem->setHtml(string);
    scoreTextItem->setFont(mFont);
    scoreTextItem->setDefaultTextColor(Qt::red);
    scoreTextItem->setZValue(100);
    addItem(scoreTextItem);

    scoreTextItem->setPos(QPointF(0,0) - QPointF(scoreTextItem->boundingRect().width()/2,
                                               gameOverPix->boundingRect().height()));
}

void Scene::hideGameOverGraphics()
{
    if(gameOverPix != nullptr){
        removeItem(gameOverPix);
        delete gameOverPix;
        gameOverPix = nullptr;
    }

    if(scoreTextItem != nullptr){
        removeItem(scoreTextItem);
        delete scoreTextItem;
        scoreTextItem = nullptr;
    }
}

void Scene::cleanPillars()
{
    QList<QGraphicsItem*> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems){
        PillarItem * pillar = dynamic_cast<PillarItem *>(item);
        if(pillar){
           //removeItem(pillar);
           delete pillar;
        }
    }
}

void Scene::cleanBullets()
{
    QList<QGraphicsItem*> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems){
        ShootItem * bullet = dynamic_cast<ShootItem *>(item);
        if(bullet){
           //removeItem(bullet);
           delete bullet;
        }
    }
}
