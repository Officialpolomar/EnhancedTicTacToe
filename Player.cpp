#include <iostream>
#include <string>
#include "Player.h"


/*-----------------------------------------------------------------
   displays the surrent statistics of player object when called.    |
   This includes the wins, loses, and draws.                        |                                       
-------------------------------------------------------------------
*/
void Player::displayStats()
{
    cout << getFirstName() + "'s updated statistics" << endl;
    cout << "Wins: " << getWins() << endl;
    cout << "Loses: " << getLoses() << endl;
    cout << "Draws: " << getDraws() << "\n" << endl;

    
}

