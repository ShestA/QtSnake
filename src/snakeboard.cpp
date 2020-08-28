#include "snakeboard.hpp"
#include "algorithms.hpp"

SnakeBoard::SnakeBoard(QRectF rect1, QRectF rect2, QList<QList<Tile>> cells, int columns, int rows){
    this->BoardRect = rect1;
    this->CellsRect = rect2;
    this->Background.load(":/image/res/BackgroundField.png");
    this->TileWidth = rect2.width() / columns;
    this->TileHeight = rect2.height() / rows;
    this->Cells = cells;
    this->ColumnsCount = columns;
    this->RowsCount = rows;
    this->DeadFlag = false;
    this->Snakes = QMap<snakeID, Snake*>();
}

SnakeBoard::~SnakeBoard(){
    for (auto& val : this->Snakes)
        delete val;
}

QRectF SnakeBoard::boundingRect() const{
    return this->BoardRect;
}

QGraphicsItemGroup* SnakeBoard::GetItems(){
    return this->GraphicsItems;
}

void SnakeBoard::SetItems(){
    this->GraphicsItems = new QGraphicsItemGroup;
    for (auto& val : this->Cells){
        for (auto& val1 : val){
            this->GraphicsItems->addToGroup(&val1);
        }
    }
    for (auto& val : this->Snakes){
        val->SetItems();
        this->GraphicsItems->addToGroup(val->GetItems());
    }
}

void SnakeBoard::ClearItems(){
    for (auto& val : this->Cells){
        for (auto& val1 : val){
            this->GraphicsItems->removeFromGroup(&val1);
        }
    }
    for (auto& val : this->Snakes){
        this->GraphicsItems->removeFromGroup(val->GetItems());
        val->ClearItems();
    }

    delete this->GraphicsItems;
}

void SnakeBoard::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    painter->drawPixmap(this->BoardRect.toRect(), this->Background);
}

snakeID SnakeBoard::AddSnake(){
    snakeID id;
    int sprout;

    id = 0;
    sprout = 0;
    qsrand(QDateTime::currentMSecsSinceEpoch());
    while(this->Snakes.contains(id)){
        sprout = qrand() % 1000000;
        id = this->Snakes.keys().count() + sprout;
    }
    Snakes[id] = new Snake(this->SnakeGenerator(), this->TileWidth, this->TileHeight, eDirection::Up, this->CellsRect);

    return id;
}

void SnakeBoard::RemoveSnake(snakeID id){
    if (Snakes.contains(id)){
        delete Snakes[id];
        Snakes.remove(id);
    }
}

bool SnakeBoard::GoAhead(snakeID id){
    if (this->Snakes.contains(id)){
        if (CanMove(id)){
            this->Snakes[id]->ClearReverse();
            this->Snakes[id]->Move();
            return true;
        }else{
            this->Snakes[id]->ChangeDirection(eDirection::Up);
            if (CanMove(id)){
                this->Snakes[id]->ClearReverse();
                this->Snakes[id]->Move();
                return true;
            }
            this->Snakes[id]->ChangeDirection(eDirection::Left);
            if (CanMove(id)){
                this->Snakes[id]->ClearReverse();
                this->Snakes[id]->Move();
                return true;
            }
            this->Snakes[id]->ChangeDirection(eDirection::Right);
            if (CanMove(id)){
                this->Snakes[id]->ClearReverse();
                this->Snakes[id]->Move();
                return true;
            }
            this->Snakes[id]->ChangeDirection(eDirection::Down);
            if (CanMove(id)){
                this->Snakes[id]->ClearReverse();
                this->Snakes[id]->Move();
                return true;
            }
        }
    }
    return false;
}

bool SnakeBoard::GoBack(snakeID id){
    if (this->Snakes.contains(id)){
        if (CanReverseMove(id)){
            this->Snakes[id]->SetReverse();
            this->Snakes[id]->ReverseMove();
            return true;
        }else{
            this->Snakes[id]->ChangeDirection(eDirection::Up);
            if (CanReverseMove(id)){
                this->Snakes[id]->SetReverse();
                this->Snakes[id]->ReverseMove();
                return true;
            }
            this->Snakes[id]->ChangeDirection(eDirection::Left);
            if (CanReverseMove(id)){
                this->Snakes[id]->SetReverse();
                this->Snakes[id]->ReverseMove();
                return true;
            }
            this->Snakes[id]->ChangeDirection(eDirection::Right);
            if (CanReverseMove(id)){
                this->Snakes[id]->SetReverse();
                this->Snakes[id]->ReverseMove();
                return true;
            }
            this->Snakes[id]->ChangeDirection(eDirection::Down);
            if (CanReverseMove(id)){
                this->Snakes[id]->SetReverse();
                this->Snakes[id]->ReverseMove();
                return true;
            }
        }
    }
    return false;
}

bool SnakeBoard::IsDead(){
    return this->DeadFlag;
}

void SnakeBoard::ClearDead(){
    this->DeadFlag = false;
}

void SnakeBoard::ChangeDirection(snakeID id, eDirection dir){
    if (Snakes.contains(id))
        this->Snakes[id]->ChangeDirection(dir);
}

bool SnakeBoard::CanMove(snakeID id){
    if (this->Snakes.contains(id)){
        QRectF headRect;
        QRectF tailRect;
        eDirection headDirection;

        headRect = this->Snakes[id]->GetHeadRect();
        tailRect = this->Snakes[id]->GetTailRect();
        headDirection = this->Snakes[id]->GetDirection();
        switch(headDirection){
        case eDirection::Up:
            headRect.moveTop(headRect.top() - this->TileHeight);
            break;
        case eDirection::Down:
            headRect.moveBottom(headRect.bottom() + this->TileHeight);
            break;
        case eDirection::Left:
            headRect.moveLeft(headRect.left() - this->TileWidth);
            break;
        case eDirection::Right:
            headRect.moveRight(headRect.right() + this->TileWidth);
            break;
        }
        if (!(this->boundingRect().contains(headRect))){
            switch(headDirection){
            case eDirection::Up:
                headRect.moveBottom(this->boundingRect().bottom());
                break;
            case eDirection::Down:
                headRect.moveTop(this->boundingRect().top());
                break;
            case eDirection::Left:
                headRect.moveRight(this->boundingRect().right());
                break;
            case eDirection::Right:
                headRect.moveLeft(this->boundingRect().left());
                break;
            }
        }
        for (auto& val : this->Snakes){
            if (val->IsSnake(headRect.center())){
                if (!headRect.contains(tailRect)){
                    if (val != this->Snakes[id])
                        DeadFlag = true;
                    return false;
                }else if (val->IsReverse()){
                    if (val != this->Snakes[id])
                        DeadFlag = true;
                    return false;
                }
                break;
            }
        }

        for (auto& val : this->Cells){
            for (auto& val1 : val){
                if (val1.IsTile(headRect.center())){
                    if (val1.IsSolid())
                        return false;
                    break;
                }
            }
        }
        return true;
        }
    return false;
}

bool SnakeBoard::CanReverseMove(snakeID id){
    if (this->Snakes.contains(id)){
        QRectF tailRect;
        QRectF headRect;
        eDirection tailDirection;

        tailRect = this->Snakes[id]->GetTailRect();
        headRect = this->Snakes[id]->GetHeadRect();
        tailDirection = this->Snakes[id]->GetDirection();
        switch(tailDirection){
        case eDirection::Up:
            tailRect.moveTop(tailRect.top() - this->TileHeight);
            break;
        case eDirection::Down:
            tailRect.moveBottom(tailRect.bottom() + this->TileHeight);
            break;
        case eDirection::Left:
            tailRect.moveLeft(tailRect.left() - this->TileWidth);
            break;
        case eDirection::Right:
            tailRect.moveRight(tailRect.right() + this->TileWidth);
            break;
        }
        if (!(this->boundingRect().contains(headRect))){
            switch(tailDirection){
            case eDirection::Up:
                tailRect.moveBottom(this->boundingRect().bottom());
                break;
            case eDirection::Down:
                tailRect.moveTop(this->boundingRect().top());
                break;
            case eDirection::Left:
                tailRect.moveRight(this->boundingRect().right());
                break;
            case eDirection::Right:
                tailRect.moveLeft(this->boundingRect().left());
                break;
            }
        }
        for (auto& val : this->Snakes){
            if (val->IsSnake(tailRect.center())){
                if (!tailRect.contains(headRect)){
                    if (val != this->Snakes[id])
                        DeadFlag = true;
                    return false;
                }else if (val->IsReverse()){
                    if (val != this->Snakes[id])
                        DeadFlag = true;
                    return false;
                }
                break;
            }
        }

        for (auto& val : this->Cells){
            for (auto& val1 : val){
                if (val1.IsTile(tailRect.center())){
                    if (val1.IsSolid())
                        return false;
                    break;
                }
            }
        }
        return true;
        }
    return false;
}

QList<Tile*> SnakeBoard::SnakeGenerator(){
    QPoint start;
    QPoint finish;
    QList<QPoint> path;
    QList<QList<LeeVertex>> map;
    LeeVertex tmpVertex;
    QList<Tile*> snake;
    Tile* tmpTile;
    int i;
    int j;

    i = 0;
    for (auto& val : this->Cells){
        j = 0;
        map.push_back(QList<LeeVertex>());
        for (auto& val1 : val){
            tmpVertex.Point = QPoint(i, j);
            tmpVertex.Steps = -1;
            tmpVertex.Marked = false;
            tmpVertex.Open = !val1.IsSolid();
            for (auto& val2 : this->Snakes){
                tmpVertex.Open &= !val2->IsSnake(val1.boundingRect().center());
            }
            map.back().push_back(tmpVertex);
            j++;
        }
        i++;
    }

    do{
        qsrand(QDateTime::currentMSecsSinceEpoch());
        start.setX(qrand() % this->ColumnsCount);
        finish.setX(qrand() % this->ColumnsCount);
        start.setY(qrand() % this->RowsCount);
        finish.setY(qrand() % this->RowsCount);
        path = FindPath(map, start, finish);
    }while (path.size() < 3);

    for (auto& val : path){
        tmpTile = new Tile(this->Cells[val.x()][val.y()].boundingRect());
        tmpTile->SetAngle(0);
        tmpTile->AddSprite(QPixmap(":/image/res/TileSnakeBodyLine.png"));
        tmpTile->SetCollision(true);
        snake.push_back(tmpTile);
    }
    snake.front()->ClearSprites();
    snake.front()->AddSprite(QPixmap(":/image/res/TileSnakeHead.png"));
    snake.back()->ClearSprites();
    snake.back()->AddSprite(QPixmap(":/image/res/TileSnakeTail.png"));
    
    return snake;
}

QList<QList<Tile>> FieldGenerator(QRectF rect, int columns, int rows){
    QList<QList<Tile>> tmp;
    int tileW;
    int tileH;
    QRectF tileRect;
    Tile tmpTile(QRectF(0,0,0,0));

    QList<bool> maze = CreateMaze(columns, rows);

    tileW = rect.width() / columns;
    tileH = rect.height() / rows;
    tileRect = QRectF(rect.left(), rect.top(), tileW, tileH);

    tmpTile.SetAngle(0);
    tmpTile.SetCollision(false);
    while(rect.contains(tileRect.bottomRight())){
        tmp.push_back(QList<Tile>());
        while((rect.contains(tileRect.bottomRight())) && (maze.size() > 0)){
            tmpTile.SetRect(tileRect);
            if (maze.front()){
                tmpTile.AddSprite(QPixmap(":/image/res/Wall.png"));
                tmpTile.SetCollision(1);
            }else{
                tmpTile.AddSprite(QPixmap(":/image/res/Tile.png"));
                tmpTile.SetCollision(0);
            }
            maze.pop_front();
            tmp.back().push_back(tmpTile);
            tmpTile.ClearSprites();
            tileRect.moveBottom(tileRect.bottom() + tileH);
        }
        tileRect.moveTop(rect.top());
        tileRect.moveRight(tileRect.right() + tileW);
    }
    return tmp;
}

QList<QList<Tile>> EmptyGenerator(QRectF rect, int columns, int rows){
    QList<QList<Tile>> tmp;
    int tileW;
    int tileH;
    QRectF tileRect;
    Tile tmpTile(QRect(0,0,0,0));

    tileW = rect.width() / columns;
    tileH = rect.height() / rows;
    tileRect = QRectF(rect.left(), rect.top(), tileW, tileH);

    while(rect.contains(tileRect.bottomRight())){
        tmp.push_back(QList<Tile>());
        while(rect.contains(tileRect.bottomRight())){
            tmpTile.SetRect(tileRect);
            tmpTile.AddSprite(QPixmap(":/image/res/Tilee.png"));
            tmpTile.SetCollision(false);
            tmp.back().push_back(tmpTile);
            tileRect.moveBottom(tileRect.bottom() + tileH);
        }
        tileRect.moveTop(rect.top());
        tileRect.moveRight(tileRect.right() + tileW);
    }
    return tmp;
}
