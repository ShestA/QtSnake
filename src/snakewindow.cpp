#include "snakewindow.hpp"

SnakeWindow::SnakeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SnakeWindow)
{
    this->ui->setupUi(this);
    this->scene = new QGraphicsScene(this);
    this->ui->gameField->setScene(this->scene);
    this->ui->gameField->setRenderHint(QPainter::Antialiasing);
    this->scene->setSceneRect(this->ui->gameField->sceneRect());
    this->scene->addPixmap(QPixmap(":/image/res/Background.png"));
    this->ui->saveButton->setStyleSheet("border-image:url(:/image/res/Save.png);");
    this->ui->generateButton->setStyleSheet("border-image:url(:/image/res/Gen.png);");
    this->ui->logoButton->setStyleSheet("border-image:url(:/image/res/Logo.png);");
    this->ui->spaceButton->setStyleSheet("border-image:url(:/image/res/Space.png);");
    connect(this->ui->generateButton, SIGNAL(pressed()), this, SLOT(pressGeneratorButton()));
    connect(this->ui->generateButton, SIGNAL(released()), this, SLOT(releaseGeneratorButton()));
    connect(this->ui->saveButton, SIGNAL(pressed()), this, SLOT(pressSaveButton()));
    connect(this->ui->saveButton, SIGNAL(released()), this, SLOT(releaseSaveButton()));
    connect(this->ui->spaceButton, SIGNAL(pressed()), this, SLOT(pressSpaceButton()));
    connect(this->ui->spaceButton, SIGNAL(released()), this, SLOT(releaseSpaceButton()));
    this->FPS = new QTimer(this);
    this->FPS->start(33);
    connect(FPS, SIGNAL(timeout()), this, SLOT(updater()));
    Startuem();
}

SnakeWindow::~SnakeWindow()
{
    delete this->AI;
    delete this->Logic;
    delete this->FPS;
    delete this->gameBoard;
    delete this->scene;
    delete this->ui;
}

void SnakeWindow::updater(){
    this->scene->update(this->gameBoard->boundingRect());
}

void SnakeWindow::pressGeneratorButton(){
    QPoint pos;

    pos = this->ui->generateButton->pos();
    this->ui->generateButton->resize(170, 85);
    pos.setX(pos.x() + 20);
    pos.setY(pos.y() + 15);
    this->ui->generateButton->move(pos);
}

void SnakeWindow::releaseGeneratorButton(){
    QPoint pos;

    pos = this->ui->generateButton->pos();
    this->ui->generateButton->resize(200, 100);
    pos.setX(pos.x() - 20);
    pos.setY(pos.y() - 15);
    this->ui->generateButton->move(pos);

    this->Restart();
    return;
}

void SnakeWindow::pressSaveButton(){
    QPoint pos;

    pos = this->ui->saveButton->pos();
    this->ui->saveButton->resize(170, 85);
    pos.setX(pos.x() + 15);
    pos.setY(pos.y() + 15);
    this->ui->saveButton->move(pos);
}

void SnakeWindow::releaseSaveButton(){
    QPoint pos;
    SQLwrap *sql;

    pos = this->ui->saveButton->pos();
    this->ui->saveButton->resize(200, 100);
    pos.setX(pos.x() - 15);
    pos.setY(pos.y() - 15);
    this->ui->saveButton->move(pos);

    sql = new SQLwrap();
    sql->OpenDB("","","","");
    sql->sendData(QList<QList<bool>>());
    sql->closeDB();
    delete sql;
}

void SnakeWindow::pressSpaceButton(){

}

void SnakeWindow::releaseSpaceButton(){
    QRectF rect1, rect2;
    int columns;
    int rows;

    this->Logic->stop();
    this->AI->stop();
    this->scene->destroyItemGroup(gameBoard->GetItems());
    this->gameBoard->RemoveSnake(this->SnakeOneID);
    this->gameBoard->RemoveSnake(this->SnakeTwoID);
    delete this->gameBoard;

    rect1 = QRectF(10,10,560,560);
    rect2 = QRectF(50,50,480,480);
    columns = 7;
    rows = 7;

    this->SnakeOneDirection = eDirection::Up;
    this->SnakeTwoDirection = eDirection::Up;

    this->gameBoard = new SnakeBoard(rect1, rect2, EmptyGenerator(rect2, columns, rows), columns, rows);
    this->SnakeOneID = this->gameBoard->AddSnake();
    this->SnakeTwoID = this->gameBoard->AddSnake();
    this->randomAI();

    this->ReverseCounterSnakeOne = 0;
    this->ReverseCounterSnakeTwo = 0;

    this->gameBoard->SetItems();
    this->scene->addItem(this->gameBoard->GetItems());

    this->Logic = new QTimer(this);
    this->AI = new QTimer(this);

    connect(Logic, SIGNAL(timeout()), this, SLOT(snakeUpdater()));
    connect(AI, SIGNAL(timeout()), this, SLOT(randomAI()));

    this->Logic->start(13);
    this->AI->start(13);


    this->scene->update(this->gameBoard->boundingRect());
    this->update();
    this->setFocus();
    this->show();
}

void SnakeWindow::Startuem(){
    QRectF rect1, rect2;
    int columns;
    int rows;

    rect1 = QRectF(10,10,560,560);
    rect2 = QRectF(50,50,480,480);
    columns = 17;
    rows = 17;

    this->SnakeOneDirection = eDirection::Up;
    this->SnakeTwoDirection = eDirection::Up;

    this->gameBoard = new SnakeBoard(rect1, rect2, FieldGenerator(rect2, columns, rows), columns, rows);
    this->SnakeOneID = this->gameBoard->AddSnake();
    this->SnakeTwoID = this->gameBoard->AddSnake();
    this->randomAI();

    this->ReverseCounterSnakeOne = 0;
    this->ReverseCounterSnakeTwo = 0;

    this->scene->addItem(this->gameBoard);
    this->gameBoard->SetItems();
    this->scene->addItem(this->gameBoard->GetItems());

    this->Logic = new QTimer(this);
    this->AI = new QTimer(this);

    connect(Logic, SIGNAL(timeout()), this, SLOT(snakeUpdater()));
    connect(AI, SIGNAL(timeout()), this, SLOT(randomAI()));

    this->Logic->start(66);
    this->AI->start(66);


    this->scene->update(this->gameBoard->boundingRect());
    this->update();
    this->setFocus();
    this->show();
}

void SnakeWindow::RestartSnakes(){
    this->Logic->stop();

    this->scene->destroyItemGroup(gameBoard->GetItems());

    this->gameBoard->RemoveSnake(this->SnakeOneID);
    this->gameBoard->RemoveSnake(this->SnakeTwoID);

    this->SnakeOneID = this->gameBoard->AddSnake();
    this->SnakeTwoID = this->gameBoard->AddSnake();
    this->randomAI();
    this->gameBoard->SetItems();

    this->ReverseCounterSnakeOne = 0;
    this->ReverseCounterSnakeTwo = 0;

    this->scene->addItem(gameBoard->GetItems());

    this->Logic->start(66);
}

void SnakeWindow::Restart(){
    this->Logic->stop();
    this->AI->stop();
    this->scene->destroyItemGroup(gameBoard->GetItems());
    this->gameBoard->RemoveSnake(this->SnakeOneID);
    this->gameBoard->RemoveSnake(this->SnakeTwoID);
    delete this->gameBoard;
    this->Startuem();
}

void SnakeWindow::snakeUpdater(){
    this->gameBoard->ChangeDirection(this->SnakeTwoID, this->SnakeTwoDirection);
    this->gameBoard->ChangeDirection(this->SnakeOneID, this->SnakeOneDirection);
    if ((this->ReverseCounterSnakeOne == 0)&&(this->gameBoard->GoAhead(SnakeOneID))){

    }else{
        if (this->gameBoard->IsDead()){
            this->gameBoard->ClearDead();
            this->RestartSnakes();
        }else{
            if (this->ReverseCounterSnakeOne == 0)
                this->ReverseCounterSnakeOne = 35;
            this->ReverseCounterSnakeOne--;
            this->gameBoard->GoBack(SnakeOneID);
        }
    }
    if ((this->ReverseCounterSnakeTwo == 0)&&(gameBoard->GoAhead(SnakeTwoID))){

    }else{
        if (this->gameBoard->IsDead()){
            this->gameBoard->ClearDead();
            this->RestartSnakes();
        }else{
            if (this->ReverseCounterSnakeTwo == 0)
                this->ReverseCounterSnakeTwo = 35;
            this->ReverseCounterSnakeTwo--;
            gameBoard->GoBack(SnakeTwoID);
        }
    }
}

void SnakeWindow::randomAI(){
    int sproutOne, sproutTwo;

    qsrand(QDateTime::currentMSecsSinceEpoch());
    sproutOne = qrand() % 100;
    sproutTwo = qrand() % 100;
    if (sproutOne < 25){
        if (SnakeOneDirection != eDirection::Down)
            SnakeOneDirection = eDirection::Up;
    }else if(sproutOne < 50){
        if (SnakeOneDirection != eDirection::Right)
            SnakeOneDirection = eDirection::Left;
    }else if(sproutOne < 75){
        if (SnakeOneDirection != eDirection::Up)
            SnakeOneDirection = eDirection::Down;
    }
    else if(sproutOne < 100){
        if (SnakeOneDirection != eDirection::Left)
            SnakeOneDirection = eDirection::Right;
    }

    if (sproutTwo < 25){
        if (SnakeTwoDirection != eDirection::Down)
            SnakeTwoDirection = eDirection::Up;
    }else if(sproutTwo < 50){
        if (SnakeTwoDirection != eDirection::Right)
            SnakeTwoDirection = eDirection::Left;
    }else if(sproutTwo < 75){
        if (SnakeTwoDirection != eDirection::Up)
            SnakeTwoDirection = eDirection::Down;
    }
    else if(sproutTwo < 100){
        if (SnakeTwoDirection != eDirection::Left)
            SnakeTwoDirection = eDirection::Right;
    }
}
