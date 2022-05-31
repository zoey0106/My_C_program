#include "cls_func.h"
using namespace std;
#include <ctime> 
typedef Card Deck [52];
typedef bool (*f)(int);
Computer Dealer("Dealer",10000,"Dealer");//Dealer只要建立一次就可以

int main () {
    
    srand(time(NULL));

    //data
    int new_round = 1;
    int end_of_round = 0;//控制一回合是否結束的變數
    int human_player = 0;
    int computer_player = 0;
    int bankroll;
    string name;
    string triat;
    char y_or_n[2];//輸入要不要繼續的字串
    int custimize;
    int race = 0;//new
    int win_money = 0;
    int lose_money = 0;
    int victory = 0;
    int lose = 0;
    //整個遊戲的開始
    cout << "**21點遊戲開始!**" <<endl;

    //非自定義玩法
    cout << "# 非自定義玩法只會有一個可控制玩家,以及兩種個性不同的電腦玩家一起進行遊戲!(初始資金皆為100) #" <<endl;
    cout << "# 想要玩非自定義玩法的話輸入0,想要玩自定義玩法的則輸入1 #" << endl;
    cout << "輸入 : ";
    cin >> custimize;

    if(custimize){
        cout << "$$  再選擇額外玩家之前,若是只有一個玩家,輸入0就可以了喔!  $$" <<endl;
        cout << "[ 想要有幾個<額外>自控的玩家呢? ] : ";
        cin >>  human_player; 
        cout << "[ 那電腦玩家需要幾位呢? ] : ";
        cin >> computer_player;
    }
    else{//非自定義
        human_player = 0;
        computer_player = 2;
        cout << "[ 想要玩競賽模式嗎?(非自定義限定) 贏到輸入的值就為成功! 相反的,若是輸了超過五倍輸入的值就算是失敗喔!(會停止回合) ]" << endl;
        cout << "$$  輸入1就可以遊玩此模式!  $$" <<endl;
        cout << "輸入: " ;
        cin >> race;
        if(race){
            cout << "競賽模式開啟! 輸入目標贏得金錢! : ";
            cin >> win_money;
            if(win_money <= 0){
                cout << " OAO 贏得的金錢不能輸入小於0的數字啦! 作弊不好喔(自動關閉競賽模式)" <<endl;
                race = 0;
            }
            else{
                lose_money = 5*win_money;
                cout << "** GOGO~! 目標贏得金錢為: " << win_money <<" 並且小心喔! 若是總共輸大於等於 " << lose_money;
                cout << " 就算是失敗了! 祝你成功 QWQ **" << endl;
            }
        } 
        else{
            cout << "## 已選擇競賽模式不要開啟! ##" << endl;
        }
    }
    //new
    if(human_player<0){
        cout << "$$  額外玩家意外輸入成負的了!自動調整成0個額外玩家  $$"<< endl;
        human_player = 0; 
    }
    human_player += 1;//加上自己
    if(computer_player<0){
        cout << "$$  電腦玩家意外輸入成負的了!自動調整成0個額外玩家  $$"<< endl;
        computer_player = 0;
    }
    //建立指向class的陣列
    Human* human_arr = new Human[human_player];
    Computer* computer_arr = new Computer[computer_player];
    if(custimize){
        cout << "[ 接下來請輸入包含自己和額外各玩家的名字和初始資金! ]"<<endl;
        for(int i=0;i < human_player;i++){
            cout << "[玩家" << i+1 << "] 名字 初始資金 :";
            cin >> name >> bankroll;
            human_arr[i] = Human(name,bankroll);//呼叫constructor
        }
        if(computer_player > 0){
            cout << "NOTICE: 電腦玩家會有兩種個性,分別是 Meek 和 Random 可以做選擇" << endl;
            cout << "[ 接下來請輸入包含各電腦玩家的名字和初始資金以及他的個性 ]"<<endl;
        }
        for(int i=0;i < computer_player;i++){
            cout << "[電腦玩家" << i+1 << "] 名字 初始資金 個性 :";
            cin >> name >> bankroll >> triat;
            if(triat != "Meek" && triat != "Random"){
                cout << "$$  貌似輸入錯個性了! 自動調整為Meek!  $$" << endl;
                triat = "Meek";
            }
            computer_arr[i] = Computer(name,bankroll,triat);//呼叫constructor
        }
    }
    else{
        cout << "請輸入自己的名字: ";
        cin >> name;
        human_arr[0] = Human(name,100);//只有自己   
        computer_arr[0] = Computer("Meek",100,"Meek");//呼叫constructor
        computer_arr[1] = Computer("Random",100,"Random");
    }
    
    

    int bet = 0;
    //確認要幾副牌組
    int cardset = (human_player + computer_player)/3 + 1;//總共三人的話，會要2副牌

    //Deck cards;//牌
    auto deck_cards = new Card [cardset][52];
    int deck_ptr = 0;//第幾副
    int card_index = 0;//第幾張
    int total_card = cardset * 52;
    int minium_card = 5*(human_player + computer_player);//最少需要的卡
    int left_card;
    for(int i=0;i<cardset;i++){
        set_cards(deck_cards[i]);//回歸全新牌組的樣子
        shuffle(deck_cards[i]);//洗牌
    }

    //正式進入遊戲
    while (1)
    {   
        //每一round的開始
        if(new_round){
            left_card = total_card - (deck_ptr * 52) - card_index;
            if(left_card < minium_card){//這邊確認了至少人會有五張，所以之後各發兩張時不用確認會不會太少
                for(int i=0;i<cardset;i++){
                    shuffle(deck_cards[i]);
                }
                deck_ptr = 0;
                card_index = 0;
            }
            new_round = 0;
            cout << "--------------------" <<endl;
            cout << "新的一回合開始了" << endl;
            //(每回合之前都要先確認剩餘的卡是否足夠5*所有玩家)
            for(int i=0;i < human_player;i++){
                cout << "[" << human_arr[i].name << "] 這一回合的賭注要多少呢?: ";
                cin >> bet;
                if(bet <= 0){
                    cout << "賭注不可為0以下! 自動調整賭注為1" << endl;
                    bet = 1;
                }
                human_arr[i].set_all(bet);//清理上一回合的東西
            }
            //接下來印出所有賭注順便直接各發兩張牌
            for(int i=0;i<human_player;i++){
                cout << "[" << human_arr[i].name << "] 賭 ";
                human_arr[i].p_bet();
                for(int j=0;j<2;j++){
                    human_arr[i].store_card(deck_cards[deck_ptr][card_index]);
                    if(card_index == 52){
                        deck_ptr += 1;
                        card_index = 0;
                    }
                    else{
                        card_index++;
                    }
                }
                Delay(500);   //延時0.5秒 
            }
            for(int i=0;i < computer_player;i++){
                cout << "[" << computer_arr[i].name << "] 賭 ";
                //要寫自動bet
                computer_arr[i].set_all();
                computer_arr[i].p_bet();
                for(int j=0;j<2;j++){
                    computer_arr[i].store_card(deck_cards[deck_ptr][card_index]);
                    if(card_index == 52){
                        deck_ptr += 1;
                        card_index = 0;
                    }
                    else{
                        card_index++;
                    }
                }
                Delay(500);
            }
            Dealer.set_all();
            for(int j=0;j<2;j++){//dealer也發兩張牌
                    Dealer.store_card(deck_cards[deck_ptr][card_index]);
                    if(card_index == 52){
                        deck_ptr += 1;
                        card_index = 0;
                    }
                    else{
                        card_index++;
                    }
            }
            cout << "各玩家初始卡牌如下:" <<endl;
            cout << "--------------------" << endl;
            //印出初始卡牌
            for(int i=0;i<human_player;i++){
                human_arr[i].p_card(0);
                Delay(500);
            }
            for(int i=0;i<computer_player;i++){
                computer_arr[i].p_card(0);
                Delay(500);
            }
            Dealer.p_card(0);
            //每一人的這一局的回合開始
            for(int i=0;i<human_player;i++){
                cout << "[" << human_arr[i].name <<"]的回合:" << endl;
                cout << "--------------------" << endl;
                human_arr[i].p_card(1);
                while (1)
                {
                    cout << "想要再抽一張嗎?(y/n): " ;
                    cin >> y_or_n;
                    if(y_or_n[0] == 'y'||y_or_n[0] =='Y'){
                        cout <<"["<<human_arr[i].name <<"]" <<"選擇抽卡"<<endl;
                        human_arr[i].store_card(deck_cards[deck_ptr][card_index]);
                        if(card_index == 52){
                            deck_ptr += 1;
                            card_index = 0;
                        }
                        else{
                            card_index++;
                        }
                        if(human_arr[i].return_points() >21){
                            human_arr[i].p_card(1);
                            cout<<"[" <<human_arr[i].name<< "] 爆開了!超過21點" << endl;
                            cout << "--------------------" << endl;
                            break;
                        }
                        else{
                            human_arr[i].p_card(1);
                        }
                        left_card = total_card - (deck_ptr * 52) - card_index;
                        if(left_card < minium_card){//這裡之後可以修改
                            for(int i=0;i<cardset;i++){
                                shuffle(deck_cards[i]);
                            }
                            deck_ptr = 0;
                            card_index = 0;
                        }
                    }
                    else{
                        cout <<"[" <<human_arr[i].name<<"]"<<"選擇不繼續抽了"<<endl; 
                        cout << "--------------------" << endl;
                        break;
                    }
                    Delay(500);
                }
            }
            for(int i=0;i<computer_player;i++){
                cout << "[" << computer_arr[i].name <<"]的回合:" << endl;
                cout << "--------------------" << endl;
                computer_arr[i].p_card(1);
                Delay(500);
                while (1)
                {
                    if(computer_arr[i].strategy()){
                        
                        cout <<"["<<computer_arr[i].name <<"]" <<"選擇抽卡"<<endl;
                        computer_arr[i].store_card(deck_cards[deck_ptr][card_index]);
                        if(card_index == 52){
                            deck_ptr += 1;
                            card_index = 0;
                        }
                        else{
                            card_index++;
                        }

                        if(computer_arr[i].return_points() >21){
                            computer_arr[i].p_card(1);
                            cout<<"[" <<computer_arr[i].name<< "] 爆開了!超過21點" << endl;
                            cout << "--------------------" << endl;
                            break;
                        }
                        else{
                            computer_arr[i].p_card(1);
                        }

                        left_card = total_card - (deck_ptr * 52) - card_index;
                        if(left_card < minium_card){//這裡之後可以修改
                            for(int i=0;i<cardset;i++){
                                shuffle(deck_cards[i]);
                            }
                            deck_ptr = 0;
                            card_index = 0;
                        }
                    }
                    else{
                        cout <<"[" <<computer_arr[i].name<<"]"<<"選擇不繼續抽了"<<endl; 
                        cout << "--------------------" << endl;
                        break;
                    }
                    Delay(500);
                }
                   
            }
            cout << "[" << Dealer.name <<"]的回合:" << endl;
            cout << "--------------------" << endl;
            Dealer.p_card(1);
            Delay(500);
            //Dealer的回合
            while (1)
            {
                if(Dealer.strategy()){
                    cout <<"["<<Dealer.name <<"]" <<"選擇抽卡"<<endl;
                    Dealer.store_card(deck_cards[deck_ptr][card_index]);
                    if(card_index == 52){
                        deck_ptr += 1;
                        card_index = 0;
                    }
                    else{
                        card_index++;
                    }
                    if(Dealer.return_points() >21){
                        Dealer.p_card(1);
                        cout<<"[" <<Dealer.name<< "] 爆開了!超過21點" << endl;
                        cout << "--------------------" << endl;
                        break;
                    }
                    else{
                        Dealer.p_card(1);
                        }
                        left_card = total_card - (deck_ptr * 52) - card_index;
                        if(left_card < minium_card){//這裡之後可以修改
                            for(int i=0;i<cardset;i++){
                                shuffle(deck_cards[i]);
                            }
                            deck_ptr = 0;
                            card_index = 0;
                        }
                }
                else{
                    cout <<"[" <<Dealer.name<<"]"<<"選擇不繼續抽了"<<endl; 
                    cout << "--------------------" << endl;
                    break;
                }
                Delay(500);
            }
        }
        cout << "回合結果如下:" << endl;
        int dealer_IO = 0;
        if(Dealer.return_points()>21){
            for(int i=0;i<human_player;i++){
                if(human_arr[i].return_points()<=21){
                    human_arr[i].end_game(1);
                    dealer_IO -= human_arr[i].return_bet();
                }
                else{
                    human_arr[i].end_game(0);
                    dealer_IO += human_arr[i].return_bet();
                }
                Delay(500);
            }
            for(int i=0;i<computer_player;i++){
                if(computer_arr[i].return_points()<=21){
                    computer_arr[i].end_game(1);
                    dealer_IO -= computer_arr[i].return_bet();
                }
                else{
                    computer_arr[i].end_game(0);
                    dealer_IO += computer_arr[i].return_bet();
                }
                Delay(500);
            }
        }
        else{
            for(int i=0;i<human_player;i++){
                if((human_arr[i].return_points() > Dealer.return_points())&&human_arr[i].return_points()<=21){
                    human_arr[i].end_game(1);
                    dealer_IO -= human_arr[i].return_bet();
                }
                else{
                    human_arr[i].end_game(0);
                    dealer_IO += human_arr[i].return_bet();
                }
                Delay(500);
            }
            for(int i=0;i<computer_player;i++){
                if((computer_arr[i].return_points() > Dealer.return_points())&&computer_arr[i].return_points()<=21){
                    computer_arr[i].end_game(1);
                    dealer_IO -= computer_arr[i].return_bet();
                }
                else{
                    computer_arr[i].end_game(0);
                    dealer_IO += computer_arr[i].return_bet();
                }
                Delay(500);
            }
        }
        Dealer.dealer_bankroll(dealer_IO);
        
        cout << "目前各玩家剩餘資金:" << endl;
        cout << "--------------------" << endl;
        for(int i=0;i<human_player;i++){
            human_arr[i].p_bankroll();
            if(race){
                int money = human_arr[i].return_bankroll();
                if(money > 100){
                    money = money - 100;
                    if(money >= win_money){
                        victory = 1;
                    }
                    else{
                        cout << "目前贏得:" <<money<<endl;
                    }
                }
                else{
                    money = 100 - money;
                    if(money >= lose_money){
                        lose = 1;
                    }
                    else{
                        cout << "目前輸了:" <<money<<endl;
                    }
                }
            }
            Delay(500);
        }
        for(int i=0;i<computer_player;i++){
            computer_arr[i].p_bankroll();
            Delay(500);
        }        
        cout << "莊家剩餘本金:"<<endl;
        cout << "--------------------" << endl;
        Dealer.p_bankroll();
        if(race){
            if(victory){
                cout << "恭喜你!!!競賽成功了!你贏得了:" << win_money <<endl;
                cout << "~快樂的結束遊戲~" <<endl;
                break;
            }
            else if(lose){
                cout << "好可惜....你已經輸了:" << lose_money <<endl;
                cout << "下次再挑戰一次!遊戲結束" <<endl;
                break;
            }
            else{
                cout << "下一回合繼續開始!" <<endl;
                new_round = 1;
            }
        }
        else{
            //確認再來一次
            cout << "想要再來一局嗎?(y/n)" << endl;
            cin >> y_or_n;
            y_or_n[1] = '\0';
            if(y_or_n[0] == 'y'||y_or_n[0] =='Y'){
                new_round = 1;
            }
            else{
                cout << "遊戲結束，希望一切順心!" << endl;
                break;//迴圈結束
            }
        }
    }
    

    delete[] human_arr;
    delete[] computer_arr;
    delete[] deck_cards;
    return 0;
}