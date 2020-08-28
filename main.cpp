#include "src/tile.hpp"
//#include "src/algorithms.hpp"
#include "src/snake.hpp"
#include "src/snakeboard.hpp"
#include "src/snakewindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{//Добавить конфиг файл
    //Добавить переключение спрайтов;
    //Добавить базу данных хранения поля;
    //Установить на винду кутэ и запустить там проект;

    QApplication a(argc, argv);
    SnakeWindow w;
    w.show();
    return a.exec();
}
