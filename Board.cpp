#include <iostream>
#include <string>
#include "Board.h"
#include "Player.h"
#include <string>
using namespace std;


/*-----------------------------------------------------------
 prints the dynamic board used for the game
-------------------------------------------------------------
*/
void Board::createDynamicBoard(int rows, int columns, char (&matrix)[13][16]){
  int letterCount = 0;
  
  for(int i = 0; i < rows; i++)
  {

    
     if(i == 0) 
     {

        cout << "     " << i + 1;

        for(int k = 0; k < columns - 1; k++)
        {

          if(k >= 9 )
          {
            
            cout << "  " << k + 2;
            
          } else 
            
          {
            
            cout << "   " << k + 2;
          }

        }

          cout << endl;
          cout << "    ---";
       
          for(int k = 0; k < columns - 1; k++) {

		        //print top portions of box (“---”)

            cout << " ---";
          
          }

          cout << endl;
          cout << char('A' + letterCount) << "  |";
          
		      for(int k = 0; k < columns; k++){

		        //print middle portion (“ letter  | matrix value in the middle |”
            cout << " " << matrix[i][k] << " |";
            
          }
            cout << " " << char('A' + letterCount); 
            cout << endl;
            cout << "    ---";
          
		      for(int k = 0; k < columns - 1; k++){

		        //print bottom portions of boxes (“---”)
             cout << " ---";
            
          }
                letterCount++;

                
      } else {
         cout << endl;
         cout << char('A' + letterCount) << "  |";
      
         for(int k = 0; k < columns; k++){

		        //print middle portion (“ letter  | matrix value in the middle |”
            cout << " " << matrix[i][k] << " |";
            
          }
       
         cout << " " << char('A' + letterCount);
            cout << endl;
            cout << "    ---";
          
		      for(int k = 0; k < columns - 1; k++){

		        //print bottom portions of boxes (“---”)
             cout << " ---";
            
          }
       

          letterCount++;
      } 

        
    }

  //ending
  
              cout << endl;
              cout << "     1";

        for(int k = 0; k < columns - 1; k++)
        {

          if(k >= 9 )
          {
            
            cout << "  " << k + 2;
            
          } else 
            
          {
            
            cout << "   " << k + 2;
          }

        }

  cout << endl;
  
}


/*-----------------------------------------------------------
member function that capitalizes the first letter of the string parameter
-------------------------------------------------------------
 */
void Board::capitalizeChar(string &piecePlacement){

 if(piecePlacement[0] == 'a')
 {
   piecePlacement[0] = 'A';
 } 
  
 if(piecePlacement[0] == 'b')
 {
   piecePlacement[0] = 'B';
 } 
  
 if(piecePlacement[0] == 'c')
 {
   piecePlacement[0] = 'C';
 } 
  
 if(piecePlacement[0] == 'd')
 {
   piecePlacement[0] = 'D';
 } 
  
 if(piecePlacement[0] == 'e')
 {
   piecePlacement[0] = 'E';
 }
  
 if(piecePlacement[0] == 'f')
 {
   piecePlacement[0] = 'F';
 }
  
if(piecePlacement[0] == 'g')
 {
   piecePlacement[0] = 'G';
 } 
  
if(piecePlacement[0] == 'h')
 {
   piecePlacement[0] = 'H';
 }
  
if(piecePlacement[0] == 'i')
 {
   piecePlacement[0] = 'I';
 } 
  
 if(piecePlacement[0] == 'j')
 {
   piecePlacement[0] = 'J';
 } 
  
 if(piecePlacement[0] == 'k')
 {
   piecePlacement[0] = 'K';
 }
  
 if(piecePlacement[0] == 'l')
 {
   piecePlacement[0] = 'L';
 } 
  
 if(piecePlacement[0] == 'm')
 {
   piecePlacement[0] = 'M';
 } 
  
}


/*-----------------------------------------------------------
member function which places the inputed piece onto the 
dynamic board 
-------------------------------------------------------------
 */
void Board::placePiece(char(&matrix)[13][16], string& placement, char symbol, int rowBound, int columnBound)
{
  
capitalizeChar(placement);
int rowPlacement = rowCharToInt(placement[0]);
  
int columnPlacement = 0;

  if (placement.size() == 2)
  {
    columnPlacement = stringToInt(placement.substr(1,1));
  } else {

    columnPlacement = stringToInt(placement.substr(1,2));

    
  }
  
     matrix[rowPlacement][columnPlacement - 1] = symbol;
  
     
  
}


/*-----------------------------------------------------------------------------
   converts the int input from the user to the matching character number                                                          on the board                                  
-------------------------------------------------------------------------------
*/

int Board::stringToInt(string columnPlacement)
{

    if(columnPlacement == "1"){
       return 1;
    }
    if(columnPlacement == "2"){
       return 2;
    }
    if(columnPlacement == "3"){
      return 3;
    }
    if(columnPlacement == "4"){
      return 4;
    }
    if(columnPlacement == "5"){
      return 5;
    }
    if(columnPlacement == "6"){
       return 6;
    }
    if(columnPlacement == "7"){
       return 7;
    }
    if(columnPlacement == "8"){
       return 8;
    }
    if(columnPlacement == "9"){
       return 9;
    }
    if(columnPlacement == "10"){
       return 10;
    }
    if(columnPlacement == "11"){
       return 11;
    }
    if(columnPlacement == "12"){
       return 12;
    }
    if(columnPlacement == "13"){
       return 13;
    }
    if(columnPlacement == "14"){
       return 14;
    }
    if(columnPlacement == "15"){
       return 15;
    }
    if(columnPlacement == "16"){
       return 16;
    }

  return '1';
}

/*-----------------------------------------------------------------------------
   This functions checks to see if every spot on the board has a piece(calls for a tie)                                
-------------------------------------------------------------------------------
*/
bool Board::isBoardFull(char matrix[13][16], int rows, int columns)
{
    
  bool isFull = true;

  for(int i = 0; i < rows; i++)
  {
    for (int k = 0; k < columns; k++)
    {
      if (matrix[i][k] == ' ')
      {
      isFull = false;
      }
    }
    
  }

  return isFull;

  
}

/*-----------------------------------------------------------
member function which converts the row letter into the letter's
matching row number
-------------------------------------------------------------
 */

int Board::rowCharToInt(char rowPlacement)
{

  if(int(rowPlacement) > 64 && int(rowPlacement) < 91)
  {
    for(int i = 0; i < 26; i++)
    {
      if('A' + i == rowPlacement)
      {
        return i;
      }
    }
  }


return -1;

  
}

/*-----------------------------------------------------------
member function for spacing check
-------------------------------------------------------------
 */
bool Board::spacesCheck(string piecePlacement)
{
  
for (int i = 0; i < piecePlacement.length(); i++)
{

  if (piecePlacement[i] == ' ')
  {
    return false;
  }

  
}

   return true;  
}
  
