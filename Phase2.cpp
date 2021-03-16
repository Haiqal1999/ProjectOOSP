#include <iostream>

#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <string>

using namespace std;

class Tile{
public:
    virtual void flip()=0;
    virtual void flag()=0;
    virtual void unflag()=0;
    virtual void plantBomb()=0;
    virtual char displayTile()=0;
};

class squareTile:public Tile{
private:
    std::vector<squareTile*> neighbors;
public:
    bool isFlagged;
    bool isFlipped;
    bool bomb;
    int value;
    void flip();
    void flag();
    void unflag();
    void plantBomb();
    char displayTile();
    void setNeighbors(std::vector<squareTile*> neighbors);
    squareTile();
};

class triangleTile:public Tile{
private:
    std::vector<triangleTile*> neighbors;
public:
    bool isFlagged;
    bool isFlipped;
    bool bomb;
    int value;
    void flip();
    void flag();
    void unflag();
    void plantBomb();
    char displayTile();
    void setNeighbors(std::vector<triangleTile*> neighbors);
    triangleTile();
};

class hexagonTile:public Tile{
private:
    std::vector<hexagonTile*> neighbors;
public:
    bool isFlagged;
    bool isFlipped;
    bool bomb;
    int value;
    void flip();
    void flag();
    void unflag();
    void plantBomb();
    char displayTile();
    void setNeighbors(std::vector<hexagonTile*> neighbors);
    hexagonTile();
};

class Board{
public:
    virtual int getSize()=0;
    virtual void flip(int x, int y)=0;
    virtual void flag(int x, int y)=0;
    virtual void unflag(int x, int y)=0;
    virtual void plantBomb(int x, int y)=0;
    virtual int displayBoard()=0;
    virtual std::vector<int> getHint()=0;
};

class squareBoard:public Board{
protected:
    squareTile* tiles[20][20];
    int tsize;
public:
    int getSize();
    void flip(int x, int y);
    void flag(int x, int y);
    void unflag(int x, int y);
    void plantBomb(int x, int y);
    int displayBoard();
    std::vector<int> getHint();
    squareBoard(int tsize);
    ~squareBoard();
};

class triangleBoard:public Board{
protected:
    triangleTile* tiles[20][20];
    int tsize;
public:
    int getSize();
    void flip(int x, int y);
    void flag(int x, int y);
    void unflag(int x, int y);
    void plantBomb(int x, int y);
    int displayBoard();
    std::vector<int> getHint();
    triangleBoard(int tsize);
    ~triangleBoard();
};

class hexagonBoard:public Board{
protected:
    hexagonTile* tiles[20][20];
    int tsize;
public:
    int getSize();
    void flip(int x, int y);
    void flag(int x, int y);
    void unflag(int x, int y);
    void plantBomb(int x, int y);
    int displayBoard();
    std::vector<int> getHint();
    hexagonBoard(int tsize);
    ~hexagonBoard();
};

class Rule{
protected:
    bool Flag;
    int numHints;
    int bombs;
public:
    Rule(bool Flag, int numHints, int bombs): Flag(Flag), numHints(numHints), bombs(bombs){}
    virtual int useHint() = 0;
    bool getFlag(){return Flag;}
    int getBombs(){return bombs;}
};

class easy_Rules: public Rule{
public:
    int useHint(){
        numHints--;
        return numHints+1;
    }
    easy_Rules(bool Flag, int numH, int numB): Rule(true,5,6){}
};

class medium_Rules: public Rule{
public:
    virtual int useHint(){
        numHints--;
        return numHints+1;
    }
    medium_Rules(bool Flag, int numH, int numB): Rule(true,3,7){}
};

class hard_rules: public Rule{
public:
    virtual int useHint(){
        return numHints =0;
    }
    hard_rules(bool Flag, int numH, int numB): Rule(false,0,10){}
};

class Game_generate{
protected:
    int seed;
    Board* gameBoard;
    void virtual setSeed()=0;
public:
    Board* generate(Board* board, Rule* rule);
};

class Guided: public Game_generate{
protected:
    void setSeed();
};

class Random: public Game_generate{
protected:
    void setSeed();
};

class Game{
protected:
    Board *board;
    Game_generate * generate;
    Rule * rule;
public:
    Game(){};
    void setRules(Rule* rule);
    void setBoard(Board* board);
    void setGeneration(Game_generate * generate);
    void updateGame(string command, int x, int y);
    int displayBoard();
    void getHint();
    void initialize(){
    this->generate->generate(board,rule);
};
};

class MineSweeperFactory{
protected:
    virtual Rule * buildRule() = 0;
    virtual Game_generate * buildGame_Generator() = 0;
    virtual Board * buildBoard() = 0;
public:
    virtual Game * buildMineSweeperGame()=0;
};

//Main focus of project Easy gamemode for SquareMinesweeper
class SquareMineSweeper_Easy: public MineSweeperFactory{
public:
    Board * buildBoard(){
        int tsize;
        std::cout<<"Please enter a size for the game. 7 for a 7x7 grid, 10 for 10x10 grid and 13 for 13x13."<<std::endl;
        std::cin>>tsize;
        cout << "     Easy MineSweeper" << endl;
        return new squareBoard(tsize);
    };
    Rule * buildRule(){
        bool Flag = true;
        int numHints = 5;
        int numBombs = 4;
        return new easy_Rules(Flag, numHints,numBombs);
    };
    Game_generate * buildGame_Generator(){
        return new Guided;
    };
    Game * buildMineSweeperGame(){
        Game * minesweeper = new Game();
        minesweeper->setBoard(buildBoard());
        minesweeper->setRules(buildRule());
        minesweeper->setGeneration(buildGame_Generator());
        minesweeper->initialize();
        return minesweeper;
    };
};

class SquareMineSweeper_Medium: public MineSweeperFactory{
    Board * buildBoard(){
        int tsize;
        std::cout<<"Please enter a size for the game. 7 for a 7x7 grid, 10 for 10x10 grid and 13 for 13x13."<<std::endl;
        std::cin>>tsize;
        cout << "     Medium MineSweeper" << endl;
        return new squareBoard(tsize);
    };
    Rule * buildRule(){
        bool Flag;
        int numHints;
        int numBombs;
        return new medium_Rules(Flag, numHints,numBombs);
    };
    Game_generate * buildGame_Generator(){
        return new Random;
    };
    Game * buildMineSweeperGame(){
        Game * minesweeper = new Game();
        minesweeper->setBoard(buildBoard());
        minesweeper->setRules(buildRule());
        minesweeper->setGeneration(buildGame_Generator());
        minesweeper->initialize();
        return minesweeper;
    };
};

class SquareMineSweeper_Hard: public MineSweeperFactory{
    Board* buildBoard(){
        int tsize;
        std::cout<<"Please enter a size for the game. 7 for a 7x7 grid, 10 for 10x10 grid and 13 for 13x13."<<std::endl;
        std::cin>>tsize;
        cout << "     Hard MineSweeper" << endl;
        return new squareBoard(tsize);
    }
    Rule* buildRule(){
        bool Flag;
        int numHints;
        int numBombs;
        return new hard_rules(Flag, numHints, numBombs);
    }
    Game_generate* buildGame_Generator(){
        return new Random;
    }
    Game* buildMineSweeperGame(){
        Game* minesweeper = new Game();
        minesweeper->setRules(buildRule());
        minesweeper->setBoard(buildBoard());
        minesweeper->setGeneration(buildGame_Generator());
        minesweeper->initialize();
        return minesweeper;
    }
};

class TriangularMineSweeper_Easy: public MineSweeperFactory{
    Board * buildBoard(){
        int tsize;
        std::cout<<"Please enter a size for the game."<<std::endl;
        std::cin>>tsize;
        cout << "     Easy MineSweeper" << endl;
        return new triangleBoard(tsize);
    };
    Rule * buildRule(){
        bool Flag;
        int numHints;
        int numBombs;
        return new easy_Rules(Flag, numHints, numBombs);
    };
    Game_generate * buildGame_Generator(){
        return new Random;
    };
    Game * buildMineSweeperGame(){
        Game* minesweeper = new Game();
        minesweeper->setRules(buildRule());
        minesweeper->setBoard(buildBoard());
        minesweeper->setGeneration(buildGame_Generator());
        minesweeper->initialize();
        return minesweeper;
    };
};

class TriangularMineSweeper_Medium: public MineSweeperFactory{
    Board * buildBoard(){
        int tsize;
        std::cout<<"Please enter a size for the game."<<std::endl;
        std::cin>>tsize;
        cout << "     Medium MineSweeper" << endl;
        return new triangleBoard(tsize);
    };
    Rule * buildRule(){
        bool Flag;
        int numHints;
        int numBombs;
        return new medium_Rules(Flag, numHints, numBombs);
    };
    Game_generate * buildGame_Generator(){
        return new Random;
    };
    Game * buildMineSweeperGame(){
        Game* minesweeper = new Game();
        minesweeper->setRules(buildRule());
        minesweeper->setBoard(buildBoard());
        minesweeper->setGeneration(buildGame_Generator());
        minesweeper->initialize();
        return minesweeper;
    };
};

class TriangularMineSweeper_Hard: public MineSweeperFactory{
    Board * buildBoard(){
        int tsize;
        std::cout<<"Please enter a size for the game."<<std::endl;
        std::cin>>tsize;
        cout << "     Hard MineSweeper" << endl;
        return new triangleBoard(tsize);
    };
    Rule * buildRule(){
        bool Flag;
        int numHints;
        int numBombs;
        return new hard_rules(Flag, numHints, numBombs);
    };
    Game_generate * buildGame_Generator(){
        return new Random;
    };
    Game * buildMineSweeperGame(){
        Game* minesweeper = new Game();
        minesweeper->setRules(buildRule());
        minesweeper->setBoard(buildBoard());
        minesweeper->setGeneration(buildGame_Generator());
        minesweeper->initialize();
        return minesweeper;
    };
};



class HexagonalMineSweeper_easy: public MineSweeperFactory{
    Board * buildBoard(){
        int tsize;
        std::cout<<"Please enter a size for the game."<<std::endl;
        std::cin>>tsize;
        cout << "     Easy MineSweeper" << endl;
        return new hexagonBoard(tsize);
    };
    Rule * buildRule(){
        bool Flag;
        int numHints;
        int numBombs;
        return new easy_Rules(Flag, numHints, numBombs);
    };
    Game_generate * buildGame_Generator(){
        return new Random;
    };
    Game * buildMineSweeperGame(){
        Game* minesweeper = new Game();
        minesweeper->setRules(buildRule());
        minesweeper->setBoard(buildBoard());
        minesweeper->setGeneration(buildGame_Generator());
        minesweeper->initialize();
        return minesweeper;
    };
};

class HexagonalMineSweeper_medium: public MineSweeperFactory{
    Board * buildBoard(){
        int tsize;
        std::cout<<"Please enter a size for the game."<<std::endl;
        std::cin>>tsize;
        cout << "     Medium MineSweeper" << endl;
        return new hexagonBoard(tsize);
    };
    Rule * buildRule(){
        bool Flag;
        int numHints;
        int numBombs;
        return new medium_Rules(Flag, numHints, numBombs);
    };
    Game_generate * buildGame_Generator(){
        return new Random;
    };
    Game * buildMineSweeperGame(){
        Game* minesweeper = new Game();
        minesweeper->setRules(buildRule());
        minesweeper->setBoard(buildBoard());
        minesweeper->setGeneration(buildGame_Generator());
        minesweeper->initialize();
        return minesweeper;
    };
};

class HexagonalMineSweeper_hard: public MineSweeperFactory{
    Board * buildBoard(){
        int tsize;
        std::cout<<"Please enter a size for the game."<<std::endl;
        std::cin>>tsize;
        cout << "     Hard MineSweeper" << endl;
        return new hexagonBoard(tsize);
    };
    Rule * buildRule(){
        bool Flag;
        int numHints;
        int numBombs;
        return new hard_rules(Flag, numHints, numBombs);
    };
    Game_generate * buildGame_Generator(){
        return new Random;
    };
    Game * buildMineSweeperGame(){
        Game* minesweeper = new Game();
        minesweeper->setRules(buildRule());
        minesweeper->setBoard(buildBoard());
        minesweeper->setGeneration(buildGame_Generator());
        minesweeper->initialize();
        return minesweeper;
    };
};

void squareTile::flag(){
    isFlagged=true;
}

void squareTile::unflag(){
    isFlagged=false;
}

void squareTile::plantBomb(){
    bomb=true;
    for(auto neighbor:neighbors){
        neighbor->value++;
    }
}

char squareTile::displayTile(){
    if(isFlipped){
        if(bomb) return '*';
        if(isFlagged) return 'f';
        return value+48;
    }
    if(isFlagged) return 'f';
    return ' ';
}

squareTile::squareTile(){
    bomb=false;
    isFlipped=false;
    isFlagged=false;
    value=0;
}

void squareTile::flip(){
    isFlipped=true;
    //When a neighbor is empty of numbers and bombs we need to trigger a recursion to flip it's neighbors
    //When a neighbor has a number we flip it, but don't recurse
    //When a neighbor is missing or a bomb we do nothing
    for(auto neighbor: neighbors){
        if(neighbor && !neighbor->isFlipped && neighbor->value==0 && !neighbor->bomb) neighbor->flip();
        else if(neighbor && neighbor->value>0 && !neighbor->bomb) neighbor->isFlipped=true;
    }
}

void squareTile::setNeighbors(std::vector<squareTile*> neighbors){
    this->neighbors=neighbors;
};

void triangleTile::flag(){
    isFlagged=true;
}

void triangleTile::unflag(){
    isFlagged=false;
}

void triangleTile::plantBomb(){
    bomb=true;
    for(auto neighbor:neighbors){
        neighbor->value++;
    }
}

char triangleTile::displayTile(){
    if(isFlipped){
        if(bomb) return '*';
        if(isFlagged) return 'f';
        return value+48;
    }
    if(isFlagged) return 'f';
    return ' ';
}

triangleTile::triangleTile(){
    bomb=false;
    isFlipped=false;
    isFlagged=false;
    value=0;
}

void triangleTile::flip(){
    isFlipped=true;
    //When a neighbor is empty of numbers and bombs we need to trigger a recursion to flip it's neighbors
    //When a neighbor has a number we flip it, but don't recurse
    //When a neighbor is missing or a bomb we do nothing
    for(auto neighbor: neighbors){
        if(neighbor && !neighbor->isFlipped && neighbor->value==0 && !neighbor->bomb) neighbor->flip();
        else if(neighbor && neighbor->value>0 && !neighbor->bomb) neighbor->isFlipped=true;
    }
}

void triangleTile::setNeighbors(std::vector<triangleTile*> neighbors){
    this->neighbors=neighbors;
};

void hexagonTile::flag(){
    isFlagged=true;
}

void hexagonTile::unflag(){
    isFlagged=false;
}

void hexagonTile::plantBomb(){
    bomb=true;
    for(auto neighbor:neighbors){
        neighbor->value++;
    }
}

char hexagonTile::displayTile(){
    if(isFlipped){
        if(bomb) return '*';
        if(isFlagged) return 'f';
        return value+48;
    }
    if(isFlagged) return 'f';
    return ' ';
}

hexagonTile::hexagonTile(){
    bomb=false;
    isFlipped=false;
    isFlagged=false;
    value=0;
}

void hexagonTile::flip(){
    isFlipped=true;
    //When a neighbor is empty of numbers and bombs we need to trigger a recursion to flip it's neighbors
    //When a neighbor has a number we flip it, but don't recurse
    //When a neighbor is missing or a bomb we do nothing
    for(auto neighbor: neighbors){
        if(neighbor && !neighbor->isFlipped && neighbor->value==0 && !neighbor->bomb) neighbor->flip();
        else if(neighbor && neighbor->value>0 && !neighbor->bomb) neighbor->isFlipped=true;
    }
}

void hexagonTile::setNeighbors(std::vector<hexagonTile*> neighbors){
    this->neighbors=neighbors;
};

int squareBoard::getSize(){
    return tsize;
}

squareBoard::squareBoard(int tsize){
    this->tsize=tsize;
    for(int i=0;i<tsize;i++){
        for(int j=0;j<tsize;j++){
            tiles[i][j]=new squareTile();
        }
    }
    for(int i=0;i<tsize;i++){
        for(int j=0;j<tsize;j++){
            std::vector<squareTile*> neighbors;
            if(i>0) neighbors.push_back(tiles[i-1][j]);
            if(i>0&j<tsize-1) neighbors.push_back(tiles[i-1][j+1]);
            if(j<tsize-1) neighbors.push_back(tiles[i][j+1]);
            if(i<tsize-1&j<tsize-1) neighbors.push_back(tiles[i+1][j+1]);
            if(i<tsize-1) neighbors.push_back(tiles[i+1][j]);
            if(i<tsize-1&j>0) neighbors.push_back(tiles[i+1][j-1]);
            if(j>0) neighbors.push_back(tiles[i][j-1]);
            if(j>0&i>0) neighbors.push_back(tiles[i-1][j-1]);
            tiles[i][j]->setNeighbors(neighbors);
        }
    }
}

squareBoard::~squareBoard(){
    for(int i=0;i<tsize;i++){
        for(int j=0;j<tsize;j++){
            delete tiles[i][j];
        }
    }
}

int squareBoard::displayBoard(){
    int output=0;
    int unflipped=0;
    std::cout<<"  ";
    for(int i=0;i<tsize;i++){
        std::cout<<' '<<i;
        if(i<9) std::cout<<' ';
    }
    std::cout<<std::endl;
    for(int i=0; i<tsize;i++){
        std::cout<<i;
        if(i<10) std::cout<<' ';
        for(int j=0; j<tsize;j++){
            std::cout<<"["<<tiles[i][j]->displayTile()<<"]";
            if(tiles[i][j]->displayTile()=='*') output=1;
            if(tiles[i][j]->bomb==0&&tiles[i][j]->displayTile()==' ') unflipped++;
        }
        std::cout<<std::endl;
    }
    if(unflipped==0) output=2;
    return output;
}

std::vector<int> squareBoard::getHint(){
    std::vector<int> coords;
    for(int i=0; i< tsize;i++){
        for(int j=0; j<tsize;j++){
            if(tiles[i][j]->bomb){
                if(!tiles[i][j]->isFlagged) return {i,j};
            }
        }
    }
    return {-1,-1};
}

void squareBoard::flag(int x, int y){
    tiles[x][y]->flag();
}

void squareBoard::unflag(int x, int y){
    tiles[x][y]->unflag();
}

void squareBoard::plantBomb(int x, int y){
    tiles[x][y]->plantBomb();
}

void squareBoard::flip(int x, int y){
    tiles[x][y]->flip();
}

int triangleBoard::getSize(){
    return tsize;
}

triangleBoard::triangleBoard(int tsize){
    this->tsize=tsize;
    for(int i=0;i<tsize;i++){
        for(int j=0;j<tsize;j++){
            tiles[i][j]=new triangleTile();
        }
    }
    for(int i=0;i<tsize;i++){
        for(int j=0;j<tsize;j++){
            std::vector<triangleTile*> neighbors;
            if(i>0) neighbors.push_back(tiles[i-1][j]);
            if(i>0&j<tsize-1) neighbors.push_back(tiles[i-1][j+1]);
            if(j<tsize-1) neighbors.push_back(tiles[i][j+1]);
            if(i<tsize-1&j<tsize-1) neighbors.push_back(tiles[i+1][j+1]);
            if(i<tsize-1) neighbors.push_back(tiles[i+1][j]);
            if(i<tsize-1&j>0) neighbors.push_back(tiles[i+1][j-1]);
            if(j>0) neighbors.push_back(tiles[i][j-1]);
            if(j>0&i>0) neighbors.push_back(tiles[i-1][j-1]);
            tiles[i][j]->setNeighbors(neighbors);
        }
    }
}

triangleBoard::~triangleBoard(){
    for(int i=0;i<tsize;i++){
        for(int j=0;j<tsize;j++){
            delete tiles[i][j];
        }
    }
}

int triangleBoard::displayBoard(){
    int output=0;
    int unflipped=0;
    std::cout<<"    Minesweeper"<<std::endl;
    std::cout<<"  ";
    for(int i=0;i<tsize;i++){
        std::cout<<' '<<i<<' ';
    }
    std::cout<<std::endl;
    for(int i=0; i<tsize;i++){
        std::cout<<i<<' ';
        for(int j=0; j<tsize;j++){
            std::cout<<"["<<tiles[i][j]->displayTile()<<"]";
            if(tiles[i][j]->displayTile()=='*') output=1;
            if(tiles[i][j]->bomb==0&&tiles[i][j]->displayTile()==' ') unflipped++;
        }
        std::cout<<std::endl;
    }
    if(unflipped==0) output=2;
    return output;
}

std::vector<int> triangleBoard::getHint(){
    std::vector<int> coords;
    for(int i=0; i< tsize;i++){
        for(int j=0; j<tsize;j++){
            if(tiles[i][j]->bomb){
                if(!tiles[i][j]->isFlagged) return {i,j};
            }
        }
    }
    return {-1,-1};
}

void triangleBoard::flag(int x, int y){
    tiles[x][y]->flag();
}

void triangleBoard::unflag(int x, int y){
    tiles[x][y]->unflag();
}

void triangleBoard::plantBomb(int x, int y){
    tiles[x][y]->plantBomb();
}

void triangleBoard::flip(int x, int y){
    tiles[x][y]->flip();
}

int hexagonBoard::getSize(){
    return tsize;
}

hexagonBoard::hexagonBoard(int tsize){
    this->tsize=tsize;
    for(int i=0;i<tsize;i++){
        for(int j=0;j<tsize;j++){
            tiles[i][j]=new hexagonTile();
        }
    }
    for(int i=0;i<tsize;i++){
        for(int j=0;j<tsize;j++){
            std::vector<hexagonTile*> neighbors;
            if(i>0) neighbors.push_back(tiles[i-1][j]);
            if(i>0&j<tsize-1) neighbors.push_back(tiles[i-1][j+1]);
            if(j<tsize-1) neighbors.push_back(tiles[i][j+1]);
            if(i<tsize-1&j<tsize-1) neighbors.push_back(tiles[i+1][j+1]);
            if(i<tsize-1) neighbors.push_back(tiles[i+1][j]);
            if(i<tsize-1&j>0) neighbors.push_back(tiles[i+1][j-1]);
            if(j>0) neighbors.push_back(tiles[i][j-1]);
            if(j>0&i>0) neighbors.push_back(tiles[i-1][j-1]);
            tiles[i][j]->setNeighbors(neighbors);
        }
    }
}

hexagonBoard::~hexagonBoard(){
    for(int i=0;i<tsize;i++){
        for(int j=0;j<tsize;j++){
            delete tiles[i][j];
        }
    }
}

int hexagonBoard::displayBoard(){
    int output=0;
    int unflipped=0;
    std::cout<<"  ";
    for(int i=0;i<tsize;i++){
        std::cout<<' '<<i<<' ';
    }
    std::cout<<std::endl;
    for(int i=0; i<tsize;i++){
        std::cout<<i<<' ';
        for(int j=0; j<tsize;j++){
            std::cout<<"["<<tiles[i][j]->displayTile()<<"]";
            if(tiles[i][j]->displayTile()=='*') output=1;
            if(tiles[i][j]->bomb==0&&tiles[i][j]->displayTile()==' ') unflipped++;
        }
        std::cout<<std::endl;
    }
    if(unflipped==0) output=2;
    return output;
}

std::vector<int> hexagonBoard::getHint(){
    std::vector<int> coords;
    for(int i=0; i< tsize;i++){
        for(int j=0; j<tsize;j++){
            if(tiles[i][j]->bomb){
                if(!tiles[i][j]->isFlagged) return {i,j};
            }
        }
    }
    return {-1,-1};
}

void hexagonBoard::flag(int x, int y){
    tiles[x][y]->flag();
}

void hexagonBoard::unflag(int x, int y){
    tiles[x][y]->unflag();
}

void hexagonBoard::plantBomb(int x, int y){
    tiles[x][y]->plantBomb();
}

void hexagonBoard::flip(int x, int y){
    tiles[x][y]->flip();
}

Board* Game_generate::generate(Board* board, Rule* rule){
    setSeed();
    int x,y;
    int bombs=rule->getBombs();
    bombs=bombs*((board->getSize()*board->getSize())/(7*7));
    bool skip=0;
    std::vector<std::tuple<int,int>> used_coord;
    while(bombs){
        skip=0;
        x=std::rand()%board->getSize();
        y=std::rand()%board->getSize();
        for(auto coord:used_coord){
            if(coord==std::tuple<int,int>(x,y)) skip=1;
        }
        if(skip) continue;
        board->plantBomb(x,y);
        used_coord.push_back(std::tuple<int,int>(x,y));
        bombs--;
    }
    return board;
}

void Guided::setSeed(){
    std::srand(0);
}

void Random::setSeed(){
    std::srand(time(0));
}

void Game::setRules(Rule* rule){
    this->rule = rule;
}

void Game::setBoard(Board* board){
    this->board = board;
}

void Game::setGeneration(Game_generate * generate){
    this->generate = generate;
}

int Game::displayBoard(){
    return board->displayBoard();
}

void Game::getHint(){
    int hints=rule->useHint();
    if(hints<=0){
        cout<<"You are out of hints"<<std::endl;
        return;
    }
    std::vector<int> coords=board->getHint();
    if(coords[0]==-1&&coords[1]==-1){
        std::cout<<"You've flagged all bombs"<<endl;
        return;
    }
    std::cout<<"There is a bomb at ("<<coords[0]<<", "<<coords[1]<<")"<<endl;
    std::cout<<"You have "<<hints-1<<" hints left"<<endl;
}

void Game::updateGame(string command, int x, int y){
    if(command=="hint") this->getHint();
    if(command=="flip") board->flip(x,y);
    if(command=="flag") board->flag(x,y);
    if(command=="unflag") board->unflag(x,y);
}




int main(){
    //Instance variable
    int instruction;
    string command;
    int x,y;
    int gameState;

    // Declare MinesweeperFactory variable
    MineSweeperFactory* SimpleGame = new SquareMineSweeper_Easy;
    MineSweeperFactory* MediumGame = new SquareMineSweeper_Medium;
    MineSweeperFactory* HardGame = new SquareMineSweeper_Hard;
    /* Need several inputs
     * Most important: Flag, Unflag, flip signals
     *                  cin<< Checks for comparison
     */
    std::cout << "Press 0 to exit application. Or else any number from the list below to start game." << std::endl
              << "1. Easy Square MineSweeper" << endl
              << "2. Medium Square MineSweeper" << endl
              << "3. Hard Square Minesweeper " << endl;
    std::cin >> instruction;
    Game * g;
    if(instruction == 0){
        cout << " Exit game..." << endl;
        return 0;
    }else if (instruction == 1){
        g = SimpleGame->buildMineSweeperGame();
    }
    else if(instruction == 2){
        g = MediumGame->buildMineSweeperGame();
    }
    else if(instruction == 3){
        g = HardGame->buildMineSweeperGame();
    }
    while(1){
        gameState=g->displayBoard();
        if(gameState==1){
            std::cout<<"Game Over"<<endl;
            return 0;
        }
        if(gameState==2){
            std::cout<<"You Win!"<<endl;
            return 0;
        }
        //If gamemode is Hard
        if (instruction == 3){
            std::cout<<"Enter a command such as 'flip', 'flag' or 'unflag' to play."<<endl
                     <<"Be sure to include coordinates. Ex: flip 1 1. 'quit' to leave."<<endl;
        }else{
            //If gamemode is easy or medium
            std::cout<<"Enter a command such as 'flip', 'flag' or 'unflag' to play."<<endl
                     <<"Be sure to include coordinates. Ex: flip 1 1"<<endl
                     <<"Type in 'hint' to recieve the location of an unflagged bomb"<<endl
                     <<"or 'quit' to leave"<<endl;
        }
        std::cin>>command;
        if(command=="quit"){
            std::cout<<"Goodbye"<<endl;
            return 0;
        }else if (command=="hint")
        {
            x=0;
            y=0;
        }else{
            std::cin>>x>>y;
        }
        std::cout<<endl<<endl;
        g->updateGame(command, x, y);
    }
}



