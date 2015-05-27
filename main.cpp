#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

void subSquare();
void magicSquare();
void division();
void summonProgrammer(); //Involves Magic

int randRange(int min, int max);
int getInt(string prompt);

#ifdef Important Functions Below
void instruction();
void mainMenu();
void yesOrNo();
void oneTwoThree();
void transferToMainMenu();
void menuSection();
void end();
void ready();
void results();
#endif //End of Important Functions

int main()
{
    srand(time(0));
    cout << "My name is Program for Arithmetic for Understanding and Learning," << endl
         << "but you can call me Paul." << endl << endl;
    char option = ' ';
    while(option != 'D')
    {
        cout << "Which game will you play, little epsilon?" << endl;
        cout << "\tA) Magic Square (One Player, Addition)" << endl
             << "\tB) Subtract a Square (Two Player, Multiplicaton and Subtraction)" << endl
             //<< "\tC) To be determined (Twoish Players, Division)" << endl
             << "\tD) Quit" << endl
             //<< "\tE) Summon Programmer" << endl
             ;
             string options;
        cin >> options;
        option = options[0];
        switch(option)
        {
        case 'A':
            magicSquare();
            break;
        case 'B':
            subSquare();
            break;
        case 'D':
            cout << "Good bye";
            break;
        }
    }
}

void subSquare()
{
    cout << endl;
    cout << "Instructions:" << endl
         << "\tThis game is called \"subtract a square.\" The goal of the game" << endl
         << "\tis to move last. There is a certain number, called the total." << endl
         << "\tI, Paul, shall select the total. Then, little epsilons, one of" << endl
         << "\tyou shall select a number, called the move.You can select any number" << endl
         << "\tbesides 0 (and no decimals or fractions.) You will then" << endl
         << "\tmultiply the move by itself, making a square number. Note: If your" << endl
         << "\tsquare is greater than the total, then you will have to pick a new" << endl
         << "\t move. You will then subtract the total by the square. You will take" << endl
         << "\tturns doing this. Whoever gets it to 0 will win!" << endl << endl
         << "\tDon't worry, I will walk you through the game, little epsilons." << endl << endl;

    string name[2];
    cin.ignore();
    cout << "First little epsilon, what is your name? ";
    getline(cin, name[0]);
    cout << "Second little epsilon, what is your name? ";
    getline(cin, name[1]);
    int level;
    do
    {
        level = getInt("Little epsilons, what difficulty will you play? (1 or more)(start with 1) ");
    }
    while(level < 1);
    int total = randRange(pow(10, level-1), pow(10, level));
    int turn = 0;
    while (total != 0)
    {
        cout << "The total is " << total << endl;
        cout << name[turn] << " it is your turn." << endl;
        cout << name[turn] << " pick a move." << endl;
        while(true)
        {
            int move;
            move = getInt(name[turn] + ": ");
            if (move == 0)
            {
                cout << "Sorry " << name[turn] << ", 0 is the only move that is never allowed." << endl;
                cout << "Pick another." << endl;
                continue;
            }
            if (move * move > total)
            {
                cout << "Sorry, but with move " << move << ", you square would be " << endl
                     << move << " x " << move  << " = " << move * move
                     << ", which is more than the total, " << total << "." << endl;
                cout << "Pick another." << endl;
                continue;
            }
            int square;
            do
            {
                cout << "Now, " << move << " x " << move << " is what?" << endl;
                square = getInt(name[turn] + ": ");
                if (move * move != square) cout << "That is wrong!" << endl;
                else break;
            }
            while(true);
            cout << "Yes!" << endl;
            int newTotal;
            do
            {
                cout << "And " << total << " - " << square << " is what?" << endl;
                newTotal = getInt(name[turn] + ": ");
                if (total - square != newTotal) cout << "That is wrong!" << endl;
                else break;
            }
            while(true);

            cout << "Yes!" << endl;
            total = newTotal;
            break;
        }
        turn = (turn + 1) % 2;
    }
    int loser = turn; //Ha Ha, can't move loser
    int winner = (loser + 1) % 2;
    cout << name[winner] << ", you have WON! Congratulations." << endl;
    cout << "Better luck next time " << name[loser] << ". :(" << endl;
}

int win[8][3] =
{
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
    {0, 3, 6},
    {1, 4, 7},
    {2, 5, 8},
    {0, 4, 8},
    {6, 4, 2}
};

char choices[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J'};

void magicSquare()
{
    string name;
    cin.ignore();
    cout << "What is your name, little epsilon? ";
    getline(cin, name);
    int level;
    do
    {
        level = getInt("What level will you play little epsilon? (1 or more) ");
    }
    while(level < 1);
    int magic = 3 * randRange(5*level, 5*(level+1)); //Random number from 15 * level to 15 * level + 15, that is divisible by 3
    int width = ceil(log10(magic)); //Guaranteed to be at least as many as the digits in magic
    cout << "In this game, you try and make the rows, columns, and diagonals add up to" << endl
        << "a special number called the magic constat. Also, you may not use the same" << endl
        << "number more than once. The magic constant for you is \"" << magic << ".\" Change the boxes" << endl
        << "so that each row, column, and diagonal, add up to \"" << magic << ".\" It will then quiz you" << endl
        << "to see if you are right. Answer the addition problems honestly." << endl
        ;
    cout << endl << "Do not worry, little epsilon. I, paul, will walk you through it." << endl << endl;

    int square[9] = {0};
    while(true)
    {
        for (int i=0; i < 9; i++) //Display the Square Loop
        {
            cout << choices[i] << setw(width) << square[i];
            if ((i+1)%3 == 0)
            {
                cout << endl;
            }
            else
            {
                cout << "|";
            }
        }
        cout << name << ", which square would you like to change? (or Z to check if you are right) ";
        string moves;
        cin >> moves;
        char movec = moves[0];
        for (int i=0; i < 9; i++)
        {
            if (choices[i] == movec)
            {
                int n;
                do
                {
                    n = getInt("What would you like to change that box to? ");
                    if (n < 0 || n > magic)
                    {
                        cout << "That can not possibly be right; try again." << endl;
                    }
                    else break;
                }
                while(true);
                square[i] = n;
                break;
            }
        }
        if (movec == 'Z')
        {
            bool dup = false;
            for (int i=0; i < 9; i++)
            {
                for (int j=0; j < 9; j++)
                {
                    if (i != j && square[i] == square[j])
                    {
                        cout << "Sorry, but you have " << square[i] << " at least twice. All boxes must be unique." << endl;
                        dup = true;
                        break;
                    }
                }
                if (dup) break;
            }
            if (dup) continue;
            bool won = true;
            for (int i=0; i < 8; i++)
            {
                int s;
                do
                {
                    cout << "What is " << square[win[i][0]] << " + " << square[win[i][1]] << " + " << square[win[i][2]] << "? ";
                    s = getInt(name + ": ");
                    if (s != (square[win[i][0]] + square[win[i][1]] + square[win[i][2]]))
                    {
                        cout << "Sorry, that is not right. Try again." << endl;
                        cout << "What is " << square[win[i][0]] << " + " << square[win[i][1]] << " + " << square[win[i][2]] << "? ";
                    }
                    else break;
                }
                while(true);
                cout << "Right!" << endl;
                if (s!=magic)
                {
                    cout << s << " is not the magic constant, " << magic << ", though. You will have to change something." << endl;
                    won = false;
                    break;
                }
            }
            if (won) break;
        }
    }
    cout << "Since these are all the magic constant, you have won " << name << "!" << endl;
}

int randRange(int min, int max)
{
    return (rand() % (max-min))+min;
}

// Based on http://stackoverflow.com/a/10349885/1172541, thanks to chris
int getInt(string prompt)
{
    int num;
    while (cout << prompt && !(cin >> num))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Sorry, that is not a number." << endl;
        cout << "You may now try again." << endl;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return num;
}

#ifdef Important Functions Defined Here
string instruction()
{
    cout >> "In this game you do arithmetic." << endl;
cout >> "And arithmetic is fun!" << endl:
         return 0;
}

void mainMenu()
{
    switch(option)
    case 1:
    Add
    break;
case 2:
    Subtract
    break;
case 3:
    Multiply
    break;
case 4:
    Divide and Conqueror
    break;
case:
case case case return case;
}

void yesOrNo(bool yesOrNo)
{
    return yesOrNo;
}

array oneTwoThree()
{
    return 1;
    return 2;
    return 3;
}

void transferToMainMenu(mainMenu)
{
    '(transfer mainMenu)
}

    void end()
    {
    print "Sorry, game over"
}

    void ready()
    {
    main :: IO()
    main = do
    a <- readLine
    b <- readLine
    return $ a + b
}

    void results()
    {
    system.out.println("The result is you win!");
}

#endif //End of important functions
