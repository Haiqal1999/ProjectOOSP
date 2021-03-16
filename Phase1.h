#include "Rule.h"
#include "Board.h"
#include "Game.h"
#include "Game_generate.h"
#include "Tile.h"

/*
 * For Generation of TriangularMinesweeper, HexagonalMinesweeper and SquareMinesweeper
 */
//Abstract Class
class MineSweeperFactory{
private:
    Game minesweeper;

protected:
    virtual Rule * buildRule() = 0;
    virtual Game_generate * buildGame_Generator() = 0;
    virtual Board * buildBoard() = 0;

public:
    virtual Game * buildMineSweeperGame()=0;

};

class SquareMineSweeper: public MineSweeperFactory{
    Board * buildBoard() override{}
    Rule * buildRule() override {
        return new easy_Rules();
    }
    Game_generate * buildGame_Generator() override{}
    Game * buildMineSweeperGame() override {
        Game * minesweeper = new Game("Easy SquareMinesweeper");
    }
};

class TriangularMineSweeper: public MineSweeperFactory{
    Board * buildBoard() override{}
    Rule * buildRule() override{
        return new medium_Rules();
    }
    Game_generate * buildGame_Generator() override{}
    Game * buildMineSweeperGame() override{
        Game * minesweeper = new Game("Medium TriangularMinesweeper");
    }

};

class HexagonalMineSweeper: public MineSweeperFactory{
    Board * buildBoard() override{}
    Rule * buildRule() {
        return hard_rules();
    }
    Game_generate * buildGame_Generator() override{}

    Game * buildMineSweeperGame() override{
        Game * minesweeper = new Game("Hard HexagonalMinesweeper");
    }
};

class Game{
protected:
    string modeOfGame;
    Board *board;
    Game_generate * generate;
    Rule * rule;
public:
    Game(string modeOfGame): modeOfGame(modeOfGame){}
    void setRules(Rule* rule){ this->rule = rule;}
    void setBoard(Board* board){this->board = board;}
    void setGeneration(Game_generate * generate){this->generate = generate;}
    void updateGame(char* input);
    void displayBoard();
};

//Abstract class
class Rule{
protected:
    bool Hint;
    bool Flag;
    int numHints;
public:
    Rule(bool Hint, bool Flag, int numHints): Hint(Hint), Flag(Flag), numHints(numHints){}
    bool get_Hint(){
        return Hint;
    }
    bool getFlag(){return Flag;}
    int getNumHints(){return numHints;}
};


class easy_Rules: public Rule{
public:
    easy_Rules(): Rule(true,true,5){
    }
};

class medium_Rules: public Rule{
public:
    medium_Rules(): Rule(true,true,3){
    }
};

class hard_rules: public Rule{
    hard_rules(): Rule(false,false,0){
    }
};

class Tile{
protected:
bool isFlagged;
bool isFlipped;
bool bomb;
int value;
public:
void virtual flip()=0;
void flag();
void unflag();
void plantBomb();
void displayTile();
};

class squareTile:public Tile{
protected:
squareTile* up;
squareTile* down;
squareTile* left;
squareTile* right;
public:
void flip();
};

class hexagonTile:public Tile{
protected:
hexagonTile* side1;
hexagonTile* side2;
hexagonTile* side3;
hexagonTile* side4;
hexagonTile* side5;
hexagonTile* side6;
public:
void flip();
};

class triangleTile:public Tile{
protected:
triangleTile* side1;
triangleTile* side2;
triangleTile* side3;
public:
void flip();
};

class Board{
protected:
    Tile** tiles;
public:
    void virtual flip()=0;
    void flag();
    void unflag();
    void plantBomb();
    void displayBoard();
};

class squareBoard:public Board{
public:
void flip();
};

class hexagonBoard:public Board{
public:
void flip();
};

class triangleBoard:public Board{
public:
void flip();
};

class Game_generate{
protected:
int seed;
Board* gameBoard;
void virtual setSeed()=0;
public:
    generateBaord();
}

class Guided: public Game_generate{
protected:
void setSeed();
public:
Guided(){
    setSeed();
}
};

class Random: public Game_generate{
protected:
void setSeed();
public:
Random(){
    setSeed();
}
};
