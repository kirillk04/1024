#include "Board.hpp"
#include <iostream>
#include <cstdlib> //rand, srand
#include <ctime>
#include <iomanip> //setw
#include <vector>
#include <string>
using namespace std;


void Board::allocateMemory() {
    panel = new int*[numRows];
    for (int i = 0; i < numRows; ++i) {
        panel[i] = new int[numCols];
    }
}

void Board::clear(){
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            panel[i][j] = 0; // Initialize each cell to be zero
        }
    }
}//set each cell of the panel to be zero



void Board::print() const{
    for (int j = 0; j < numCols; ++j) {
        cout << "+----";
    }
    cout << "+" << endl;

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            cout << "|";
            if (panel[i][j] != 0) {
                cout <<setw(4)<< panel[i][j];
            } else {
                cout << "    ";
            }
        }
        cout << "|" << endl;

        for (int j = 0; j < numCols; ++j) {
            cout << "+----";
        }
        cout << "+" << endl;
    }
}//print the panel


Board::Board(){
    numRows = 3;
    numCols = 3;
    allocateMemory();
    max = 0;
    target = 32;
} //construct a 3 x 3 panel

Board::Board(int m){
    if(m >=1){
        numRows = m;
        numCols = m;
    }
    else{
        numRows = 3;
        numCols = 3;
    }
    allocateMemory();
    max = 0;
    target = 32;

} //construct a m x m panel
    

Board::Board(int m, int n){
    if(m >= 1 && n >= 1){
        numRows = m;
        numCols = n;
    }
    else {
        numRows = 3;
        numCols = 3;
    }
    allocateMemory();
    max = 0;
    target = 32;
} //construct a m x n panel

Board::~Board(){
    for (int i = 0; i < numRows; ++i) {
        delete[] panel[i];
    }
    delete[] panel;
} //destructor,
        //when no longer need the current object,
        //release dynamic memory of this object.

int Board::getNumRows() const{
    return numRows;
}

int Board::getNumCols() const{
    return numCols;
}
int Board::getTarget() const{
    return target;
}
int Board::getMax() const{
    return max;
}


struct RowCol
{
 int row;
 int col;
};

void Board::selectRandomCell(int& row, int& col){
    vector<RowCol> zeros;
    RowCol cell;
    for (int i = 0; i < numRows; i++){
        for (int j = 0; j < numCols; j++){
            if(panel[i][j] == 0){
                cell.row = i;
                cell.col = j;
                zeros.push_back(cell);
            }
        }
    }
    if(zeros.size() > 0){
        int index = rand() % zeros.size();
        row = zeros[index].row;
        col = zeros[index].col;
        panel[row][col] = 1;
        print();
    }
    if(zeros.size() == 0 || zeros.size() == 1){
        if(noAdjacentSameValue()){
            if(max < target){
                cout<<"Game over. Try again."<<endl;
            }
            else {
                cout<<"Congratulations!"<<endl;
            }
            exit(0);
        }
        else{
            return;
        }
    }  
}


bool Board::noAdjacentSameValue() const{
    for (int i = 0; i < numRows; i++){
        for (int j = 0; j < numCols - 1; j++){
            if(panel[i][j] == panel[i][j+1]){
                return false;
            }
        }
    }
    for (int j = 0; j < numCols; j++){
        for (int i = 0; i < numRows - 1; i++){
            if(panel[i][j] == panel[i+1][j]){
                return false;
            }
        }
    }
    return max < target;
}
        //if there is no two adjacent cells
        //share same value, return true,
        //otherwise, return false.

void merge(vector<int>& result, int& max){
    int i = 0;
    int size = result.size();
    while(i < size){
        if(i+1 < size && result[i+1] == result[i]){
            result[i] *= 2;
            result[i+1] = 0;
            if(result[i] > max)
                max = result[i];
            i += 2;
        }
        else{
            i++;
        }
    }
}

void Board::pressUp(){
    for(int col = 0; col < numCols; col++){
        vector<int> nonZeros;

        for(int row = 0; row < numRows; row++){
            if(panel[row][col] != 0)
                nonZeros.push_back(panel[row][col]);
        }
        
        merge(nonZeros, max);
        int row = 0;
        for(int i = 0; i < nonZeros.size(); i++){
            if(nonZeros[i] != 0){
                panel[row][col] = nonZeros[i];
                row++;
            }
        }

        while(row < numRows){
            panel[row][col] = 0;
            row++;
        }
    }
    int row = 0;
    int col = 0;
    selectRandomCell(row,col);
}

void Board::pressDown() {
    for (int col = 0; col < numCols; col++) {
        vector<int> nonZeros;

        for (int row = numRows - 1; row >= 0; row--) {
            if (panel[row][col] != 0)
                nonZeros.push_back(panel[row][col]);
        }

        merge(nonZeros, max);
        int row = numRows - 1;
        for(int i = 0; i < nonZeros.size(); i++){
            if(nonZeros[i] != 0){
                panel[row][col] = nonZeros[i];
                row--;
            }
        }

        while(row >= 0){
            panel[row][col] = 0;
            row--;
        }
    }

    int row = 0;
    int col = 0;
    selectRandomCell(row, col);
}

void Board::pressLeft(){
    for (int row = 0; row < numRows; row++) {
        vector<int> nonZeros;

        for (int col = 0; col < numCols; col++) {
            if (panel[row][col] != 0)
                nonZeros.push_back(panel[row][col]);
        }

        merge(nonZeros, max);

        int col = 0;
        for (int i = 0; i < nonZeros.size(); i++) {
            if (nonZeros[i] != 0) {
                panel[row][col] = nonZeros[i];
                col++;
            }
        }

        while (col < numRows) {
            panel[row][col] = 0;
            col++;
        }
    }

    int row = 0;
    int col = 0;
    selectRandomCell(row, col);
}

void Board::pressRight() {
    for (int row = 0; row < numRows; row++) {
        vector<int> nonZeros;

        for (int col = numCols-1; col >= 0; col--) {
            if (panel[row][col] != 0)
                nonZeros.push_back(panel[row][col]);
        }

        merge(nonZeros, max);

        int col = numCols-1;
        for (int i = 0; i < nonZeros.size(); i++) {
            if (nonZeros[i] != 0) {
                panel[row][col] = nonZeros[i];
                col--;
            }
        }

        while (col >= 0) {
            panel[row][col] = 0;
            col--;
        }
    }

    int row = 0;
    int col = 0;
    selectRandomCell(row, col);
}

void Board::start(){
    int round = 1;
    srand(NULL);
    int row1, row2;
    int col1, col2;
    selectRandomCell(row1, col1);
    selectRandomCell(row2,col2);

    char ch;
    while(true){
        if(max >= target){
            cout<<"Congratulation!"<<endl;
            break;
        }

        ch = getchar();
        if(ch == 'S'){
            break;
        }
        if(ch == '\033'){
            getchar();
            switch(getchar()){
                case 'A':
                    cout<<"Round "<< setw(4) <<round<<": ";
                    cout<<"Press UP. "
                        <<"Goal: " << target<<endl;
                    pressUp();
                    round++;
                    break;
                case 'B':
                    cout << "Round " << setw(4) << round << ": ";
                    cout << "Press DOWN. "
                         << "Goal: " << target << endl;
                    pressDown();
                    round++;
                    break;
                case 'C':
                    cout << "Round " << setw(4) << round << ": ";
                    cout << "Press RIGHT. "
                         << "Goal: " << target << endl;
                    pressRight();
                    round++;
                    break;
                case 'D':
                    cout << "Round " << setw(4) << round << ": ";
                    cout << "Press LEFT. "
                         << "Goal: " << target << endl;
                    pressLeft();
                    round++;
                    break;
            }
        }
    }
}