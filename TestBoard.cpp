#include <iostream>
#include "Board.hpp"
using namespace std;
int main()
{
 Board game(4, 4); //create a Board object with 4 rows and 4 columns.
 game.start();
 return 0;
}