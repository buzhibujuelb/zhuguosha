#include "zgs.h"

extern int player_number;
extern Pig player[MAX_PLAYER];

bool can_use_k(int playerid,int recipient){
  return playerid!=recipient && dis(playerid,recipient)<=1;
}

int can_use(int id,char* type){
  for(int i=1;i<=player[id].card_number;i++)
    if(player[id].card[i].type==type)
      return i;
  return 0;
}

void use_k(int playerid,int recipient){
}
