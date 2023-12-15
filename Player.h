
#include <string>
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

/*------------------------------------------------------------------------------
   The player class houses each player's data needed for tic-tac-toe game.     |
   The class also holds the getters and setters functions for all data         |
--------------------------------------------------------------------------------
*/

class Player {

private:
  string player_first_name;
  string player_last_name;
  int player_wins = 0;
  int player_losses = 0;
  int player_draws = 0;
  char playerSymbol;
  char WinOrLoss;

public:
  char getWinOrLoss() { return WinOrLoss; }

  char getSymbol() { return playerSymbol; }

  string getFirstName() { return player_first_name; }

  string getLastName() { return player_last_name; }

  int getWins() { return player_wins; }

  int getLoses() { return player_losses; }

  int getDraws() { return player_draws; }

  void setSymbol(char sym) { playerSymbol = sym; }

  void setFirstName(string firstName) { player_first_name = firstName; }

  void setLastName(string lastName) { player_last_name = lastName; }

  void increaseWins() { player_wins += 1; }

  void increaseLoses() { player_losses += 1; }

  void increaseDraws() { player_draws += 1; }

  void displayStats();

  void setWinOrLoss(char gameDeterminer) { WinOrLoss = gameDeterminer; }
};

#endif