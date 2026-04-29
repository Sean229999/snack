#include<iostream>
#include<conio.h>
#include<windows.h>
#include<random>
#include<ctime>
#include<chrono>

using namespace std;

#define height 20
#define weight 30


//头部和坐标
char head = 'H';
int pos_x = weight / 2;
int pos_y = height / 2;

//身体长度和坐标，默认为3
int length = 3;
int body_x[100];
int body_y[100];

// int food_num = 3;
// int food_x[100];
// int food_y[100];

//食物坐标
int food_x;
int food_y;

//分数
int score = 0;

//方向，默认向上
int dir = 1;

//生成随机数，获取食物坐标
int randomNumGen(int l,int r){
    static default_random_engine e(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> u(l,r);
    return u(e);
}

bool isOnBody(int x,int y){
    if(x == pos_x && y == pos_y){
        return true;
    }
    for(int i = 0;i<length;i++){
        if(x == body_x[i] && y == body_y[i]){
            return true;
        }
    }

    return false;
}



//生成食物
void genFood(){

    int x = randomNumGen(2,weight-1);
    int y = randomNumGen(2,height-1);

    //防止生成到蛇身上
    if(isOnBody(x,y)){
        genFood();
    }

    food_x = x;
    food_y = y;
}

//墙壁检测
bool noWallY(int pos){
    return (pos < height && pos >= 0);
}
bool noWallX(int pos){
    return (pos < weight-1 && pos > 0);
}

//游戏结束条件
bool isOver(){
    
    //判断是否碰到墙壁
    if(pos_x <=0 || pos_x >= weight){
        return true;
    }
    if(pos_y <=0 || pos_y >= height){
        return true;
    }

    //判断头部是否碰到身体
    for(int i = 0;i<length;i++){
        if(pos_x == body_x[i] && pos_y == body_y[i]){
            return true;
        }
    }
    return false;

}


//移动
void Move(int dir){
    if(dir == 1){
        pos_y--;
    }
    else if(dir == 2){
        pos_y++;
    }
    else if(dir == 3){
        pos_x++;
    }
    else if(dir == 4){
        pos_x--;
    }
    
    //碰到边界时从另一个方向出来
    // if(pos_x >=weight+1){
    //     pos_x = 0;
    // }
    // else if(pos_x <= -1){
    //     pos_x = weight;
    // }

    // if(pos_y >=height+1){
    //     pos_y = 0;
    // }
    // else if(pos_y <= -1){
    //     pos_y = height;
    // }

}

//更新身体的坐标
void snackbody(){
    
    for(int i = length-1;i>0;i--){
        body_x[i] = body_x[i-1];
        body_y[i] = body_y[i-1];    
    }

    body_x[0] = pos_x;
    body_y[0] = pos_y;

}

//判断该当前是否有蛇的身体
bool IsdrawBody(int x,int y){
    for(int i = 0;i<length;i++){
        if(body_x[i]== x && body_y[i] == y){
            return true;
        }
    }
    return false;
}

//判断当前坐标是否有食物
bool IsdrawFood(int x,int y){
    if(food_x == x && food_y == y){
        return true;
    }

    return false;
}

//绘制地图和蛇以及食物
void draw(){
    for(int i = 0;i<weight;i++){
        cout << "#";
    }
    cout << endl;
    for(int j = 0;j<height;j++){
        for(int i = 0;i<weight;i++){
            if(i == 0 || i == weight - 1){
                cout << "#";
            }
            else if(i == pos_x && j == pos_y){
                cout << head;
            }
            else if(IsdrawBody(i,j)){
                cout << "o";
            }
            else if(IsdrawFood(i,j)){
                cout << "*";
            }
            else{
                cout << " ";
            }
        }
        cout << endl;
    }
    for(int i = 0;i<weight;i++){
        cout << "#";
    }
    cout << endl;
    cout << "You have got " << score << " Score";
    cout << endl;
    if(score < 50){
        cout << "Come on budy,you can make it!";
    }
    else if(score >= 50 && score < 100){
        cout << "Great! You are a total master!";
    }
    else if(score >=100 && score < 200){
        cout << "Holy shit! that is fucking crazy!";
    }
    else if(score >= 200){
        cout << "You are GOAT!";
    }
    else if(score >= 1000){
        cout << "What can I say, Maba out";
    }
    cout << endl;

}

//判断是否吃到食物
bool getFood(int x,int y){
    // for(int i = 0;i<food_num;i++){
    //     if(food_x[i] == x && food_y[i] == y){
    //         food_x[i] = -1;
    //         food_y[i] = -1;
    //         return true;
    //     }
    // }
    if(food_x == x && food_y == y){
        return true;
    }

    return false;
}

//变长
void increaseLenght(int x,int y){
    if(getFood(x,y)){
        length++;
        genFood();
        score+=10;
    }
}

void init(){

    for(int i = 0;i<100;i++){
        body_x[i] = -1;
        body_y[i] = -1;
    }

    body_x[0] = pos_x;
    body_y[0] = pos_y+1;
   
    body_x[1] = pos_x;
    body_y[1] = pos_y+2;
   
    body_x[2] = pos_x;
    body_y[2] = pos_y+3;


    genFood();

}



int main(){

    
    cout << "Press s to start or press q to quit:" <<endl;
    char t;
    cin >> t;
    
    init();

    if(t == 's'){
        while(1){
            
            draw();
            if(isOver()){
                cout << "Game Over! You finally got " << score << " Score" << endl;
                return 0;
            }

            increaseLenght(pos_x,pos_y);

            snackbody();
            Move(dir);

            if(_kbhit()){
                char ch = _getch();
                if(ch == 'w' && dir != 2){
                    dir = 1;
                }
                else if(ch == 's' && dir != 1){
                    dir = 2;
                }
                else if(ch == 'd' && dir != 4){
                    dir = 3;
                }
                else if(ch == 'a' && dir != 3){
                    dir = 4;
                }
                if(ch == 'q'){
                    cout << "You finally got " << score << " Score" << endl;
                    break;
                } 
            }
            
            Sleep(100);
            system("cls");
        }
    }
    else if(t == 'q'){
        return 0;
    }
    
    return 0;
}