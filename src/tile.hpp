#ifndef TILE_HPP
#define TILE_HPP

//#include <QMainWindow>
//#include <QGraphicsScene>
//#include <QtWidgets>
//#include <QVector>
//#include <QGraphicsItemGroup>
//#include <QGraphicsItem>
//#include <QPair>

#include <QPainter>
#include <QGraphicsItem>
#include <QList>
#include <QTimer>

class Tile : public QGraphicsItem
{
/*********Методы*********/
//Конструкторы
public:
    Tile() = delete;
    Tile(QRectF);
    Tile(const Tile& val);
    Tile(Tile&& val);
//Деструктор
public:
    ~Tile();
//Операторы
public:
    Tile& operator= (const Tile&);
    Tile& operator= (Tile&&);
//Qt графика
public:
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
//Сеттеры
public:
    void SetRect(QRectF);
    void SetAngle(float);
    void Mirror();
    void AddSprite(QPixmap);
    void SetCollision(bool);
//Геттеры
public:
    bool IsSolid() const;
    bool IsTile(QPointF) const;
//Вспомогательные
public:
    void ClearSprites();
    void StartAnim(int);
    void StopAnim();
public slots:
	void AnimationStep();
/************************/
/**********Поля**********/
private:
    QRectF TileRect;
    float SpriteAngle;
    bool Mirroring;
    QList<QPixmap*> Sprites;
    QList<QPixmap*>::Iterator CurrentSprite;
    bool Collision;
    QTimer* Timer;
    QMetaObject::Connection AnimationWire;
/************************/
};

#endif // TILE_HPP
