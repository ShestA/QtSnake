#include "snake.hpp"

Snake::~Snake(){

}

Snake::Snake(QList<Tile*> body, int stepX, int stepY, eDirection dir, QRectF bord) : Body(body), StepX(stepX), StepY(stepY){
    this->Direction = dir;
    this->BorderRect = bord;
}

QGraphicsItemGroup* Snake::GetItems(){
    return this->BodyItems;
}

void Snake::SetItems(){
    this->BodyItems = new QGraphicsItemGroup;
    for (auto& val : this->Body)
        this->BodyItems->addToGroup(val);
}

void Snake::ClearItems(){
    for (auto& val : this->Body){
        this->BodyItems->removeFromGroup(val);
        delete val;
    }
    delete this->BodyItems;
}

void Snake::ChangeDirection(eDirection dir){
    this->Direction = dir;
}

eDirection Snake::GetDirection(){
    return this->Direction;
}

bool Snake::IsSnake(QPointF point) const{
    for (auto& val : this->Body)
        if (val->IsTile(point))
            return true;
    return false;
}

void Snake::Move(){
    QRectF tmp;
    QRectF tmp1;
    QRectF tmp2;

    tmp = this->GetHeadRect();
    switch(this->Direction){
    case eDirection::Up:
        tmp.moveTop(tmp.top() - StepX);
        break;
    case eDirection::Down:
        tmp.moveBottom(tmp.bottom() + StepX);
        break;
    case eDirection::Left:
        tmp.moveLeft(tmp.left() - StepY);
        break;
    case eDirection::Right:
        tmp.moveRight(tmp.right() + StepY);
        break;
    }
    if (!(this->BorderRect.contains(tmp))){
        switch(this->Direction){
        case eDirection::Up:
            tmp.moveBottom(this->BorderRect.bottom());
            break;
        case eDirection::Down:
            tmp.moveTop(this->BorderRect.top());
            break;
        case eDirection::Left:
            tmp.moveRight(this->BorderRect.right());
            break;
        case eDirection::Right:
            tmp.moveLeft(this->BorderRect.left());
            break;
        }
    }
    switch(this->Direction){
    case eDirection::Up:
        this->Body.front()->SetAngle(0);
        break;
    case eDirection::Down:
        this->Body.front()->SetAngle(180);
        break;
    case eDirection::Left:
        this->Body.front()->SetAngle(-90);
        break;
    case eDirection::Right:
        this->Body.front()->SetAngle(90);
        break;
    }
    for (auto& val : this->Body){
        tmp1 = val->boundingRect();
        val->SetRect(tmp);
        tmp = tmp1;
    }
    for (auto i = this->Body.begin() + 1; i < this->Body.end() - 1; i++){
        float x1, x2, x3, y1, y2, y3;
        bool x, y, z, q;

        tmp = (*(i - 1))->boundingRect();
        tmp1 = (*(i))->boundingRect();
        tmp2 = (*(i + 1))->boundingRect();
        x1 = tmp.center().x();
        y1 = tmp.center().y();
        x2 = tmp1.center().x();
        y2 = tmp1.center().y();
        x3 = tmp1.center().x();
        y3 = tmp1.center().y();

        x = tmp.x() < tmp2.x();
        y = tmp.y() > tmp2.y();
        z = tmp1.x() == tmp2.x();
        q = tmp.y() == tmp1.y();

        if ((x && y && z && q) || (!x && !y && !z && !q)){
            (*i)->ClearSprites();
            (*i)->AddSprite(QPixmap(":/image/res/TileSnakeBodyCorner.png"));
            (*i)->SetAngle(270);
        }else if ((!x && y && z && q) || (x && !y && !z && !q)){
            (*i)->ClearSprites();
            (*i)->AddSprite(QPixmap(":/image/res/TileSnakeBodyCorner.png"));
            (*i)->SetAngle(0);
        }else if ((x && !y && z && q) || (!x && y && !z && !q)){
            (*i)->ClearSprites();
            (*i)->AddSprite(QPixmap(":/image/res/TileSnakeBodyCorner.png"));
            (*i)->SetAngle(180);
        }else if ((!x && !y && z && q) || (x && y && !z && !q)){
            (*i)->ClearSprites();
            (*i)->AddSprite(QPixmap(":/image/res/TileSnakeBodyCorner.png"));
            (*i)->SetAngle(90);
        }else if ((x1 == x2) && (x2 == x3)){
            (*i)->ClearSprites();
            (*i)->AddSprite(QPixmap(":/image/res/TileSnakeBodyLine.png"));
            (*i)->SetAngle(0);
        }else{
            (*i)->ClearSprites();
            (*i)->AddSprite(QPixmap(":/image/res/TileSnakeBodyLine.png"));
            (*i)->SetAngle(90);
        }
    }
    bool x, y, z, q;

    x = (*(this->Body.end() - 2))->boundingRect().x() > this->Body.back()->boundingRect().x();
    y = (*(this->Body.end() - 2))->boundingRect().y() > this->Body.back()->boundingRect().y();
    z = (*(this->Body.end() - 2))->boundingRect().x() == this->Body.back()->boundingRect().x();
    q = (*(this->Body.end() - 2))->boundingRect().y() == this->Body.back()->boundingRect().y();
    if (x && q){
        this->Body.back()->SetAngle(180);
    }else if (!x && q){
        this->Body.back()->SetAngle(0);
    }else if (!y && z){
        this->Body.back()->SetAngle(90);
    }else{
        this->Body.back()->SetAngle(270);
    }
}

void Snake::ReverseMove(){
    QRectF tmp;
    QRectF tmp1;
    QRectF tmp2;

    tmp = this->GetTailRect();
    switch(this->Direction){
    case eDirection::Up:
        tmp.moveTop(tmp.top() - StepX);
        break;
    case eDirection::Down:
        tmp.moveBottom(tmp.bottom() + StepX);
        break;
    case eDirection::Left:
        tmp.moveLeft(tmp.left() - StepY);
        break;
    case eDirection::Right:
        tmp.moveRight(tmp.right() + StepY);
        break;
    }
    if (!(this->BorderRect.contains(tmp))){
        switch(this->Direction){
        case eDirection::Up:
            tmp.moveBottom(this->BorderRect.bottom());
            break;
        case eDirection::Down:
            tmp.moveTop(this->BorderRect.top());
            break;
        case eDirection::Left:
            tmp.moveRight(this->BorderRect.right());
            break;
        case eDirection::Right:
            tmp.moveLeft(this->BorderRect.left());
            break;
        }
    }
    for (auto i = this->Body.end() - 1; i >= this->Body.begin(); i--){
        tmp1 = (*i)->boundingRect();
        (*i)->SetRect(tmp);
        tmp = tmp1;
    }
    switch(this->Direction){
    case eDirection::Up:
        this->Body.last()->SetAngle(270);
        break;
    case eDirection::Down:
        this->Body.last()->SetAngle(90);
        break;
    case eDirection::Left:
        this->Body.last()->SetAngle(180);
        break;
    case eDirection::Right:
        this->Body.last()->SetAngle(0);
        break;
    }
    for (auto i = this->Body.begin() + 1; i < this->Body.end() - 1; i++){
        float x1, x2, x3, y1, y2, y3;
        bool x, y, z, q;

        tmp = (*(i - 1))->boundingRect();
        tmp1 = (*(i))->boundingRect();
        tmp2 = (*(i + 1))->boundingRect();
        x1 = tmp.center().x();
        y1 = tmp.center().y();
        x2 = tmp1.center().x();
        y2 = tmp1.center().y();
        x3 = tmp1.center().x();
        y3 = tmp1.center().y();

        x = tmp.x() < tmp2.x();
        y = tmp.y() > tmp2.y();
        z = tmp1.x() == tmp2.x();
        q = tmp.y() == tmp1.y();

        if ((x && y && z && q) || (!x && !y && !z && !q)){
            (*i)->ClearSprites();
            (*i)->AddSprite(QPixmap(":/image/res/TileSnakeBodyCorner.png"));
            (*i)->SetAngle(270);
        }else if ((!x && y && z && q) || (x && !y && !z && !q)){
            (*i)->ClearSprites();
            (*i)->AddSprite(QPixmap(":/image/res/TileSnakeBodyCorner.png"));
            (*i)->SetAngle(0);
        }else if ((x && !y && z && q) || (!x && y && !z && !q)){
            (*i)->ClearSprites();
            (*i)->AddSprite(QPixmap(":/image/res/TileSnakeBodyCorner.png"));
            (*i)->SetAngle(180);
        }else if ((!x && !y && z && q) || (x && y && !z && !q)){
            (*i)->ClearSprites();
            (*i)->AddSprite(QPixmap(":/image/res/TileSnakeBodyCorner.png"));
            (*i)->SetAngle(90);
        }else if ((x1 == x2) && (x2 == x3)){
            (*i)->ClearSprites();
            (*i)->AddSprite(QPixmap(":/image/res/TileSnakeBodyLine.png"));
            (*i)->SetAngle(0);
        }else{
            (*i)->ClearSprites();
            (*i)->AddSprite(QPixmap(":/image/res/TileSnakeBodyLine.png"));
            (*i)->SetAngle(90);
        }
    }
    bool x, y, z, q;

    x = (*(this->Body.begin() + 1))->boundingRect().x() > (*this->Body.begin())->boundingRect().x();
    y = (*(this->Body.begin() + 1))->boundingRect().y() > (*this->Body.begin())->boundingRect().y();
    z = (*(this->Body.begin() + 1))->boundingRect().x() == (*this->Body.begin())->boundingRect().x();
    q = (*(this->Body.begin() + 1))->boundingRect().y() == (*this->Body.begin())->boundingRect().y();
    if (x && q){
        this->Body.front()->SetAngle(270);
    }else if (!x && q){
        this->Body.front()->SetAngle(90);
    }else if (!y && z){
        this->Body.front()->SetAngle(180);
    }else{
        this->Body.front()->SetAngle(0);
    }
}

void Snake::SetReverse(){
    this->Reverse = true;
}

void Snake::ClearReverse(){
    this->Reverse = false;
}

bool Snake::IsReverse(){
    return this->Reverse;
}

QRectF Snake::GetHeadRect() const{
    return this->Body.front()->boundingRect();
}

QRectF Snake::GetTailRect() const{
    return this->Body.back()->boundingRect();
}
