#include "cls_func.h"

Player::Player(){//default
    name = "NULL";
    bet = 1;
    bankroll = 100;
}
Player::Player(string player,int roll){ //有傳參數的constructor
    name = player;
    bankroll = roll; 
}
void set_cards(Card (*cards)){
    for(int i=0;i<4;i++){
        for(int j=0;j<13;j++){
            int p = j + 13*i;
            switch (i)
            {
            case 0:
                cards[p].suit = Card::spade;
                break;
            case 1:
                cards[p].suit = Card::heart;
                break;
            case 2:
                cards[p].suit = Card::diamond;
                break;
            case 3:
                cards[p].suit = Card::club;
                break;
            default:
                break;
            }
            cards[p].rank = j + 1;
            if(j >= 10){
                cards[p].value = 10;
            }
            else{
                cards[p].value = cards[p].rank;
            }
        }
    }
}
void shuffle(Card (*cards)){//重新洗牌
    Card deck[52];
    set_cards(deck);
    //總共五round
    for(int s=0;s<10;s++){
        int increase = 6;//每經過一round會加2
        // 範圍 
        int min = 7;
        int max = 10;
        int normal_num = 51;
        int ran_num;
        int last_round = 0;//計算上次切到的地方的是多少
        //其中一round
        for(int i=0;i<5;i++){
            ran_num = rand() % (max - min + 1) + min;//min~max
            for(int j = ran_num - 1;j >= last_round;j--){
                cards[normal_num] = deck[j];
                normal_num --;
            }
            last_round = ran_num;
            min += increase;
            max += increase;
            increase += 2;
        }
        //最後的牌
        for(int j = 51 ;j >= last_round;j--){
            cards[normal_num] = deck[j];
            normal_num --;
        }
        //把deck複製成cards下次再洗一次
        for(int i=0;i<4;i++){
            for(int j=0;j<13;j++){
                int p = j + 13*i;
                deck[p] = cards[p];
            }
        }
    }
}
void Player::p_card(int con){ // 印卡
    int i;
    cout <<"["<< name <<"]" << "現在的手牌擁有: ";
    if(con == 0){
        i = 1;
        cout << "[??]";
    }
    else{
        i = 0;
    }
    for(;i<card_index;i++){
        cout <<"[" <<cards[i].rank;
        switch (cards[i].suit)
        {
        case 0:
            cout << "S]";
            break;
        case 1:
            cout << "H]";
            break;
        case 2:
            cout << "D]";
            break;
        case 3:
            cout << "C]";
            break;
        default:
            break;
        }
    }
    if(con != 0){//要印現在的點數
        cout << "(" ;
        int points = return_points();
        cout << points;
        cout << "點)";
    }
    cout << endl;
}
void Player::p_bet(){
    cout << bet <<endl;
}
void Player::store_card(Card p){
    cards[card_index].rank = p.rank;
    cards[card_index].suit = p.suit;
    cards[card_index].value = p.value;
    card_index++;
}
int Player::return_points(){
    int points = 0;
    //計算點數(最大值且不會爆開去計算)
    int one_show = 0;//計算1 rank出現了幾次
    for(int i=0;i<card_index;i++){
        if(cards[i].rank!=1){
            points += cards[i].value;//不是一的
        }
        else{
            one_show ++;
        }
    }
    int max = points;;
    if(one_show >= 1){
        //0個十
        max = points + one_show;
        //一個十
        if((points + 10 + one_show)<=21){
            max = points + 10 + one_show;
        }
    }
    return max;
}
int Player::return_bet(){
    return bet;
}
void Player::p_bankroll(){
    cout <<"["<< name << "] "<<bankroll<<endl;
}
int Player::return_bankroll(){
    return bankroll;
}


int Human::strategy(){
    cout << "我有加虛擬函數!" << endl;
    return 0;
}
void Human::set_all(int bet){
    Player::bet = bet;
    Player::card_index = 0;
}
void Human::end_game(int wins){
    if(wins){
        cout << "哇喔! 玩家[" << Player::name <<"] 贏了"<<Player::bet<<endl;
        Player::bankroll += Player::bet;
    }
    else{
        cout << "可惜! 玩家[" << Player::name <<"] 輸了"<<Player::bet<<endl;
        Player::bankroll -= Player::bet;
    }
}

void Computer::set_all(){
    if(trait == "Meek"){
        int times_two = 2;//
        for(int i=0;i<(win/3);i++){
            times_two *= 2;
        }
        Player::bet = times_two;
    }
    else if(trait == "Random"){
        int min = 1;
        int max = Player::bankroll/2;
        Player::bet = rand() % (max - min + 1) + min;//min~max
    }
    Player::card_index = 0;
    win = 0;
}
int Computer::strategy(){
    if(trait == "Dealer"){
        if((return_points())<=16){
            return 1;
        }
    }
    else if(trait == "Meak"){
        int clubs = 0;
        for(int i=0;i<card_index;i++){
            if(cards[i].suit == Card::club){
                clubs ++;
            }
        }
        if(clubs == 7){
            return 1;
        }
        int points = return_points();
        if((points%2) == 0){
            return 1;
        }
    }
    else if(trait == "Random"){
        int points = return_points();
        int max = 10;
        int min = 1;
        int ran_num = rand() % (max - min + 1) + min;//min~max
        if(points < 10){
            return 1;
        }
        else if(points < 13){
            if(ran_num <= 8){
                return 1;
            }
        }
        else if(points < 16){
            if(ran_num <= 7){
                return 1;
            }
        }
        else if(points < 19){
            if(ran_num <= 5){
                return 1;
            }
        }
   }

    return 0;
}
void Computer::end_game(int wins){
    if(wins){
        cout << "哇喔! 電腦玩家[" << Player::name <<"] 贏了"<<Player::bet<<endl;
        Player::bankroll += Player::bet;
        win += 1;
    }
    else{
        cout << "可惜! 電腦玩家[" << Player::name <<"] 輸了"<<Player::bet<<endl;
        Player::bankroll -= Player::bet;
        win = 0;
    }
}
void Computer::dealer_bankroll(int income){
    Player::bankroll += income;
}

void Delay(int time)//time*1000為秒數 
{ 
    clock_t   now   =   clock(); 
    while(clock()-now<time); 
} 



