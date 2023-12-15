#include <iostream>
#include "Player.h"
#include "Player.cpp"
#include "Board.h"
#include "Board.cpp"
#include <string>
using namespace std;


//function prototypes
void gameSequence(char[13][16], int, int, Player[], int);
int stringToIntMain(string);
void fillArray(char[13][16]);
void displayStats(Player[], int);
int isBiggestName(Player[], int);
bool winningConfig(char[13][16], int, int, Player[], int);
void validateName(string&);
void isNumberValid(string&,int,int);
bool spacesCheck(string);
int  nameSpaceCheck(string&);
bool lettersCheck(string);
int splitLocation(string);
void isPieceValid(string&, int, int, char[13][16]);
bool isInBound(string&,int,int);
bool isCorrectFormat(string);
bool isTaken(string, char[13][16]);
void capitalizeCharMain(string&);
int rowCharToIntMain(char);
string formatWord(string);
void nextPlayer(int&, int);
void eraseSpace(string&);



int main() {
//create temp variables for: amount of players, amount of rows, and columns needed for the game and board
 const int ROWS = 13;
 const int COLUMNS = 16;
 const int MAX_PLAYERS = 7;
  
  
 Board board; 
 char matrix[ROWS][COLUMNS];
 string tempRow;
 string tempColumn;
 string FirstName;
 string LastName;
 string tempNumPlayerHolder;
 string tempFullName;
 string green = "\033[1;32m";
 string reset = "\033[0m";
 string answer = "";
 string placement = " ";
 string introResponce; 
 int rows = 0;
 int columns = 0;
 int playerNum = 0;
 int gamesPlayed = 0;
 int split;
 int whoGoes = 2;  
 bool continueGame = true;


  
//Fill every space in 2d array with ' ';
fillArray(matrix);
  

// create an introduction for the game with instructions
cout << green << "Welcome! you are about to play tic-tac-toe on steriods\n" << reset << endl;
cout << "Rules:\n\n When inputting the full name of player(s) there must be no spaces except between the first and last name.\n\nAfter the player information has been entered, you will be instructed to enter the amount of rows and columns the board will have.\n\nThe max number of rows is 13 and the max number of columns is 16.The minimum number of rows and columns is 4.\n\nNext the board will be displayed and you will be prompted to enter the position(row letter,column number) on the board you would like to place your piece(e.g A1, d5, m16).\n\nTo win the game you must place three of your pieces in a row horizonally, vertically, or diagnolly.\n\nThe letters of the winning configuration will be capitalize and each players statistics(wins,losses,and draws) will be displayed.\n\nGood Luck! Are you ready to play(y/n)? ";
   getline(cin, introResponce);
  
while (introResponce != "No" &&
       introResponce != "no" && 
       introResponce != "n" && 
       introResponce != "N" && 
       introResponce != "Yes" && 
       introResponce != "yes" && 
       introResponce!= "y" && 
       introResponce != "Y") 
{

   cout << "\nInput enter is neither a yes or a no. Please enter yes or no to continue.\n";
   cin >> introResponce;
   cin.ignore();
    
}

if (introResponce == "No" || introResponce == "no" || 
        introResponce == "n" || introResponce == "N")
     {
        cout << "\nOk, have a good day";
        exit(0);    
     }
  
    cout << "\nHow many players will this game have(must be between 3 & 7 players)? " << endl;
    getline(cin,tempNumPlayerHolder);
    //check if the input is a number
    isNumberValid(tempNumPlayerHolder, 3, 7);
  
    //convert numbers from string to int
    playerNum = stringToIntMain(tempNumPlayerHolder); 
    // create an array of objects players(size is based on how many players their will be)
    Player player_list[MAX_PLAYERS];
    cout << endl;
      
 for (int i = 0; i < playerNum; i++)
 {
    cout << "Full name of PLAYER " << i + 1 << "--> "; 
    getline(cin, tempFullName);
   //validate input and get location of space
   eraseSpace(tempFullName);
   
   validateName(tempFullName);  
   split = splitLocation(tempFullName);
   FirstName = formatWord(tempFullName.substr(0, split));
   LastName  = formatWord(tempFullName.substr(split + 1));
   player_list[i].setFirstName(FirstName);
   player_list[i].setLastName(LastName); 
   player_list[i].setSymbol('a' + i);
   cout << endl; 
   cout << "PLAYER " << i+1 << " name: " << player_list[i].getFirstName() << " " << player_list[i].getLastName() << endl;
   cout << "will play with " << "'" << char('a' + i) << "'" << "\n" << endl;
 }
   
while (continueGame)
{
    cout << "\nHow many rows will the board have? " << endl;
    getline(cin,tempRow);
    isNumberValid(tempRow, 4, 13);

    rows = stringToIntMain(tempRow);

    cout << "How many columns will the board have? " << endl;
    getline(cin,tempColumn);

  
    isNumberValid(tempColumn, 4, 16);
  
    columns = stringToIntMain(tempColumn);

    //get index of player who goes first
    int whosGoingFirst = whoGoes;
  
    fillArray(matrix);
    cout << "\nHere is the board\n" << endl;
    board.createDynamicBoard(rows, columns, matrix);

    cout << "\n" <<player_list[whoGoes].getFirstName() 
         << " goes first(" << player_list[whoGoes].getSymbol() 
         << "). Please input coordinates for your piece. ";
  
    getline(cin,placement);
    cout << endl;
  
    isPieceValid(placement, rows, columns, matrix);
       
    board.placePiece(matrix, placement, player_list[whoGoes].getSymbol(), rows, columns);
    board.createDynamicBoard(rows, columns, matrix);
  
 

  
   //game sequence
    while (!winningConfig(matrix, rows, columns, player_list,playerNum) && !board.isBoardFull(matrix, rows, columns))
       {
          nextPlayer(whoGoes, playerNum);
          cout << "\n" << player_list[whoGoes].getFirstName() << "'s turn(" << player_list[whoGoes].getSymbol() << "). Please input the coordinates for your piece. \n";
          getline(cin,placement);
        
          isPieceValid(placement, rows, columns, matrix);
          board.placePiece(matrix, placement, player_list[whoGoes].getSymbol(), rows, columns);
          board.createDynamicBoard(rows, columns, matrix);   
        }
         //printing board after game sequence
         board.createDynamicBoard(rows, columns, matrix);
  
       if (board.isBoardFull(matrix, rows, columns))
       {
        cout << "\nThere has been of draw!" << endl;
        nextPlayer(whosGoingFirst, playerNum);
        whoGoes = whosGoingFirst;
        
          for (int i = 0; i < playerNum; i++)
          {
             player_list[i].increaseDraws();  
          }
         
        } 
        else 
        {
        nextPlayer(whoGoes, playerNum);
        }
    
       gamesPlayed++;
       cout << endl;
       //ending statement
       cout << "Number of Games Played: " << gamesPlayed << endl;

       displayStats(player_list,playerNum);

       string answer = "";
  
       cout << "Would you like to play again? ";
       cin >> answer;
       cin.ignore();

      while (answer != "No" && answer != "no" && answer != "n" && answer != "N" && answer != "Yes" && answer != "yes" && answer!= "y" && answer != "Y") 
      {

         cout << "Input enter is neither a yes or a no. Please enter yes or no if you want to continue.";
         cin >> answer;
         cin.ignore();
    
    }

     if (answer == "No" || answer == "no" || answer == "n" || answer == "N")
     {
         continueGame = false;
     } 
     else if (answer == "Yes" || answer == "yes" || answer == "y" || answer == "Y")
     {
         cout << green << "\nGame restarting" << reset << endl;
     }

  }

         cout << green << "\n\nOk, game has ended" << reset << endl;
 
 }




/*-----------------------------------------------------------
                                                             
This function checks to see if the user input was a decimal  
-------------------------------------------------------------
 */

int stringToIntMain(string playerNum){

   int num = 0;
   int l = playerNum.length();

   for(int i = 0; i < l; i++){

    num = num * 10 + (int(playerNum[i]) - 48 ); 
   }
    
  return num;
  
}

/*-----------------------------------------------------------
  The fillArray function fills the board with empty spaces
  to reset game.
-------------------------------------------------------------
 */
void fillArray(char newBoard[13][16] ){

  for (int i = 0; i < 13;i++) 
  {
    for (int k = 0; k < 16; k++)
    {
      newBoard[i][k] = ' ';
    }
    
  }

  
}

/*-----------------------------------------------------------
  isBiggestName function check to see which full name out of
  all the players is the longest(used for setting up stat display)
-------------------------------------------------------------
 */
int isBiggestName(Player player_list[], int length){

 int playerIndexWithBiggestName = 0;


  for (int i = 0; i < length - 1; i++)
  {

    if((player_list[playerIndexWithBiggestName].getFirstName().length() + player_list[playerIndexWithBiggestName].getLastName().length()) < player_list[i+1].getFirstName().length() + player_list[i+1].getLastName().length())
    {
      
      playerIndexWithBiggestName = i+1;
    }
    
  }

    return playerIndexWithBiggestName; 
  
}


/*-----------------------------------------------------------
  displayStats functions displays the stats of the players with 
  names aligned to the right side. 
-------------------------------------------------------------
 */
void displayStats(Player player_list[], int length){

  int counter = 0;
//get size of player’s full name and see which one is the biggest(what display board will be based on
 int biggestNameIndex = isBiggestName(player_list, length);

  int aligmentSetting = player_list[biggestNameIndex].getFirstName().length() + player_list[biggestNameIndex].getLastName().length() + 1;


//create for loop of spaces base off longest full name plus 4 spaces then add dashes
  for (int i = 0; i < aligmentSetting + 4; i++)
  {
      cout << " ";
  }
  for (int k = 0; k < 3; k++)
  {
    cout << " ------";
  }

  cout << endl;
    
  for (int l = 0; l < aligmentSetting + 3; l++)
  {
      cout << " ";
  }
  cout << " |  WIN | LOSS | DRAW |" << endl;


  
//create for loop of spaces base off longest full name plus 3 spaces then add vertical lines with WIN, LOSS, and DRAW

    while(counter < length){

      
             //first step
           for(int i = 0; i < aligmentSetting + 4; i++)
           {
             cout << " ";
           } 
          for(int k = 0; k < 3; k++)
           {
          cout << " ------";
           }
          cout << endl;
      

              //Create a for loop for the number of spaces.
             for(int j = 0; j < aligmentSetting - (player_list[counter].getFirstName().length() + player_list[counter].getLastName().length() - 2); j++)
           {

                  cout << " ";
      
          }
          cout << player_list[counter].getFirstName() <<  " " << player_list[counter].getLastName() << " ";

           cout << "|    " << player_list[counter].getWins() << " |    " << player_list[counter].getLoses() << " |   " <<                                                  player_list[counter].getDraws() << "  |" << endl;   

      
              counter++;

        }

      for (int i = 0; i < aligmentSetting + 4; i++)
           {
          cout << " ";
           } 

      for (int k = 0; k < 3; k++)
           {
           cout << " ------";
           }
          cout << endl << "\n";

   
}

/*-----------------------------------------------------------
 winningConfig function checks if the game has been won, capitalizes
 winning characters and displays the winner's names.
-------------------------------------------------------------
 */
bool winningConfig(char matrix[13][16], int rows, int columns, Player player_list[], int length){

int record = 0;
  
for (int i = 0; i < rows; i++)
{
  for (int k = 0; k < columns; k++)
  {

    //top right corner case
    if ((k == columns - 2 || k == columns - 1) && (i != rows - 2 && i != rows - 1))
    {
          //diagonal case(down and left)
        if (matrix[i][k] == matrix[i + 1][k - 1] && matrix[i][k] == matrix[i + 2][k  - 2] && matrix[i][k] != ' ')
        {
            record++;
           
          for (int l = 0; l < length; l++)
          {
            if (matrix[i][k] == player_list[l].getSymbol() && record == 1)
            {
              cout << endl << player_list[l].getFirstName() << " is the winner!!\n" ;
              player_list[l].increaseWins();
            } 
            else if (record == 1)   
            {
              player_list[l].increaseLoses();
            }
          }

           matrix[i][k] = toupper(matrix[i][k]);
           matrix[i + 1][k  - 1] = toupper(matrix[i + 1][k  - 1]);
           matrix[i + 2][k  - 2] = toupper(matrix[i + 2][k  - 2]);
          
        } 
        //vertical case(down)
        if (matrix[i][k] == matrix[i + 1][k] && matrix[i][k] == matrix[i + 2][k] && matrix[i][k] != ' ')
        {
          record++;
           
          for (int l = 0; l < length; l++)
          {
            if (matrix[i][k] == player_list[l].getSymbol() && record == 1)
            {
              cout << endl << player_list[l].getFirstName() << " is the winner!!\n";
              player_list[l].increaseWins();
            } 
            else if (record == 1)  
            {
              player_list[l].increaseLoses();               
            }
            
          }

          
           matrix[i][k] = toupper(matrix[i][k]);
           matrix[i + 1][k] = toupper(matrix[i + 1][k]);
           matrix[i + 2][k] = toupper(matrix[i + 2][k]);
            
        }
       
    } 
    //bottom left corner case 
    if ((k != columns - 2 && k != columns - 1) && (i == rows - 2 || i == rows - 1))
    {
          //diagonal check 
          if (matrix[i][k] == matrix[i - 1][k  + 1] && matrix[i][k] == matrix[i - 2][k  + 2] && matrix[i][k] != ' ')
        {
          record++;
            
            for (int l = 0; l < length; l++)
          {
            if (matrix[i][k] == player_list[l].getSymbol() && record == 1)
            {
              cout << endl << player_list[l].getFirstName() << " is the winner!!\n";
              player_list[l].increaseWins();
            } 
            else if (record == 1)
            {
              player_list[l].increaseLoses(); 
            }
          }

             matrix[i][k] = toupper(matrix[i][k]);
             matrix[i - 1][k + 1] = toupper(matrix[i - 1][k + 1]);
             matrix[i - 2][k + 2] = toupper(matrix[i - 2][k + 2]);
          
            
          
        } 
        //horizonal check
        if(matrix[i][k] == matrix[i][k + 1] && matrix[i][k] == matrix[i][k + 2] && matrix[i][k] != ' ')
        {
          record++;
           
          for (int l = 0; l < length; l++)
          {
            if (matrix[i][k] == player_list[l].getSymbol() && record == 1)
            {
              cout << endl << player_list[l].getFirstName() << " is the winner!!\n";
              player_list[l].increaseWins();
            } 
            else if (record == 1)  
            {
              player_list[l].increaseLoses();
            }
            
          }
 
           matrix[i][k] = toupper(matrix[i][k]);
           matrix[i][k  + 1] = toupper(matrix[i][k  + 1]);
           matrix[i][k  + 2] = toupper(matrix[i][k  + 2]);
    
        }
      

      //bottom right case
     } 
      if ((k == columns - 2 || k == columns - 1) && (i == rows - 2 || i == rows - 1))
     {
          //diagonal check 
          if (matrix[i][k] == matrix[i - 1][k - 1] && matrix[i][k ] == matrix[i - 2][k - 2] && matrix[i][k] != ' ')
        {
          record++;
          
          for (int l = 0; l < length; l++)
          {
            if(matrix[i][k] == player_list[l].getSymbol() && record == 1)
            {
              cout << endl << player_list[l].getFirstName() << " is the winner!!\n";
              player_list[l].increaseWins();
            } 
            else if(record == 1)
            {
              player_list[l].increaseLoses();
            }
          }

          matrix[i][k] = toupper(matrix[i][k]);
          matrix[i - 1][k - 1] = toupper(matrix[i - 1][k - 1]);
          matrix[i - 2][k - 2] = toupper(matrix[i - 2][k - 2]);
          
          
        } 
        //horizonal check
        if(matrix[i][k] == matrix[i][k - 1] && matrix[i][k] == matrix[i][k - 2] && matrix[i][k] != ' ')
        {
          record++;
          matrix[i][k] = toupper(matrix[i][k]);
          matrix[i][k - 1] = toupper(matrix[i][k - 1]);
          matrix[i][k - 2] = toupper(matrix[i][k - 2]);
          
          for (int l = 0; l < length; l++)
          {
            if (matrix[i][k] == player_list[l].getSymbol() && record == 1)
            {
              cout << endl << player_list[l].getFirstName() << " is the winner!!\n";
              player_list[l].increaseWins();
            } 
            else if(record == 1)
            {
              player_list[l].increaseLoses();              
            }
          }
          
        }
 
     }

      // everything else check
          //horizontal
        if(matrix[i][k] == matrix[i][k + 1] && matrix[i][k] == matrix[i][k + 2] && matrix[i][k] != ' '){
          record++;
           
         for (int l = 0; l < length; l++)
          {
            if (matrix[i][k] == player_list[l].getSymbol() && record == 1)
            {
              cout << endl << player_list[l].getFirstName() << " is the winner!!\n";
              player_list[l].increaseWins();
            } 
            else if(record == 1)
            {
              player_list[l].increaseLoses();              
            }
          }

          matrix[i][k] = toupper(matrix[i][k]);
          matrix[i][k + 1] = toupper(matrix[i][k + 1]);
          matrix[i][k + 2] = toupper(matrix[i][k + 2]);
          
        
        } 
          // diagonal 
        if(matrix[i][k] == matrix[i + 1][k + 1] && matrix[i][k] == matrix[i + 2][k + 2] && matrix[i][k] != ' ') 
        {
          record++;
            
           for(int l = 0; l < length; l++)
          {
            if(matrix[i][k] == player_list[l].getSymbol() && record == 1)
            {
              cout << endl << player_list[l].getFirstName() << " is the winner!!\n";
              player_list[l].increaseWins();
            } 
            else if (record == 1)
            {
              player_list[l].increaseLoses();            
            }
            
          }

          matrix[i][k] = toupper(matrix[i][k]);
          matrix[i + 1][k + 1] = toupper(matrix[i + 1][k + 1]);
          matrix[i + 2][k + 2] = toupper(matrix[i + 2][k + 2]);
          


          
        }
          //vertical(down)
        if (matrix[i][k] == matrix[i + 1][k] && matrix[i][k] == matrix[i + 2][k] && matrix[i][k] != ' ')
        {

           record++;
             
           for (int l = 0; l < length; l++)
          {
            if (matrix[i][k] == player_list[l].getSymbol() && record == 1){
              cout << endl << player_list[l].getFirstName() << " is the winner!!\n";
              player_list[l].increaseWins();
            } 
            else if (record == 1)
            {
              player_list[l].increaseLoses();              
            }
          }

          matrix[i][k] = toupper(matrix[i][k]);
          matrix[i + 1][k] = toupper(matrix[i + 1][k]);
          matrix[i + 2][k] = toupper(matrix[i + 2][k]);
          
        }

  }
}    
           cout << endl;
  
           if (record >= 1)
           {
              return true;
           } else 
             
           {
              return false;
           }
     
       
  }

/*-----------------------------------------------------------
 The validateName function is the logic behind the input
 validation of players' name.
-------------------------------------------------------------
 */
void validateName(string& playerName)
{
    while (nameSpaceCheck(playerName) != 1 || !lettersCheck(playerName))
    {
      
      if (nameSpaceCheck(playerName) != 1 && !lettersCheck(playerName))
      {
        cout << "\n- Full name must only have ONE space separating first and last name" << endl;
        cout << "- Full name must also contain only letters " << endl;
        cout << "\nPlease input again --> "; 
        getline(cin, playerName);
        continue; 
      }

      if (nameSpaceCheck(playerName) != 1 || lettersCheck(playerName))
      {
         cout << "\n- Letters in full name: VALID " << endl;
         cout << "- Must only have ONE space separating first and last name" << endl;
         cout << "\nPlease input again --> "; 
         getline(cin, playerName);
         continue;
      }

      if (nameSpaceCheck(playerName) == 1 || !lettersCheck(playerName))
      {
        cout << "\n- Amount of spaces: VALID " << endl;
        cout << "- All characters in name must be of the alphabet" << endl;
        cout << "\nPlease input again --> "; 
        getline(cin, playerName);
        continue;
      }
        
    }
}

/*-----------------------------------------------------------
 The nameSpaceCheck function checks the number of spaces where they are located in 
 the full name's string.
-------------------------------------------------------------
 */
int nameSpaceCheck(string& playerName){
 int i = 1;
 int spaceCounter = 0;
 eraseSpace(playerName);
  //if space at beginning of string return false;
  if (playerName[0] == ' ')
  {
    return -1;
  }
  // check amount of spaces in string
   for (int i = 0; i < playerName.length(); i++)
   {

     if (playerName[i] == ' ')
     {
       spaceCounter++;
     }
     
   }
   
  /*
    while(playerName[i] == ' '){
      i++;
    }
    spaceCounter++;
  */
  
  return spaceCounter;
}

/*-----------------------------------------------------------
 The lettersCheck function checks if the string contains only letters.
 If it does, return true. If not, it returns false.
-------------------------------------------------------------
 */
bool lettersCheck(string playerName)
{
   
    for (int i = 0; i < playerName.length(); i++)
   {

       if (!(int(playerName[i]) > 64 && int(playerName[i]) < 91) && !(int(playerName[i]) > 96 && int(playerName[i]) < 123) &&int(playerName[i]) != 32)
     {
      return false;     
     } 
  
   }

  return true; 

  
}

/*-----------------------------------------------------------
 The splitLocation functions return the exact index of where
 the space. This is used in order for the first and last name 
 to be seperated. 
-------------------------------------------------------------
 */
int splitLocation(string playerName){
  
   for (int i = 0; i < playerName.length(); i++)
   {

     if (playerName[i] == ' ')
     {
       return i; 
     }
     
   }
  return -1;
  
}

/*-----------------------------------------------------------
 The formatWord function formats the word to where
 the first letter is capitalized and the rest are lowercase.
-------------------------------------------------------------
 */
string formatWord(string playerName){

  //capitalize first letter if lower case
  if (int(playerName[0]) >= 97 && int(playerName[0]) <= 122)
  { 
    playerName[0] = char(int(playerName[0]) - 32);
  }

  
  for (int i = 1; i < playerName.length(); i++)
  {
   // convert to lower case if letter is capitalized 
    if (int(playerName[i]) >= 65 && int(playerName[i]) <= 90)
     {
      playerName[i] = char(int(playerName[i]) + 32);
     }
   
  }

  return playerName;

}


/*-----------------------------------------------------------
 Checks if there are spaces in the string and returns false
 if that is the case.
-------------------------------------------------------------
 */
bool spacesCheck(string playerName){

  for (int i = 0; i < playerName.length(); i++)
  {
    if(playerName[i] == ' ')
    {
    return false;
    }
  
  }

  return true;
}

/*-----------------------------------------------------------
The input validation for whenever a number is needed to be typed
 in.
-------------------------------------------------------------
 */
void isNumberValid(string& size, int lowerBound, int upperBound)
{
    while ((stringToIntMain(size) < lowerBound || stringToIntMain(size) > upperBound) || (!spacesCheck(size)) || size.find('.') != -1 )
  {
    if (size.find('.') != -1)
    {

      cout << "\nInput cannot be a decimal, try again. " << endl;
      getline(cin, size);
      continue;
    }
    
    if (!spacesCheck(size))
    {
      cout << "\nInput cannot have a space. Try again. " << endl;
      getline(cin, size);
      continue;
    }


    if (stringToIntMain(size) < lowerBound || stringToIntMain(size) > upperBound)
    {
      cout << "\nThe input was not a number between " << lowerBound << " and " << upperBound << " try again." << endl;
      getline(cin, size);
      continue;
    }

  }

  
}
/*-----------------------------------------------------------
 The input validation for the pieces on the board and 
 checks if piece input is already taken or out of bounds.
  
-------------------------------------------------------------
 */
void isPieceValid (string &pieceCoord, int rowBound, int columnBound, char matrix[13][16]){

  
  while (!isCorrectFormat(pieceCoord) || !isInBound(pieceCoord,rowBound, columnBound) || !isTaken(pieceCoord, matrix)) 
  {
   cout << "\nplease try again.";
   getline(cin, pieceCoord);
   cout << endl;
  }
  
}

/*-----------------------------------------------------------
 Capaitizes the first characters in a string  
-------------------------------------------------------------
 */
void capitalizeCharMain(string &pieceCoord){

  if (int(pieceCoord[0]) >= 97 && int(pieceCoord[0]) <= 122)
    {
    pieceCoord[0] = char(int(pieceCoord[0]) - 32);
    }  
}
/*-----------------------------------------------------------
 Converts the row letter to its coorasponding row number
-------------------------------------------------------------
 */
int rowCharToIntMain(char rowletter){

if(int(rowletter) > 64 && int(rowletter) < 91)
  {
    for(int i = 0; i < 26; i++)
    {
      if('A' + i == rowletter)
      {
        return i;
      }
    }
  }


return -1;

  
}

/*-----------------------------------------------------------
checks if input is a to a place on board that is already taken.
returns false if place is taken
-------------------------------------------------------------
 */
bool isTaken(string pieceCoord, char matrix[13][16]){

capitalizeCharMain(pieceCoord);
  int rowPlacement = rowCharToIntMain(pieceCoord[0]);
  
int columnPlacement = 0;

  if (pieceCoord.size() == 2)
  {
    columnPlacement = stringToIntMain(pieceCoord.substr(1,1));
  } 
  else 
  {
    columnPlacement = stringToIntMain(pieceCoord.substr(1,2));
  }

  if(matrix[rowPlacement][columnPlacement - 1] == ' '){
    return true;
  }
  
  cout << "\n- This piece of the board is already taken";
   return false;
   
}

/*-----------------------------------------------------------
checks if input is a to a place on board that is 
out of bounds.
-------------------------------------------------------------
 */
bool isInBound(string& pieceCoord, int rowBound, int columnBound){
  
  capitalizeCharMain(pieceCoord);
  int rowPlacement = rowCharToIntMain(pieceCoord[0]);
  
int columnPlacement = 0;

  if (pieceCoord.size() == 2)
  {
    columnPlacement = stringToIntMain(pieceCoord.substr(1,1));
  } 
  else 
  {
    columnPlacement = stringToIntMain(pieceCoord.substr(1,2));
  }
  
  if(rowPlacement + 1 > rowBound || columnPlacement > columnBound){
    cout << "\n- Input is out of bounds of current board" << endl;
    return false;
  }

  return true;
  
}

/*-----------------------------------------------------------
checks to see if input for a piece coordinate is a valid
-------------------------------------------------------------
 */

bool isCorrectFormat(string piecePlacement){

  if (piecePlacement.length() < 2 || piecePlacement.length() > 3)
  {
	  cout << "\n- Must be between 2 and 3 characters." << endl;
  return false;
  }

 if (!spacesCheck(piecePlacement))
 {
   cout << "\n- Cannot be space in input.";
  return false; 
 }

  if (!(int(piecePlacement[0]) > 64 && int(piecePlacement[0]) < 91) && !(int(piecePlacement[0]) > 96 && int(piecePlacement[0]) < 123) && int(piecePlacement[0]) != 32)
  {
    cout << "\n- First character must be a letter." << endl;
    return false;
  }


  if (!(int(piecePlacement[1]) >= 49 && int(piecePlacement[1]) <= 57))
  {
    cout << "\n- Second character must be a digits 1-9" << endl;
   return false;  
  }

 if (piecePlacement.length() == 3 && !(int(piecePlacement[2]) >= 48 && int(piecePlacement[2]) <= 57))
 {
   cout << "\n- Third character must be a digit 1-9" << endl;
   return false;  
 }
   return true;  
 }

/*-----------------------------------------------------------
  function that maintains the round robin system of which 
  player's turn it is 
-------------------------------------------------------------
 */
void nextPlayer(int& currentPlayer, int numPlayers){
  
 if (currentPlayer >= numPlayers - 1)
  {
    currentPlayer = 0;
  } 
  else 
  {
  currentPlayer++;
  }

}

void eraseSpace(string &polynomialInput)
{
    int spaceCounter = 0;

  for (int i = 0; i < polynomialInput.length(); i++)
  {
    while (polynomialInput[i] == ' ' && polynomialInput[i+1] == ' ')
    {
      polynomialInput.erase(i, 1);
    }

  }

}




