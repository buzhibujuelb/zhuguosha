#include "zgs.h"

int player_number, MP;
char identity;

Game game;

void swap(int x,int y){
  int z=x;
  x=y;
  y=z;
}

void swapC(Card x,Card y){
  Card z=x;
  x=y;
  y=z;
}

extern char* FULL_NAME(char* s){
  if(s=="K")return "杀";
  if(s=="D")return "闪";
  if(s=="P")return "桃";
  if(s=="F")return "决斗";
  if(s=="Z")return "诸葛连弩";
  if(s=="N")return "南蛮入侵";
  if(s=="W")return "万箭齐发";
  if(s=="J")return "无懈可击";
  return s;
}

extern int dis(int x,int y){
  int ret1=1,ret2=1;
  if(x>y)swap(x,y);
  for(int i=x+1;i<y;i++)if(!is_dead(i))ret1++;
  for(int i=1;i<x;i++)if(!is_dead(i))ret2++;
  for(int i=y+1;i<=player_number;i++)if(!is_dead(i))ret2++;
  return ret1<ret2?ret1:ret2;
}

Card get_a_card(){
  Card ret;
  int rnd=rand()%80;
  if(rnd<29)ret.type="K";
  else if(rnd<29+14) ret.type="D";
  else if(rnd<29+14+8) ret.type="P";
  else if(rnd<29+14+8+10) ret.type="F";
  else if(rnd<29+14+8+20) ret.type="Z";
  else if(rnd<29+14+8+20+3) ret.type="N";
  else if(rnd<29+14+8+20+3+3) ret.type="W";
  else if(rnd<29+14+8+20+3+3+3) ret.type="J";
  return ret;
}

Pig player[MAX_PLAYER];

void use(int id,int cardid){
  for(int i=cardid;i<player[id].card_number;i++)
    player[id].card[i]=player[id].card[i+1];
  player[id].card_number--;
}

void show_pig(int id, bool hide){
  printf("Player %d(%s):\n",id,player[id].is_human?"Human":"AI");
  printf("Identity:%c Health:%d\n",player[id].id,player[id].health);
  printf("Has weapon:%d\n",player[id].has_z);
  if(!hide){
    printf("Cards:\n");
    for(int i=1;i<=player[id].card_number;i++)
      printf("(#%d)%s ",i,FULL_NAME(player[id].card[i].type));
  }else{
    printf("Cards:%d\n",player[id].card_number);
  }
  puts("");
}

void reset_game(){
  game.MP_number=1;
  game.ZP_number=0;
  game.FP_number=1;
  player_number=1;
  identity='R';
}

extern void game_init(){
  srand(time(0));
  reset_game();
}

extern void game_edit(){
  do{
    puts("-------------");
    printf("Now MP:%d ZP:%d FP:%d\n",game.MP_number,game.ZP_number,game.FP_number);
    printf("Total:%d Player(s)\n",game.MP_number+game.ZP_number+game.FP_number);
    puts("1.Add a player");
    puts("2.Del a player");
    puts("3.Change your identity");
    puts("4.Exit");
    int opt;
    scanf("%d",&opt);
    switch(opt){
      case 1:{
               puts("M -> zhu");
               puts("Z -> zhong");
               puts("F -> fan");
               char ch=getchar();
               while(ch!='M'&&ch!='Z'&&ch!='F')ch=getchar();
               switch(ch){
                 case 'M':{
                            if(game.MP_number<1){
                              game.MP_number++;
                            }else{
                              puts("Too many MP");
                            }
                            break;
                          }
                 case 'Z':{
                            game.ZP_number++;
                            break;
                          }
                 case 'F':{
                            game.FP_number++;
                            break;
                          }
               }
               printf("OK");
               break;
             }
      case 2:{
               puts("M -> zhu");
               puts("Z -> zhong");
               puts("F -> fan");
               char ch=getchar();
               while(ch!='M'&&ch!='Z'&&ch!='F')ch=getchar();
               switch(ch){
                 case 'M':{
                            if(game.MP_number>1){
                              game.MP_number--;
                            }else{
                              puts("Too few MP");
                            }
                            break;
                          }
                 case 'Z':{
                            if(game.ZP_number>0){
                              game.ZP_number--;
                            }else{
                              puts("Too few ZP");
                            }
                            break;
                          }
                 case 'F':{
                            if(game.FP_number>1){
                              game.FP_number--;
                            }else{
                              puts("Too few FP");
                            }
                            break;
                          }
               }

               break;
             }
      case 3:{
               printf("Now your are %c\n",identity);
               puts("R -> random");
               puts("M -> zhu");
               puts("Z -> zhong");
               puts("F -> fan");
               char ch=getchar();
               while(ch!='R'&&ch!='M'&&ch!='Z'&&ch!='F')ch=getchar();
               identity=ch;
               break;
             }
      case 4: return;
    }
  }while(1);
}

extern bool is_dead(int id){
  if(player[id].health>0)return 0;
  int ret=can_use(id,"P");
  if(ret){
    use(id,ret);
    return 0;
  }else return 1;
}

extern int game_end(){
  if(is_dead(MP))return -1;
  int flag=1;
  for(int i=1;i<=player_number;i++)
    if(player[i].id=='F'&&!is_dead(i)){
      flag=0;
      break;
    }
  return flag;
}


void show_pigs(){
  for(int i=1;i<=player_number;i++){
    show_pig(i,1);
  }
}

void human_play(int id){
  show_pig(id,0);
  int opt;
  if(player[id].card_number>0){
    do{
      scanf("%d",&opt);
    }while(opt<1||opt>player[id].card_number);
  }else{
    puts("You don't have any cards, so skip.");
    char ch=getchar();
    return;
  }
  Card card=player[id].card[opt];
  if(card.type=="K"||card.type=="F"){
    show_pigs();
    int r;
    do{
      printf("Choose who to %s",FULL_NAME(card.type));
      scanf("%d",&r);
    }while(r<1||r>player_number||is_dead(r)||(card.type=="K"&&!can_use_k(id,r)));
    if(card.type=="K")
      use_k(id,r);
    else use_f(id,r,opt);
  }
  use(id,opt);
}

extern void game_start(){
  CLEAR;

  puts("Game starting...");
  printf("Now MP:%d ZP:%d FP:%d\n",game.MP_number,game.ZP_number,game.FP_number);
  printf("Total:%d Player(s)\n",game.MP_number+game.ZP_number+game.FP_number);

  for(int i=1;i<=game.MP_number;i++)
    player[i].id='M';
  for(int i=1;i<=game.ZP_number;i++)
    player[i+game.MP_number].id='Z';
  for(int i=1;i<=game.FP_number;i++)
    player[i+game.MP_number+game.ZP_number].id='F';

  if(identity=='R'){
    int rnd=rand()%3;
    while((rnd==0&&game.MP_number==0)||(rnd==1&&game.ZP_number==0)||(rnd==2&&game.FP_number==0)){
      rnd=rand()%3;
    }
    if(rnd==0){
      identity='M';
      player[1].is_human=1;
    }
    else if(rnd==1){
      identity='Z';
      player[1+game.MP_number].is_human='H';
    }else{
      identity='F';
      player[1+game.MP_number+game.ZP_number].is_human='H';
    }
  }

  player_number=game.MP_number+game.ZP_number+game.FP_number;
  for(int i=1;i<=player_number;i++){
      player[i].card_number=0;
    player[i].health=4;
    for(int j=1;j<=4;j++){
      player[i].card_number++;
      player[i].card[player[i].card_number]=get_a_card();
    }
    
    show_pig(i,1);
  }

  //shuffle the order
  for(int i=1;i<=player_number;i++){
    int j=rand()%i+1;
    Pig temp=player[i];
    player[i]=player[j];
    player[j]=temp;
  }

  int cur_player=-1;
  for(int i=1;i<=player_number;i++)
    if(player[i].id=='M'){
      cur_player=i;
      MP=i;
      break;
    }

  while(!game_end()){
    puts("-----------------------------------------------");
    printf("Curplayer:%d\n",cur_player);
    if(player[cur_player].is_human){
      human_play(cur_player);
    }else
    switch(player[cur_player].id){
      case 'M':{
                 mp_play(cur_player);
                 break;
               }
      case 'Z':{
                 zp_play(cur_player);
                 break;
               }
      case 'F':{
                 fp_play(cur_player);
                 break;
               }
    }
    cur_player++;
    if(cur_player>player_number)cur_player=1;
  }
  printf("Game end. Winner is %s\n",game_end()==1?"MP & ZP":"FP");
  char ch=getchar();

}
