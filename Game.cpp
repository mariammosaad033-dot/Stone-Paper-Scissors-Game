#include <iostream>
#include<cstdlib>
#include <ctime>
using namespace std;

enum enGameChoice{Paper=1,Stone=2, Scissors =3};
enum enWinner{Player=1,Computer=2,Draw=3};

struct stGameResult
{
    short NumberOfRound = 0;
    short Player1WinsTimes = 0;
    short ComputerWinsTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string GameWinnerName ;
};
struct stRoundInfo
{
    short RoundNumber;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}
enGameChoice GetComputerChoice()
{
    return enGameChoice(RandomNumber(1, 3));
}

enGameChoice ReadPlayerChoice()
{
    short Choice;
    do
    {
        cout << "Your Choice [1]:Paper , [2]:Stone , [3]:Scissors ?";
        cin >> Choice;
    } while (Choice < 1 || Choice>3);
    return enGameChoice(Choice);
}

int ReadNumberOfRound()
{
    int NumberOfRound;
    do
    {
        cout << "Please enter the number of Round From 1 To 10 ? ";
        cin >> NumberOfRound;
    } while (NumberOfRound < 1 || NumberOfRound>10);
    return NumberOfRound;
}

enWinner WhoWinRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.ComputerChoice == RoundInfo.PlayerChoice)
    {
        return enWinner::Draw;
    }
    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
            return enWinner::Computer;
        break;
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
            return enWinner::Computer;
        break;
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
            return enWinner::Computer;
        break;
    }
    return enWinner::Player;
}

enWinner WhoWinTheGame(int Player1WinsTimes, int ComputerWinsTimes)
{
    if (Player1WinsTimes > ComputerWinsTimes)
        return enWinner::Player;

    else if (ComputerWinsTimes > Player1WinsTimes)
        return enWinner::Computer;

    else
       return  enWinner::Draw;
}

string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = {"Player","Computer","Draw"};
    return arrWinnerName[Winner - 1];
}
string ChoiceName(enGameChoice GameChoice)
{
    string arrWinnerChoice[3] = { "Paper","Stone","Scissors" };
    return arrWinnerChoice[GameChoice - 1];
}

void SetScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        break;
    case enWinner::Draw:
        system("color 6F");
        break;
    }
}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void ShowGameOverScreen()
{
    cout << "\t\t-----------------------------------------------------\n\n";
    cout << "\t\t            +++ G a m e  O v e r +++\n";
    cout << "\t\t-----------------------------------------------------\n\n";
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
    cout << "\n---------Round[" << RoundInfo.RoundNumber << "]--------------\n";
    cout << "PLayer Choice : " <<ChoiceName( RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice : " <<ChoiceName( RoundInfo.ComputerChoice )<< endl;
    cout << "Round Winner : " <<RoundInfo.WinnerName << endl;
    cout << "----------------------------------------------------------\n";
  
}

void PrintGameResult(stGameResult GameResult)
{
    cout << "\t\t-----------------Game Result------------------\n";
    cout << "\t\tGames Round : " << GameResult.NumberOfRound << endl;
    cout << "\t\tPlayer1WinTimes  : " << GameResult.Player1WinsTimes << endl;
    cout << "\t\tComputer WinTimes : " << GameResult.ComputerWinsTimes << endl;
    cout << "\t\tDraw Times  : " << GameResult.DrawTimes << endl;
    cout << "\t\tWinner is : " << GameResult.GameWinnerName << endl;
}

stGameResult FillGameResult(short NumberOfRound, short Player1WinsTimes, short ComputerWinsTimes, short DrawTimes)
{
    stGameResult GameResult;
    GameResult.NumberOfRound = NumberOfRound;
    GameResult.Player1WinsTimes = Player1WinsTimes;
    GameResult.ComputerWinsTimes = ComputerWinsTimes;
    GameResult.DrawTimes = DrawTimes;
    GameResult.GameWinner = WhoWinTheGame(Player1WinsTimes, ComputerWinsTimes);
    GameResult.GameWinnerName = WinnerName(GameResult.GameWinner);
    return GameResult;
}

stGameResult PlayGame(short NumberOfRound)
{
    stRoundInfo RoundInfo;

    short Player1WinsTimes = 0, ComputerWinsTimes = 0, DrawTimes = 0;

    for (int GameRound = 1;GameRound <= NumberOfRound;GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins  :  \n\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.Winner = WhoWinRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinsTimes++;

        else if (RoundInfo.Winner == enWinner::Player)
            Player1WinsTimes++;

        else
            DrawTimes++;


        PrintRoundResult(RoundInfo);
        SetScreenColor(RoundInfo.Winner);
    }
    return FillGameResult(NumberOfRound, Player1WinsTimes, ComputerWinsTimes, DrawTimes);
}

void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        stGameResult GameResult = PlayGame(ReadNumberOfRound());
        ShowGameOverScreen();
        PrintGameResult(GameResult);
        cout << "\nDo You Want to play agan ('Y' or 'N') ? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}
int main()
{
    srand((unsigned)time(NULL));
    StartGame();
}
