#ifndef SNAKE_HPP
#define SNAKE_HPP
//#include <QGraphicsItem>
//#include <QPainter>
//#include <QMainWindow>
//#include <QGraphicsScene>
//#include <QtWidgets>
//#include <QGraphicsItem>
//#include <QVector>
//#include <QPair>
#include <QGraphicsItemGroup>
#include <QList>

//#include "algorithms.hpp"
#include "tile.hpp"

enum eDirection {Up, Down, Left, Right};//if (Up || Left) in ++; else in --;

class Snake
{
/*********Методы*********/
//Служебные
public:
    Snake() = delete;
    Snake(QList<Tile*>, int, int, eDirection, QRectF);
    Snake(Snake&);
    Snake(Snake&&);
    ~Snake();
    QGraphicsItemGroup* GetItems();
    void SetItems();
    void ClearItems();
//Игровая логика
public:
	void ChangeDirection(eDirection);
    eDirection GetDirection();
    bool IsSnake(QPointF) const;
    void Move();
    void ReverseMove();
    void SetReverse();
    void ClearReverse();
    bool IsReverse();
    QRectF GetHeadRect() const;
    QRectF GetTailRect() const;
/************************/
/**********Поля**********/
//Служебные
private:
    QGraphicsItemGroup* BodyItems;
//Игровая логика
private:
    const QList<Tile*> Body;
    const int StepX;
    const int StepY;
    eDirection Direction;
    QRectF BorderRect;
    bool Reverse;
/************************/
};


#endif // SNAKE_HPP
