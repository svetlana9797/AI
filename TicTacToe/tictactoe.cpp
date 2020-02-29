#include<iostream>
using namespace std;
int idx;
char board[9] = {'*','*','*','*','*','*','*','*','*'};

//check if the board is full
bool isFull()
{
    for(int i =0; i<9; i++)
    {
        if(board[i]!='X'&&board[i]!='O')
            return 0;
    }

    return 1;
}

bool has_won(char sign)
{
    for(int i=0; i<9; i+=3)
    {
        if((board[i]==board[i+1])&&(board[i+1]==board[i+2])&&(board[i]==sign))
            return 1;
    }
    for(int i=0; i<3; i++)
    {
        if((board[i]==board[i+3])&&(board[i+3]==board[i+6])&&(board[i]==sign))
            return 1;
    }
    if((board[0]==board[4])&&(board[4]==board[8])&&(board[0]==sign))
    {
        return 1;
    }
    if((board[2]==board[4])&&(board[4]==board[6])&&(board[2]==sign))
    {
        return 1;
    }
    return 0;
}

void print_board() //display tic-tac-toe board
{
    cout<<endl;
    cout<<board[0]<<"|"<<board[1]<<"|"<<board[2]<<endl;
    cout<<"-----"<<endl;
    cout<<board[3]<<"|"<<board[4]<<"|"<<board[5]<<endl;
    cout<<"-----"<<endl;
    cout<<board[6]<<"|"<<board[7]<<"|"<<board[8]<<endl;
}

//flag=1 -> Computer's move
int minMax(bool flag)
{

    int alpha=-1000;
    int beta=1000;

    int val = 1;

    if(has_won('X'))
    {
        return 10;
    }

    else if(has_won('O'))
    {
        return -10;
    }

    else if(isFull())
    {
        return 0;
    }

    int values[9] = {1,1,1,1,1,1,1,1,1};//value[i]=1 <=> it is empty

    for(int i=0; i<9; i++)
    {
        if(board[i] == '*')
        {
            if(beta>alpha)
            {
                if(flag == true) //Computer
                {
                    board[i] = 'X';
                    val = minMax(false);
                }
                else //User
                {
                    board[i] = 'O';
                    val = minMax(true);
                }
                board[i] = '*';
                values[i] = val;
            }
        }
    }

    //Computer
    if(flag == true)
    {
        alpha = -1000;
        for(int j=0; j<9; j++)
        {
            if(values[j] > alpha && values[j] != 1)
            {
                alpha = values[j];
                idx = j;
            }
        }
        return alpha;
    }

    //User
    if(flag == false)
    {
        beta = 1000;
        for(int j=0; j<9; j++)
        {
            if(values[j] < beta && values[j] != 1)
            {
                beta = values
                [j];
                idx = j;
            }
        }
        return beta;
    }
}

int main() //The main function
{
    int move,choice;
    cout<<"TIC TAC TOE GAME";
    cout<<endl<<"USER->(O) CPU->(X)";
    cout<<endl<<"SELECT :\nPlayer first -> enter 1\n Computer first->enter 2\n";
    cin>>choice;

//if the user is first
    if(choice == 1)
    {
        print_board();
up:
        cout<<endl<<"Enter the move:";
        cin>>move;
        if(board[move-1]=='*')
        {
            board[move-1] = 'O';
            print_board();
        }
        else
        {
            cout<<endl<<"Invalid Move! Please try a different move";
            goto up;
        }
    }

    while(true)
    {

        cout<<endl<<"Computer MOVE:";
        minMax(true);
        board[idx] = 'X';

        print_board();

        if(has_won('X'))
        {
            cout<<endl<<"CPU WON!";
            return 0;
        }

        if(isFull())
        {
            cout<<endl<<"No one wins";
            return 0;
        }
again:
        cout<<endl<<"Enter the move:";
        cin>>move;

        if(board[move-1]=='*')
        {
            board[move-1] = 'O';
            print_board();
        }
        else
        {
            cout<<endl<<"Invalid Move! Please try a different move";
            goto again;
        }

        if(has_won('O'))
        {
            cout<<endl<<"You Won!";
            return 0;
        }
        if(isFull())
        {
            cout<<endl<<"No one wins";
            return 0;
        }
    }
}
