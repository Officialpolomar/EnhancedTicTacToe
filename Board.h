#include <iostream>
#include <string>
#include "Player.h"
using namespace std;

#ifndef BOARD_H
#define BOARD_H


class Board {

private:
int stringToInt(string);
void capitalizeChar(string&);
int rowCharToInt(char);
bool spacesCheck(string);

public:

void createDynamicBoard(int, int, char(&)[13][16]); //

void placePiece(char(&)[13][16], string&, char, int, int); //

bool isBoardFull(char[13][16], int, int); //





};







#endif