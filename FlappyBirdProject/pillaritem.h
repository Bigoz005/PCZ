#ifndef PILLARITEM_H
#define PILLARITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <ShootItem.h>

class PillarItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit PillarItem();
    ~PillarItem();

    qreal x() const;
    int yPos;
    ShootItem * collidingBullet;
    QGraphicsPixmapItem * wood;

    void freezeInPlace();

signals:
    void collideFail();
    void collideShoot();

public slots:

    void setX(qreal x);

private:

    bool collidesWithBird();
    bool collidesWithShoot();
    QGraphicsPixmapItem * topPillar;
    QGraphicsPixmapItem * bottomPillar;

    QPropertyAnimation * xAnimation;

    qreal m_x;
    bool pastBird;
};

#endif // PILLARITEM_H
