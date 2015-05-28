#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

void subSquare();
void magicSquare();
void division();

int randRange(int min, int max); // Random Integer x, such that min <= x < max
int getInt(string prompt); //Safely aquire int from stdin

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
    char option; //Selection from main menu
    do
    {
        cout << "Which game will you play, little epsilon?" << endl;
        cout << "\tA) Arcade: Most Divisions (1 Player, Division)" << endl
             << "\tB) Versus: Subtract a Square (2 Players, Multiplicaton, Subtraction)" << endl
             << "\tC) Puzzle: Magic Square (1 Player, Addition)" << endl
             << "\tD) Quit" << endl
             //<< "\tE) Summon Programmer" << endl
             ;
        string options;
        cin >> options;
        option = options[0];
        switch(option)
        {
        case 'C':
            magicSquare();
            break;
        case 'B':
            subSquare();
            break;
        case 'A':
            division();
            break;
        case 'D':
            cout << "Good bye" << endl;
            break;
        }
    }
    while(option != 'D');
}

void subSquare()
{
    cout << endl;
    cout << "Instructions:" << endl
         << "\tThis game is called \"subtract a square.\" The goal of the game" << endl
         << "\tis to move last. There is a certain number, called the total." << endl
         << "\tI, Paul, shall select the total. Then, little epsilons, one of" << endl
         << "\tyou shall select a number, called the move. You can select any number" << endl
         << "\tbesides 0 (and no decimals or fractions.) You will then" << endl
         << "\tmultiply the move by itself, making a square number. Note: If your" << endl
         << "\tsquare is greater than the total, then you will have to pick a new" << endl
         << "\t move. You will then subtract the total by the square. You will take" << endl
         << "\tturns doing this. Whoever gets it to 0 will win!" << endl
         << "\tIf you want to quit, type 0." << endl
         << endl << "\tDon't worry, I will walk you through the game, little epsilons." << endl << endl;

    string name[2]; //Store the names in an array
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
    int total = randRange(pow(10, level-1), pow(10, level)); //level is number of digits
    int turn = 0; //Index of name array, a.k.a., switches between 0 and 1
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
                cout << "Are you sure you want to quit (y/n)? ";
                string ans;
                cin >> ans;
                if (ans[0] == 'y') return;
                else continue;
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
            int newTotal; //Temporary total until user gets newTotal correct
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
    int loser = turn;
    int winner = (loser + 1) % 2; //Other player
    cout << name[winner] << ", you have WON! Congratulations." << endl;
    cout << "Better luck next time " << name[loser] << ". :(" << endl;
}

int win[8][3] = //Rows, Columns, and Diagonals
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

char choices[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J'}; //Indexed cell names

void magicSquare()
{
    string name;
    cin.ignore();
    cout << "What is your name, little epsilon? ";
    getline(cin, name);
    int level; //Determines size of magic constant
    do
    {
        level = getInt("What level will you play little epsilon? (1 or more) ");
    }
    while(level < 1);
    int magic = 3 * randRange(5*level, 5*(level+1)); //Random number from 15 * level to 15 * level + 15, that is divisible by 3
    int width = ceil(log10(magic)); //Guaranteed to be at least as many as the digits in magic, for formatting purposes
    cout << "Instructions: " << endl
        << "\tIn this game, you try and make the rows," << endl
        << "\tcolumns, and diagonals add up to" << endl
        << "\ta special number called the magic constat." << endl
        << "\tAlso, you may not use the same" << endl
        << "\tnumber more than once. The magic constant" << endl
        << "\tfor you is \"" << magic << ".\" Change the boxes" << endl
        << "\tso that each row, column, and diagonal," << endl
        << "\tadd up to \"" << magic << ".\" It will then quiz you" << endl
        << "\tto see if you are right. Answer the addition problems honestly." << endl
        ;
    cout << endl << "Do not worry, little epsilon. I, paul, will walk you through it." << endl << endl;

    int square[9] = {0};
    while(true)
    {
        cout << endl;
        for (int i=0; i < 9; i++) //Display the Square Loop
        {
            cout << choices[i] << setw(width) << square[i];
            if ((i+1)%3 == 0) //End of row
            {
                cout << endl;
            }
            else
            {
                cout << "|";
            }
        }
        cout << "Which square would you like to change? (Z:Check square, 0:Quit) ";
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
                    n = getInt(name + ", what would you like to change that box to? ");
                    if (n < 0 || n > magic) //This also makes sure cells don't violate cell width
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
                        cout << endl;
                        cout << "Sorry, but you have " << square[i] << " at least twice. You must change them to be different." << endl;
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
        if (movec==0)
        {
            cout << "Are you sure you want to quit (y/n)? ";
            string ans;
            cin >> ans;
            if (ans[0] == 'y') break;
        }
    }
    cout << "Since these are all the magic constant, you have won, " << name << "!" << endl;
}

void division()
{
    cout << endl;
    cout << "Instructions" << endl
        << "\tIn this game, you are trying to get as many points as you can." << endl
        << "\tI, paul, shall pick a number called the total. Each turn, you" << endl
        << "\tshall pick a number, called the move. The total must be divisible" << endl
        << "\tby the move. You will then divide the total by the move. Each turn," << endl
        << "\tyou get one point. You may not divide by 1, as this would allow you" << endl
        << "\tto go on forever. No decimals, fractions, or negatives either." << endl
        << "\tWhen you get to one, the game is over. Type 0 to quit." << endl
        << endl << "\tTry and get the high score, little epsilon!" << endl << endl;
    string name;
    cin.ignore();
    cout << "What is your name, little epsilon? ";
    getline(cin, name);
    int level; //Number of digits == level + 1
    do
    {
        level = getInt("What level will you play little epsilon? (1 or more) ");
    }
    while(level < 1);
    int total = randRange(pow(10, level), pow(10, level+1));
    int score = 0;
    while(total!=1)
    {
        cout << "Your score is " << score << "." << endl;
        cout << "The total is " << total << "." << endl;
        cout << "Pick a number that you can divide into " << total << "." << endl;
        int div = getInt(name + ": ");
        if (div == 0)
        {
            cout << "Are you sure you want to quit (y/n)? ";
            string ans;
            cin >> ans;
            if (ans[0] == 'y') return;
            else continue;
        }
        if (div == 1)
        {
            cout << "1 is cheating." << endl;
            cout << "Try again." << endl;
        }
        if (not (total % div == 0))
        {
            cout << div << " is not divisible by " << total << endl;
            cout << "Try again." << endl;
            continue;
        }
        if (div < 0)
        {
            cout << "Smart kid, but no negatives. Sorry." << endl;
            cout << "Try again." << endl;
            continue;
        }
        int newTotal; //temporary variable for the new total until user gets it right
        while(true)
        {
            cout << "Now, what is " << total << "/" << div << "?" << endl;
            newTotal = getInt(name + ": ");
            if (newTotal != total / div)
            {
                cout << "That is wrong, try again." << endl;
            }
            else break;
        }
        total = newTotal;
        score++;
    }
    cout << "That is it. Your score is " << score << ", " << name << "." << endl;
    ifstream file(to_string(level), ios::in);
    int highscore;
    bool newscore = false;
    if (file.is_open())
    {
        file >> highscore;
        cout << "The high score for level " << level << " was " << highscore << endl;
        if (highscore >= score)
        {
            cout << "Sorry, you did not beat it this time." << endl;
        }
        else
        {
            cout << "You got the high score!" << endl;
        }
        file.close();
    }
    else
    {
        cout << "There was no previous high score for level " << level << ", so the high score is yours!" << endl;
        newscore=true;
    }
    if (newscore)
    {
        ofstream newfile(to_string(level), ios::out);
        newfile << score;
        newfile.close();
    }
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
