#include <iostream>
#include <string>
#include <cstdlib>    // Include cstdlib for rand() and srand() functions.
#include <ctime>      // Include ctime for the time() function, used for seeding the random number generator.
#define GREEN_BG  "\033[42m"
#define RED_BG    "\033[41m"
#define YELLOW_BG "\033[43m"


using namespace std;

int UserCount =0;
    int computerCount =0;
    int NoWinnersCount = 0;

enum enmChoices{rock = 1, paper = 2, scissors = 3};

int ReadUserNumber(string txt){
    cout << txt;
    int number;
    do{
        cin >> number;
    }while(number < 1);
    return number;
}

int RandomNumber(int From, int To)
{
    // Calculate a random number in the range [From, To]:
    // rand() % (To - From + 1) gives a value between 0 and (To - From),
    // then adding From shifts this range to [From, To].
    int randNum = rand() % (To - From + 1) + From;
    return randNum;  // Return the generated random number.
}

int UsersChoice(){
    int ChoiceNum;
    
    do{
        ChoiceNum = ReadUserNumber("\nWhat is your choice: [1]:rock [2]:paper [3]:scissors ?? ");
    }while(ChoiceNum != 1 && ChoiceNum != 2 && ChoiceNum != 3);
    
    return ChoiceNum;
}

int ComputersChoice(){
    int ComChoice = RandomNumber(1,3);
    cout << "Computer choice is: " << enmChoices(ComChoice) << endl;
    return ComChoice;
}

// UC user choice, CC computer choice
void RoundResult(int UC , int CC, int RoundCountI){
    switch(UC){
        case enmChoices::rock:
        {
        if(CC == scissors){
            ++UserCount;
            cout << "\033[42m";
            break;
        }else if(CC == rock){
            ++NoWinnersCount;
            cout << YELLOW_BG;
            break;
        }else{
            ++computerCount;
            
            cout << RED_BG;
            break;
        }
        }
        
        //
        
        case enmChoices::paper:
        {
        if(CC == scissors){
            ++computerCount;
            cout << RED_BG;
            break;
        }else if(CC == rock){
            ++UserCount;
            cout << "\033[42m";
            break;
        }else{
            ++NoWinnersCount;
            cout << YELLOW_BG;
            break;
        }
        }
        
        //
        
        case enmChoices::scissors:
        {
        if(CC == scissors){
            ++NoWinnersCount;
            cout << YELLOW_BG;
            break;
        }else if(CC == rock){
            ++computerCount;
            cout << RED_BG;
            break;
        }else{
            ++UserCount;
            cout << "\033[42m";
            break;
        }
        }
    }
    
    cout << "\nPlayer Choice: " << enmChoices(UC);
}

bool PlayMore(){
    char letter;
    do{
        cout << "\nDo you want to play again: yes[y]/no[n]?? ";
        cin >> letter;
    }while(letter != 'y' && letter != 'n');
    
    if(letter == 'y'){
        return true;
    }else{
        return false;
    }
}

void StartGame(int Rounds_Number){
    for(int i=1; i<=Rounds_Number; i++){
        cout << "Round #" << i << ": "; 
       int UserChoice = UsersChoice();
    int ComputerChoice = ComputersChoice();
    RoundResult(UserChoice, ComputerChoice, i);
    }
}

void ResultDisplay(int Rounds_Number){
    cout << "\n\n\t---------------------RESULT MENU----------------------\n\nRound numbers: " << Rounds_Number
    << "\nUser Wins: " << UserCount << "\nComputer Wins: " << computerCount
    << "\nDraw: " << NoWinnersCount << "\n";
    if(UserCount > computerCount){
        cout << "Final winner: Player"; 
    }else if(computerCount > UserCount){
        cout << "Final winner: Computer";
    }else{
        cout << "Final Winner: draw";
    }
    cout << "\n----------------------------------------------------\n";
}

void RestartGame(){
    UserCount =0;
    computerCount=0;
    NoWinnersCount=0;
    
    if(PlayMore()){
        int Rounds_Number = ReadUserNumber("How many round(s) you want to play: ");
        StartGame(Rounds_Number);
        ResultDisplay(Rounds_Number);
    }else{
        cout << "\n\nThanks for playing\n";
    }
    
}

int main()
{
    
    // Seed the random number generator with the current time.
    // This ensures that the sequence of random numbers is different on each run.
    srand((unsigned)time(NULL));
    
    int Rounds_Number = ReadUserNumber("How many round(s) you want to play: ");
    
    StartGame(Rounds_Number);
    ResultDisplay(Rounds_Number);
    
    RestartGame();
    
    

    return 0;
}