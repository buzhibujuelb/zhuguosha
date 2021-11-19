#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#define MAX_PLAYER 10
#define MAX_CARD 100

#ifdef linux
#define CLEAR system("clear")
#else
#define CLEAR    system("cls")
#endif

#ifndef _COMMON
#define _COMMON

typedef struct{
  char* type;
  int number;
} Card;

typedef struct{
  char id;
  bool is_human;
  int health, card_number;
  bool has_z;//有诸葛连弩
  Card card[MAX_CARD];
} Pig;

typedef struct{
  int MP_number,ZP_number,FP_number;
} Game;

//game.c
int dis(int a,int b);
bool is_dead(int id);
void game_init();
void game_edit();
void game_start();
void show_pig(int id,bool hide);
void show_pigs();
void use(int id,int cardid);

void human_play(int playerid);

//base.c
void use_p(int playerid,int cardid);
bool can_use_k(int playerid,int recipient);
int can_use(int playerid,char* type);
void use_k(int playerid,int recipient);

//tip.c
void use_f(int playerid,int recipient,int cardid);
void use_n(int playerid,int cardid);
void use_w(int playerid,int cardid);
void use_j(int playerid,int cardid, int origin_p_id,int origin_c_id,bool is_against);


//act.c

bool can_xyq(int playerid,int recipient);
bool can_bdy(int playerid,int recipient);
bool is_zp(int playerid);
bool is_fp(int playerid);

//ai.c

void mp_play(int playerid);
void zp_play(int playerid);
void fp_play(int playerid);

#endif

