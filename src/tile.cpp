#include "tile.hpp"

Tile::~Tile(){
    for (auto val : Sprites){
        delete val;
    }
}

Tile::Tile(QRectF rect){
    this->TileRect = rect;
}

Tile::Tile(const Tile& other){
    this->TileRect = other.TileRect;
    this->SpriteAngle = other.SpriteAngle;
    this->Mirroring = other.Mirroring;
    this->Collision = other.Collision;
    for (auto& val : other.Sprites){
        this->Sprites.push_back(new QPixmap);
        *(this->Sprites.back()) = *val;
    }
}

Tile::Tile(Tile&& other){
    this->TileRect = other.TileRect;
    this->SpriteAngle = other.SpriteAngle;
    this->Mirroring = other.Mirroring;
    this->Collision = other.Collision;
    for (QPixmap* val : other.Sprites){
        this->Sprites.push_back(val);
        val = nullptr;
    }
    this->Timer = other.Timer;
    other.Timer = nullptr;
    this->AnimationWire = other.AnimationWire;
}

QRectF Tile::boundingRect() const{
    return TileRect;
}

void Tile::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    painter->drawPixmap(this->TileRect.toRect(), QPixmap(this->Sprites.front()->transformed(QTransform().rotate(this->SpriteAngle))));
}

void Tile::SetRect(QRectF rect){
    this->TileRect = rect;
}

void Tile::SetAngle(float angle){
    this->SpriteAngle = angle;
}

void Tile::Mirror(){
    this->Mirroring = !this->Mirroring;
}

void Tile::AddSprite(QPixmap sprite){
    QPixmap* newSprite = new QPixmap(sprite);
    this->Sprites.push_back(newSprite);

}

void Tile::SetCollision(bool power){
    this->Collision = power;
}

bool Tile::IsSolid() const{
    return this->Collision;
}

bool Tile::IsTile(QPointF point) const{
    return this->TileRect.contains(point);
}

void Tile::ClearSprites(){
    for (auto& val : this->Sprites){
        delete val;
    }
    this->Sprites.clear();
}

void Tile::StartAnim(int time){
}

void Tile::StopAnim(){
}

void Tile::AnimationStep(){
}
