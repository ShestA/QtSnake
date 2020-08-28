#ifndef SNAKEWINDOW_HPP
#define SNAKEWINDOW_HPP

#include <QGraphicsItem>
#include <QPainter>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QtWidgets>
#include <QGraphicsItem>
#include <QVector>
#include <QGraphicsItemGroup>
#include <QList>
#include <QPair>

#include "snakeboard.hpp"
#include "../ui_snakewindow.h"
#include "sqlwrap.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class SnakeWindow; }
QT_END_NAMESPACE

class SnakeWindow : public QMainWindow
{Q_OBJECT
/*********Методы*********/
//Служебные
public:
/*****Конструктор*****/
    SnakeWindow(QWidget *parent = nullptr);
/*****Деструктор****/
    ~SnakeWindow();
public slots:
/*****Обработчик кадра****/
    void updater();
//Игровая логика
private:
/*****Запуск игровой сессии****/
    void Startuem();
/*****Перезапуск змеек на карте****/
    void RestartSnakes();
/*****Перезапуск игры****/
    void Restart();
public slots:
/*****Обработчик анимации****/
    void snakeUpdater();
/*****Случайный выбор направления змей****/
    void randomAI();
/*****Нажали на кнопку Gen****/
    void pressGeneratorButton();
/*****Отпустили кнопку Gen****/
    void releaseGeneratorButton();
/*****Нажали на кнопку Save****/
    void pressSaveButton();
/*****Отпустили кнопку Save****/
    void releaseSaveButton();
/*****Нажали на кнопку Space****/
    void pressSpaceButton();
/*****Отпустили кнопку Space****/
    void releaseSpaceButton();
/************************/
/**********Поля**********/
//Служебные
private:
/*****Графический интерфейс окна****/
    Ui::SnakeWindow *ui;
/*****Игровая сцена****/
    QGraphicsScene *scene;
/*****Таймер кадра****/
    QTimer *FPS;
/*****Доступ к базе данных****/
    SQLwrap* sql;
//Игровая логика
private:
/*****Игровое поле****/
    SnakeBoard *gameBoard;
/*****Идентификатор первой змеи****/
    snakeID SnakeOneID;
/*****Идентификатор второй змеи****/
    snakeID SnakeTwoID;
/*****Направление движения первой змеи****/
    eDirection SnakeOneDirection;
/*****Направление движения второй змеи****/
    eDirection SnakeTwoDirection;
/*****Счетчик обратного хода первой змеи****/
    int ReverseCounterSnakeOne;
/*****Счетчик обратного хода второй змеи****/
    int ReverseCounterSnakeTwo;
/*****Таймер игровых событий****/
    QTimer *Logic;
/*****Таймер смены *направления движения***/
    QTimer *AI;
/************************/
};
#endif // SNAKEWINDOW_HPP
