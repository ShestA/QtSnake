#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <QList>
#include <QPoint>
#include <QDate>

class LeeVertex{
public:
    LeeVertex();
    LeeVertex(const LeeVertex& other);
    LeeVertex(LeeVertex&& other);
    LeeVertex& operator=(const LeeVertex& other);
    LeeVertex& operator=(LeeVertex&& other);

    QPoint Point;
    int Steps;
    bool Marked;
    bool Open;
};

class MazeVertex{
public:
    MazeVertex();
    MazeVertex(const MazeVertex& other);
    MazeVertex(MazeVertex&& other);
    MazeVertex& operator=(const MazeVertex& other);
    MazeVertex& operator=(MazeVertex&& other);

    QPoint Point;
    bool Visited;
    bool Wall;
    static int Unvisited;
};

/*****Поиск наикратчайшего пути между точками основанный на алгоритме Ли в окрестности Мура*****/
QList<QPoint> FindPath(QList<QList<LeeVertex>>, QPoint, QPoint);

QList<bool> CreateMaze(int, int);
#endif // ALGORITHMS_HPP
