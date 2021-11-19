#include "zgs.h"



extern struct Game game;

extern Pig player[MAX_PLAYER];

extern int player_number;

extern struct Game game;

int main(){
  game_init();
  do{
    CLEAR;
    puts("1. Start game");
    puts("2. Edit game");
    puts("3. Exit game");
    int opt;
    scanf("%d",&opt);
    switch(opt){
      case 1:{
               game_start();
               char ch=getchar();
               ch=getchar();
               break;
             }
      case 2:{
               game_edit();
               break;
             }
      case 3:exit(0);
    }
  }while(1);

  return 0;
}
