#include<iostream>
#include<cmath>
using namespace std;

//3x3 Board as a 1D array
char board[9]={' ',' ',' ',' ',' ',' ',' ',' ',' '};

void DisplayBoard(){
  int len=sizeof(board)/sizeof(char);
  cout<<"_____________\n";
  for (int i = 0; i < 9; i += 3) {
        cout << "| " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << " |" << endl;
        cout<<"-------------"<<endl;
  }
}

bool checkWinner(char player){
  int winConditions[8][3]={
    {0,1,2},{3,4,5},{6,7,8}//horizontal
   ,{0,3,6},{1,4,7},{2,5,8}//vertical
   ,{0,4,8},{2,4,6}}; //diagonal
   for(auto &condition:winConditions){
    if(board[condition[0]]==player &&board[condition[1]]==player &&board[condition[2]]==player){
      return true;
    }
   }
   return false;
  };

bool checkFullBox(){
    for(char a:board){
      if(a==' '){
        return false;
      }
    }
    return true;
  };

int minimax(bool isMaximizing){
  if(checkWinner('X')){
    return -1;//if human win
  }
  else if (checkWinner('O')){
    return 1; //if AI Win
  }
  else if (checkFullBox()){
    return 0; //draw
  }

  if (isMaximizing){
    int bestScore= INT_MIN;
    for(int i=0;i<9;i++){
      if(board[i]==' '){
        board[i]='O';
        int score=minimax(false);
        board[i]=' ';
        bestScore=max(bestScore,score);
      }
    }
    return bestScore;
  }
  else{
    int bestScore=INT_MAX;
    for(int i=0;i<9;i++){
      if(board[i]==' '){
        board[i]='X';
        int score=minimax(true);
        board[i]=' ';
        bestScore=min(bestScore,score);
      }
    }
    return bestScore;
  }

}

void aiMove(){
  int bestScore=INT_MIN;
  int bestMove=-1;
  for(int i=0;i<9;i++){
    if(board[i]==' '){
      board[i]='O';
      int score=minimax(false);
      board[i]=' ';
      if(score>bestScore){
        bestMove=i;
        bestScore=score;
      }
    }
  }
  board[bestMove]='O';
}

int main(){ 
  while(true){
    system("cls");
    DisplayBoard();
    
    cout<<"Available Moves : ";
    for(int i=0;i<9;i++){
      if(board[i]==' '){
        cout<<i+1<<' ';
      }
    }

    cout<<endl<<"Choose your move: ";
    int move=-1;
    cin>>move;

    if(board[move-1]!=' '){
      cout<<endl<<"Wrong Move";
      continue;
    }
    board[move-1]='X';
    if(checkWinner('X')){
      DisplayBoard();
      cout<<endl<<"You win";
      break;
    }
    if(checkFullBox()){
      DisplayBoard();
      cout<<endl<<"Game Draw";
      break;
    }
    DisplayBoard();
    aiMove();
    if(checkWinner('O')){
      DisplayBoard();
      cout<<endl<<"AI win";
      break;
    }
    if(checkFullBox()){
      DisplayBoard();
      cout<<endl<<"Game Draw";
      break;
    }

  }
  return 0;
}
