#ifndef CLS_FUNC_H
#define CLS_FUNC_H
#include <iostream>
#include <cstring>
#include <cstdlib> /* 亂數相關函數 */
#include <ctime>
#include <cmath>
#include <ctype.h>
#include <stdbool.h>
using namespace std;
//任何和class有關的function和定義
class Card {
public:
    int rank;
    typedef enum {spade, heart, diamond, club}Suit;
    int value; 
    Suit suit;//它的花色
};
class Player {
public:  
    string name;
    int bankroll;
    int bet;
    int card_index;
    Card cards[52];//抽到的卡牌
    //member_func
    virtual int strategy() = 0;
    Player();
    Player(string player,int roll);
    void p_card(int con);
    void p_bet();
    void store_card(Card p);
    int return_points();
    int return_bet();
    int return_bankroll();
    void p_bankroll();
};
class Human: public Player { 
public:
    //construct
    Human():Player(){
        card_index = 0;
    }
    Human(string player,int roll):Player(player,roll){
        card_index = 0;
    }
    //m_func
    int strategy();
    void set_all(int bet);
    void end_game(int wins);

};
class Computer: public Player { 
private:
    string trait;
    int win;
public:
    //construct
    Computer():Player(){
        Player::card_index = 0;
        win = 0;
    }
    Computer(string player,int roll,string personality):Player(player,roll){
        Player::card_index = 0;
        trait = personality;
        win = 0;
    }
    //my_func
    void set_all();
    int strategy();
    void end_game(int wins);
    void dealer_bankroll(int income);

};
void set_cards(Card (*cards));
void shuffle(Card (*cards));
void Delay(int time);
#endif