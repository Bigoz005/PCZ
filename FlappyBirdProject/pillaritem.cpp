#include "pillaritem.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include "scene.h"
#include "birditem.h"
#include "shootitem.h"
#include <QDebug>


PillarItem::PillarItem():
    topPillar(new QGraphicsPixmapItem(QPixmap(":/images/pipe1.png"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/images/pipe1.png"))),
    wood(new QGraphicsPixmapItem(QPixmap(":/images/wood.png"))),
    pastBird(false)
{
    topPillar->setPos(QPointF(0,0) - QPointF(topPillar->boundingRect().width()/2,
                      topPillar->boundingRect().height() + 60));

    bottomPillar->setPos(QPointF(0,0) + QPointF(-bottomPillar->boundingRect().width()/2,
                      60));

    wood->setPos(QPointF(0,0) - QPointF(topPillar->boundingRect().width()/2 - 10, bottomPillar->boundingRect().height()-topPillar->boundingRect().height()+30));

    addToGroup(topPillar);
    addToGroup(bottomPillar);
    addToGroup(wood);

    yPos = QRandomGenerator::global()->bounded(150);
    int xRandomizer = QRandomGenerator::global()->bounded(200);

    setPos(QPoint(0,0) + QPoint(260 + xRandomizer, yPos));

    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(260 + xRandomizer);
    xAnimation->setEndValue(-300);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(2000);

    connect(xAnimation, &QPropertyAnimation::finished, [=](){
        qDebug()<<"Animation ended";
        scene()->removeItem(this);
        delete this;
    });

    xAnimation->start();
}

PillarItem::~PillarItem()
{
    qDebug()<<"Deleted Pillar";
    delete topPillar;
    delete bottomPillar;
    if (wood != nullptr){
        delete wood;
    }
}

qreal PillarItem::x() const
{
    return m_x;
}

void PillarItem::freezeInPlace()
{
    xAnimation->stop();
}

void PillarItem::setX(qreal x)
{
    m_x = x;

    if(x < 0 && !pastBird){
        pastBird = true;
        QGraphicsScene * mScene = scene();
        Scene * myScene = dynamic_cast<Scene *>(mScene);
        if(myScene){
            //QSound::play("sounds/click.mp3");
            //player2->play();

            myScene->incrementScore();
        }
    }


    if(collidesWithBird()){
        emit collideFail();
    }

    if(collidesWithShoot()){
        delete wood;
        wood = nullptr;
        emit collideShoot();
    }

    setPos(QPoint(0,0)+ QPoint(x, yPos));
}

bool PillarItem::collidesWithBird()
{
    QList<QGraphicsItem*> collidingItems = topPillar->collidingItems();
    collidingItems.append(bottomPillar->collidingItems());
    if(wood != nullptr){
        collidingItems.append(wood->collidingItems());
    }

    foreach(QGraphicsItem * item, collidingItems){
        BirdItem * birdItem = dynamic_cast<BirdItem*>(item);
        if(birdItem){
            return true;
        }
    }
    return false;
}

bool PillarItem::collidesWithShoot()
{
    if(wood != nullptr){
        QList<QGraphicsItem*> collidingItems = wood->collidingItems();

    foreach(QGraphicsItem * item, collidingItems){
        ShootItem * shootItem = dynamic_cast<ShootItem*>(item);
        if(shootItem){
            collidingBullet = shootItem;
            return true;
        }
    }
    return false;
    }
}

