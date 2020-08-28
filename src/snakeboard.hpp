#ifndef SNAKEBOARD_HPP
#define SNAKEBOARD_HPP

//#include <QGraphicsItem>
//#include <QPainter>
//#include <QMainWindow>
//#include <QGraphicsScene>
//#include <QtWidgets>
//#include <QGraphicsItem>
//#include <QVector>
//#include <QTimer>
//#include <QPair>
//#include <QHash>
//#include <QDebug>

#include <QGraphicsItemGroup>
#include <QList>
#include <QMap>
#include <QTime>

#include "snake.hpp"
//#include "algorithms.hpp"

typedef uint snakeID;

class SnakeBoard : public QGraphicsItem
{
/*********Методы*********/
//Служебные
public:
    SnakeBoard() = delete;
/*****Конструктор*****/
    SnakeBoard(QRectF, QRectF, QList<QList<Tile>>, int, int);
/*****Деструктор*****/
    ~SnakeBoard();
/*****Рамка графического айтема*****/
    QRectF boundingRect() const;
/*****Клетки игрового поля как графический айтем*****/
/*****Змеи на игровом поле как графический айтем*****/
    QGraphicsItemGroup* GetItems();

    void SetItems();

    void ClearItems();
/*****Отрисовка поля как графического айтема = задний фон*****/
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
//Игровая логика
public:
/*****Добавить змею на поле*****/
    snakeID AddSnake();
/*****Убрать змею с поля*****/
    void RemoveSnake(snakeID);
/*****Шаг анимации перемещения вперед*****/
    bool GoAhead(snakeID);
/*****Шаг анимации перемещения назад*****/
    bool GoBack(snakeID);
/*****Проверка здоровья змеи*****/
    bool IsDead();
/*****Сброс здоровья змеи*****/
    void ClearDead();
/*****Смена направления движения змеи*****/
    void ChangeDirection(snakeID, eDirection);
private:
/*****Может ли змея переместиться вперед*****/
    bool CanMove(snakeID);
/*****Может ли змея переместиться назад*****/
    bool CanReverseMove(snakeID);
/*****Генератор игрового поля*****/
    friend QList<QList<Tile>> FieldGenerator(QRectF, int, int);
/*****Генератор змеи*****/
    QList<Tile*> SnakeGenerator();
/************************/
/**********Поля**********/
//Служебные
private:
/*****Рамка игрового поля*****/
    QRectF BoardRect;
/*****Задний план игрового поля*****/
    QPixmap Background;
/*****Графические айтемы клеток на игровом поле*****/
/*****Графические айтемы змей на игровом поле*****/
    QGraphicsItemGroup* GraphicsItems;
/*****Ширина тайлов*****/
    int TileWidth;
/*****Высота тайлов*****/
    int TileHeight;
//Игровая логика
private:
/*****Игровые клетки*****/
    QList<QList<Tile>> Cells;
/*****Количество столбцов игровых клеток*****/
    int ColumnsCount;
/*****Количество строк игровых клеток*****/
    int RowsCount;
/*****Пул змей на поле с индивидуальным айди*****/
    QMap<snakeID, Snake*> Snakes;
/*****Флаг смерти после последнего перемещения****/
    bool DeadFlag;
    QRectF CellsRect;
/************************/
};
QList<QList<Tile>> FieldGenerator(QRectF, int, int);
QList<QList<Tile>> EmptyGenerator(QRectF , int, int);
#endif // SNAKEBOARD_HPP
