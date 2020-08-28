#include "algorithms.hpp"

LeeVertex::LeeVertex(){
    Point = QPoint(0,0);
    Steps = -1;
    Marked = false;
    Open = true;
}

LeeVertex::LeeVertex(const LeeVertex& other){
    this->Point = other.Point;
    this->Steps = other.Steps;
    this->Marked = other.Marked;
    this->Open = other.Open;
}

LeeVertex::LeeVertex(LeeVertex&& other){
    this->Point = other.Point;
    this->Steps = other.Steps;
    this->Marked = other.Marked;
    this->Open = other.Open;
}

LeeVertex& LeeVertex::operator=(const LeeVertex& other){
    this->Point = other.Point;
    this->Steps = other.Steps;
    this->Marked = other.Marked;
    this->Open = other.Open;
    return *this;
}

LeeVertex& LeeVertex::operator=(LeeVertex&& other){
    this->Point = other.Point;
    this->Steps = other.Steps;
    this->Marked = other.Marked;
    this->Open = other.Open;
    return *this;
}

MazeVertex::MazeVertex() {
    this->Point = QPoint(0,0);
    this->Visited = false;
    this->Wall = false;
}

MazeVertex::MazeVertex(const MazeVertex& other){
    this->Point = other.Point;
    this->Visited = other.Visited;
    this->Wall = other.Wall;
}

MazeVertex::MazeVertex(MazeVertex&& other){
    this->Point = other.Point;
    this->Visited = other.Visited;
    this->Wall = other.Wall;
}

MazeVertex& MazeVertex::operator=(const MazeVertex& other){
    this->Point = other.Point;
    this->Visited = other.Visited;
    this->Wall = other.Wall;
    return *this;
}

MazeVertex& MazeVertex::operator=(MazeVertex&& other){
    this->Point = other.Point;
    this->Visited = other.Visited;
    this->Wall = other.Wall;
    return *this;
}

QList<QPoint> FindPath(QList<QList<LeeVertex>> Graph, QPoint Start, QPoint Finish){
    QMultiMap<int, LeeVertex> Wave;
    int Pass;
    bool Passed;
    QPoint Left, Right, Up, Down;
    QList<QPoint> Path;

    Graph[Start.x()][Start.y()].Steps = 0;
    Graph[Start.x()][Start.y()].Marked = true;
    Wave.insert(0, Graph[Start.x()][Start.y()]);
    Pass = 0;
    Passed = true;
    while ((Passed) && (!Graph[Finish.x()][Finish.y()].Marked)){
        Passed = false;
        for (auto& val : Wave.values(Pass)){
            Left = val.Point;   Left.setX(Left.x() - 1);
            Right = val.Point;  Right.setX(Right.x() + 1);
            Up = val.Point;     Up.setY(Up.y() - 1);
            Down = val.Point;   Down.setY(Down.y() + 1);

            if (Left.x() > 0){
                if ((!Graph[Left.x()][Left.y()].Marked) && (Graph[Left.x()][Left.y()].Open)){
                    Graph[Left.x()][Left.y()].Steps = Pass + 1;
                    Graph[Left.x()][Left.y()].Marked = true;
                    Wave.insert(Pass + 1, Graph[Left.x()][Left.y()]);
                    Passed = true;
                }
            }
            if (Right.x() < Graph.size()){
                if ((!Graph[Right.x()][Right.y()].Marked) && (Graph[Right.x()][Right.y()].Open)){
                    Graph[Right.x()][Right.y()].Steps = Pass + 1;
                    Graph[Right.x()][Right.y()].Marked = true;
                    Wave.insert(Pass + 1, Graph[Right.x()][Right.y()]);
                    Passed = true;
                }
            }
            if (Up.y() > 0){
                if ((!Graph[Up.x()][Up.y()].Marked) && (Graph[Up.x()][Up.y()].Open)){
                    Graph[Up.x()][Up.y()].Steps = Pass + 1;
                    Graph[Up.x()][Up.y()].Marked = true;
                    Wave.insert(Pass + 1, Graph[Up.x()][Up.y()]);
                    Passed = true;
                }
            }
            if (Down.y() < Graph.begin()->length()){
                if ((!Graph[Down.x()][Down.y()].Marked) && (Graph[Down.x()][Down.y()].Open)){
                    Graph[Down.x()][Down.y()].Steps = Pass + 1;
                    Graph[Down.x()][Down.y()].Marked = true;
                    Wave.insert(Pass + 1, Graph[Down.x()][Down.y()]);
                    Passed = true;
                }
            }
        }
        Pass++;
    }

    if (Graph[Finish.x()][Finish.y()].Marked){
        Path.push_back(Graph[Finish.x()][Finish.y()].Point);
        Pass = Graph[Finish.x()][Finish.y()].Steps - 1;
        while (Pass > 0){
            Passed = false;
            for (auto& val : Wave.values(Pass)){
                if (val.Point.x() == Path.back().x()){
                    if ((val.Point.y() == Path.back().y() + 1) || (val.Point.y() == Path.back().y() - 1)){
                        Path.push_back(val.Point);
                        Pass--;
                        Passed = true;
                        break;
                    }
                }else if (val.Point.y() == Path.back().y()){
                    if ((val.Point.x() == Path.back().x() + 1) || (val.Point.x() == Path.back().x() - 1)){
                        Path.push_back(val.Point);
                        Pass--;
                        Passed = true;
                        break;
                    }
                }
            }
            if (!Passed){
                Path.clear();
                break;
            }
        }
    }
    return Path;
}

int MazeVertex::Unvisited {0};

QList<bool> CreateMaze(int w, int h){
    QList<QList<MazeVertex*>> maze;
    QList<MazeVertex*> pathStack;
    MazeVertex* vert;
    QPoint current;
    QPoint applicant;
    QList<bool> ret;
    MazeVertex::Unvisited = 0;

    for (int i = 0; i < w; i++){
        maze.push_back(QList<MazeVertex*>());

        for (int j = 0; j < h; j++){
            bool x;
            bool y;
            bool z;

            x = i % 2;
            y = j % 2;
            z = (i == 0) || (j == 0) || (i == w - 1) || (j == h - 1);
            vert = new MazeVertex;
            vert->Wall = !x || !y || z;
            vert->Point = QPoint(i, j);
            maze[i].push_back(vert);
            maze.last().last()->Unvisited += !(vert->Wall);
        }
    }
    auto HavePath = [&](QPoint pos) -> bool{
        if ((pos.x() - 2 > 0) && (!(maze[pos.x() - 2][pos.y()]->Visited))){
            return true;
        }else if ((pos.y() - 2 > 0) && (!(maze[pos.x()][pos.y() - 2]->Visited))){
            return true;
        }else if ((pos.x() + 2 < maze.size() - 1) && (!(maze[pos.x() + 2][pos.y()]->Visited))){
            return true;
        }else if ((pos.y() + 2 < maze[pos.x()].size() - 1) && (!(maze[pos.x()][pos.y() + 2]->Visited))){
            return true;
        }else
            return false;
    };
    auto ChoosePath = [&](QPoint pos) -> QPoint{
        int state;
        bool l, r, u, d;
        int bl, br, bu, bd;

        l = false;r = false; u = false; d = false;
        bl = 0; br = 0; bu = 0; bd = 0;

        if ((pos.x() - 2 > 0) && (!(maze[pos.x() - 2][pos.y()]->Visited))){
            l = true;
        }
        if ((pos.y() - 2 > 0) && (!(maze[pos.x()][pos.y() - 2]->Visited))){
            r = true;
        }
        if ((pos.x() + 2 < maze.size() - 1) && (!(maze[pos.x() + 2][pos.y()]->Visited))){
            u = true;
        }if ((pos.y() + 2 < maze[pos.x()].size() - 1) && (!(maze[pos.x()][pos.y() + 2]->Visited))){
            d = true;
        }
        state = 0;
        if (l) state++;
        if (r) state++;
        if (u) state++;
        if (d) state++;
        bl = 10000 * l;
        br = 10000 * (l + r);
        bu = 10000 * (l + r + u);
        bd = 10000 * (l + r + u + d);
        for(size_t i = 0; i < 0x00000FFF; i++){
            qsrand(QDateTime::currentMSecsSinceEpoch() * QDateTime::currentMSecsSinceEpoch());
        }
        state *= qrand() % 10000;
        if (state < bl){
            return QPoint(pos.x() - 2, pos.y());
        }
        if (state < br){
            return QPoint(pos.x(), pos.y() - 2);
        }
        if (state < bu){
            return QPoint(pos.x() + 2, pos.y());
        }
        if (state < bd){
            return QPoint(pos.x(), pos.y() + 2);
        }
        return QPoint(0,0);
    };
    auto DestroyWall = [&](QPoint src, QPoint dest){
        QPoint offset;
        QPoint target;
        offset.setX((dest.x() - src.x()) / 2);
        offset.setY((dest.y() - src.y()) / 2);
        target.setX(src.x() + offset.x());
        target.setY(src.y() + offset.y());
        maze[target.x()][target.y()]->Wall = false;
    };
    current = QPoint(1,1);
    maze[1][1]->Visited = 1;
    maze.first().first()->Unvisited--;
    if ((maze.size() > 2) && (maze.first().size() > 2)){
        do{
            if (HavePath(current)){
                pathStack.push_back(maze[current.x()][current.y()]);
                applicant = ChoosePath(current);
                DestroyWall(current, applicant);
                maze[applicant.x()][applicant.y()]->Visited = true;
                maze.first().first()->Unvisited--;
                current = applicant;
            }else if (pathStack.size() > 0){
                current = pathStack.back()->Point;
                pathStack.pop_back();
            }else{
                //break;
            }
        }while (maze.first().first()->Unvisited > 0);
    }
    for(auto& val : maze){
        for(auto& val1 : val){
            ret.push_back(val1->Wall);
        }
    }
    for(auto& val : maze){
        for(auto& val1 : val)
            delete val1;
    }
    return ret;
}
