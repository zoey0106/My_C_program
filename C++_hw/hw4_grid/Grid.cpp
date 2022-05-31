using namespace std;
#include "Grid.h"
#define ON 1
#define OFF 0
char grid[40][40];
Grid::Grid(){
    row = 1;
    col = 1;
    grid[0][0] = '>';
    ds = EAST ;    
}
Grid::Grid(int r,int c){
    /*if(r<3||c<3){
        r=3;
        c=3;
    }
    else if(r>40||c>40){
        r=40;
        c=40;
    }
    static vector<char> row(c,0);
    static vector<vector<char>> grid(r,row);
*/
    srand( time(NULL) ); //初始化隨機種子
    //ex. r=4 c=4 => 有2個可以放mover (0~1)
    int mover = rand() % ((c*r) - (c*2+r*2-4) );//全部格子-邊
    //exit ex. r=4 c=3 => 有6個#可以放出口(得出0~5)
    int exit = rand() % (c*2+r*2-8); //最上下左右邊相加把重疊減去(4)再把角落減去(4)
    //確認可否填 和mover一樣就代表可以填
    int check_mover = 0;
    int check_exit = 0;

    if(r<3||c<3){
        r=3;
        c=3;
    }
    else if(r>40||c>40){
        r=40;
        c=40;
    }
    row = r;
    col = c;

    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            //如果在最上下左右的邊上，就填上# 
            if(i==0||i==(r-1)||j==0||j==(c-1)){
                if(check_exit == exit){
                    if(!(i==0&&j==0)){
                        if(!(i==(r-1)&&j==(c-1))){
                            if(!(i==(r-1)&&j==0)){
                                if(!(i==0&&j==(c-1))){
                                    grid[i][j] = '.';//exit
                                    check_exit++;
                                }
                                else{
                                    grid[i][j] = '#';
                                    break;
                                }
                            }
                            else{
                                grid[i][j] = '#';
                                break;
                            }
                        }
                        else{
                            grid[i][j] = '#';
                            break;
                        }
                    }
                    else{
                        grid[i][j] = '#';
                        break;
                    }
                }
                else{
                    check_exit++; 
                    grid[i][j] = '#';
                }
            }
            else{
                if(check_mover == mover){
                    switch(rand() % 4) { 
                        case NORTH:
                            grid[i][j] = '^';
                            ds = 0;
                            break; 
                        case WEST: 
                            grid[i][j] = 'v';
                            ds = 1;
                            break; 
                        case SOUTH: 
                            grid[i][j] = '<';
                            ds = 2; 
                            break; 
                        case EAST: 
                            grid[i][j] = '>';
                            ds = 3;
                            break; 
                        default: 
                            grid[i][j] = '>';
                            ds = 3;
                            break;
                    } 
                    check_mover++;
                }
                else{
                    check_mover++;
                    grid[i][j] = '.';
                }
                
            }
        }
    }
}
Grid::Grid(int r,int c,int mr,int mc,int d){
    PATH = ON;
    /*
    if(r<3||c<3){
        r=3;
        c=3;
    }
    else if(r>40||c>40){
        r=40;
        c=40;
    }
    static vector<char> row(c,0);
    static vector<vector<char>> grid(r,row);
    */
    if(r<3||c<3){
        r=3;
        c=3;
    }
    else if(r>40||c>40){
        r=40;
        c=40;
    }
    row = r;
    col = c;
    if(mr>=r){
        //若mr超過界線，mr會變成靠近的邊
        if((mr%r)>=(r/2)){
            mr = r-1;
        }
        else{
            mr = 0;
        }
    }
    
    if(mc>=c){
        //若mr超過界線，mr會變成靠近的邊
        if((mc%c)>=(c/2)){
            mc = c-1;
        }
        else{
            mc = 0;
        }
    }

    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if((i==mr)&&(j==mc)){
                switch (d)
                {
                    case NORTH:
                        grid[i][j] = '^';
                        ds=0;
                        break;
                    case SOUTH:
                        grid[i][j] = 'v';
                        ds=2;
                        break;
                    case WEST:
                        grid[i][j] = '<';
                        ds=1;
                        break;
                    case EAST:
                        grid[i][j] = '>';
                        ds=3;
                        break;
                    default:
                        break;
                }
            }
            else{
                grid[i][j] ='.';
            }
        }
    }
}
// toggle whether or not moved path is shown
void Grid::TogglePath(){
    if(PATH==1){
        PATH = OFF;
    }
    else{
        PATH = ON;
    }
} 
int Grid::GetNumRows() const{
        return row;
}
// return number of columns in the grid
int Grid::GetNumCols() const{
        return col;
}
// return row of the mover
int Grid::GetRow() const{
    int row = GetNumRows();
    int col = GetNumCols();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(grid[i][j] == '^'||grid[i][j] == 'v'||grid[i][j] == '>'||grid[i][j] == '<'||grid[i][j]=='@'){
                return i;
            }
        }
    }
    return 0;
} 
// return column of the mover
int Grid::GetCol() const{
    int row = GetNumRows();
    int col = GetNumCols();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(grid[i][j] == '^'||grid[i][j] == 'v'||grid[i][j] == '>'||grid[i][j] == '<'||grid[i][j]=='@'){
                return j;
            }
        }
    }
    return 0;
} 
void Grid::Display() const{
    cout << "The Grid:" <<endl;
    int r = GetNumRows();
    int c = GetNumCols();
    if(PATH == OFF){
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                if(grid[i][j] == ' '){
                    cout << '.' << ' ';
                }
                else{
                    cout << grid[i][j] << ' ';
                }
            }
            cout << endl;
        }
    }
    else{
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                cout << grid[i][j] << ' ';
            }
            cout << endl;
        }
    }
}
// check to see if space in front of mover is clear
bool Grid::FrontIsClear() const{
    int row = GetNumRows();
    int col = GetNumCols();
    int m_r = GetRow();
    int m_c = GetCol();
    if(ds == NORTH){
        if((m_r!=0)){
            if(grid[m_r-1][m_c] != '#'){
                return true;
            }
        }
    }
    else if(ds == SOUTH){
        if((m_r!=(row-1))){
            if(grid[m_r+1][m_c] != '#'){
                return true;
            }
        }
    }
    else if(ds == EAST){
        if((m_c!=(col-1))){
            if(grid[m_r][m_c+1] != '#'){
                return true;
            }
        }
    }
    else{
         if(m_c!= 0){
            if(grid[m_r][m_c-1] != '#'){
                return true;
            }
        }
    }
    return false;
} 
// check to see if space to right of mover is clear */
bool Grid::RightIsClear() const{
    int row = GetNumRows();
    int col = GetNumCols();
    int m_r = GetRow();
    int m_c = GetCol();
    if(ds == NORTH){
        if((m_c!=(col-1))){
            if(grid[m_r][m_c+1] != '#'){
                return true;
            }
        }
    }
    else if(ds == SOUTH){
        if(m_c!= 0){
            if(grid[m_r][m_c-1] != '#'){
                return true;
            }
        }
    }
    else if(ds == EAST){
        if((m_r!=(row-1))){
            if(grid[m_r+1][m_c] != '#'){
                return true;
            }
        }
    }
    else{
        if((m_r!=0)){
            if(grid[m_r-1][m_c] != '#'){
                return true;
            }
        }
    }
    return false;
} 
// put a block at (r, c), if possible
bool Grid::PlaceBlock(int r, int c){
    int row = GetNumRows();
    int col = GetNumCols();
    if((r<row) && (r>=0)){
        if((c<col) && (c>=0)){
            if(grid[r][c] == ' '||grid[r][c] == '.'){
                grid[r][c] = '#';
                return true;
            }
        }
    }
    return false;
}
// put down an item at the mover's position
void Grid::PutDown(){
    int m_r = GetRow();
    int m_c = GetCol();
    if(grid[m_r][m_c] != '@'){
        grid[m_r][m_c] = '@';
    }
    //若是本身在的地方沒有物品就不會是@的樣子
} 
// put down an item at (r, c), if possible    
bool Grid::PutDown(int r, int c){
    int row = GetNumRows();
    int col = GetNumCols();
    int m_r = GetRow();
    int m_c = GetCol();

    if(r>=row || r<0){
        return false;
    }
    else if(c>=col || c<0){
        return false;
    }
    else if(grid[r][c] == '#' ){
        return false;
    }
    else if((r==m_r) && (c == m_c)){
        if(grid[r][c] == '@'){//是@就不改
            return false;
        }
        else{//是mover only就改成@(擺上物品)
            grid[r][c] = '@';
            return true;
        }
    }
    else{
        grid[r][c] = '0' ; //若沒有超出界線+上面沒有障礙+上面的不是@或mover
        return true;
    }
    return false;
}
// pick up item at current position
bool Grid::PickUp(){
    int m_r = GetRow();
    int m_c = GetCol();
    if(grid[m_r][m_c] == '@'){
        if(ds == NORTH){
            grid[m_r][m_c] ='^';
        }
        else if(ds == SOUTH){
            grid[m_r][m_c] = 'v';
        }
        else if(ds == WEST){
            grid[m_r][m_c] = '<';
        }
        else if(ds == EAST){
            grid[m_r][m_c] = '>';
        }
        return true;
    }
    else{
        return false;
    }

    return false;
}
// move forward s spaces, if possible
bool Grid::Move(int s){
    int row = GetNumRows();
    int col = GetNumCols();
    int m_r = GetRow();
    int m_c = GetCol();
    if(ds == NORTH){
        //超過邊界
        if((m_r-s) < 0){
            return false;
        }
        else{
            for(int i=m_r-1;i>=(m_r-s);i--){
                if(grid[i][m_c] == '#'){
                    return false;
                }
            }
            for(int i=m_r-1;i>=(m_r-s);i--){
                if(grid[i][m_c] == '.'){
                    grid[i][m_c] = ' ';//走過的路消除   
                }
            }
        }
        if(grid[m_r][m_c] == '@'){
            grid[m_r][m_c] ='0';
        }
        else{
            grid[m_r][m_c] =' ';//先空著
        }
        if(grid[m_r-s][m_c] == '0'){
            grid[m_r-s][m_c] = '@';
        }
        else{
            grid[m_r-s][m_c] = '^'; //移動
        }
        return true;
    }
    else if(ds == WEST){
        //超過邊界
        if((m_c-s) < 0){
            return false;
        }
        else{
            for(int i=m_c-1;i>=(m_c-s);i--){
                if(grid[m_r][i] == '#'){
                    return false;
                }
            }
            for(int i=m_c-1;i>=(m_c-s);i--){
                if(grid[m_r][i] == '.'){
                    grid[m_r][i] = ' ';
                }
            }
        }
        //原本的位置
        if(grid[m_r][m_c] == '@'){
            grid[m_r][m_c] ='0';
        }
        else{
            grid[m_r][m_c] =' ';//先空著
        }
        //移動後
        if(grid[m_r][m_c-s] == '0'){
            grid[m_r][m_c-s] = '@';
        }
        else{
            grid[m_r][m_c-s] = '<'; //移動
        }
        return true;
    }
    else if(ds == SOUTH){
        //超過邊界
        if((m_r+s) >= row){
            return false;
        }
        else{
            for(int i=m_r+1;i<=(m_r+s);i++){
                if(grid[i][m_c] == '#'){
                    return false;
                }
            }
            for(int i=m_r+1;i<=(m_r+s);i++){
                if(grid[i][m_c] == '.'){
                    grid[i][m_c] = ' ';
                }
            }
        }
        //原本的位置
        if(grid[m_r][m_c] == '@'){
            grid[m_r][m_c] ='0';
        }
        else{
            grid[m_r][m_c] =' ';//先空著
        }
        //移動後
        if(grid[m_r+s][m_c] == '0'){
            grid[m_r+s][m_c] = '@';
        }
        else{
            grid[m_r+s][m_c] = 'v'; //移動
        }

        return true;
    }
    else if(ds == EAST){
        //超過邊界
        if((m_c+s) >= col){
            return false;
        }
        else{
            for(int i=m_c+1;i<=(m_c+s);i++){
                if(grid[m_r][i] == '#'){
                    return false;
                }
            }
             for(int i=m_c+1;i<=(m_c+s);i++){
                if(grid[m_r][i] == '.'){
                    grid[m_r][i] = ' ';
                }
            }
        }
         //原本的位置
        if(grid[m_r][m_c] == '@'){
            grid[m_r][m_c] ='0';
        }
        else{
            grid[m_r][m_c] =' ';//先空著
        }
        //移動後
        if(grid[m_r][m_c+s] == '0'){
            grid[m_r][m_c+s] = '@';
        }
        else{
            grid[m_r][m_c+s] = '>'; //移動
        }
        return true;
    }
    return false;
}
// turn the mover to the left
void Grid::TurnLeft(){
    int m_r = GetRow();
    int m_c = GetCol();

    if(ds == NORTH){
        ds = WEST;
        if(grid[m_r][m_c] != '@'){
            grid[m_r][m_c] = '<';
        }
    }
    else if(ds == WEST){
        ds = SOUTH;
        if(grid[m_r][m_c] != '@'){
             grid[m_r][m_c] = 'v';
        }
    }
    else if(ds == SOUTH){
        ds = EAST;
        if(grid[m_r][m_c] != '@'){
            grid[m_r][m_c] = '>';
        }
    }
    else if(ds == EAST){
        ds = NORTH;
        if(grid[m_r][m_c] != '@'){
            grid[m_r][m_c] = '^';
        }
    }
}
// grow the grid by gr rows, gc columns
void Grid::Grow(int gr, int gc){
    int row = GetNumRows();
    int col = GetNumCols();
    
    if(gr<0){
        gr = 0;
    }
    if(gc<0){
        gc =0;//不得減少
    }
    int set_row = row +gr;
    int set_col = col +gc;
    if(set_row>40){
        set_row = 40;
    }
    if(set_col>40){
        set_col = 40;
    }
    if(set_row<=3){
        set_row = 3;
    }
    if(set_col<=3){
        set_col = 3;
    }
    
    //先長row
    for(int i=row;i<set_row;i++){
        for(int j=0;j<col;j++){
            if(grid[i-1][j] == '#'){
                grid[i][j] = '#';
                if(j!=0&&j!=col-1){
                    grid[i-1][j] = '.';
                }
            }
            else{
                grid[i][j] = '.';
            }
        }
    }
    row = set_row;
    Grid::row = set_row;
    //再長col
    for(int i=0;i<row;i++){
        for(int j=col;j<set_col;j++){
            if(grid[i][j-1] == '#'){
                grid[i][j] = '#';
                if(i!=0&&i!=row-1){
                    grid[i][j-1] = '.';
                }
            }
            else{
                grid[i][j] = '.';
            }
        }
    }
    col = set_col;
    Grid::col = set_col;
}


