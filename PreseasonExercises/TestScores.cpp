#include <iostream>
using namespace std;

int main()
{
    int numOfTests, score;
    cout << "Enter how many test scores there are: ";
    cin >> numOfTests; // gets the size of the array from the user
    
    double testScores[numOfTests]; // declares the array as the size of the int the user put
    cout << "There are " << numOfTests << " tests." << endl;
    
    for (int i = 0; i < numOfTests; i++) // for loop to fill the array with values
    {
        cout << "Enter the score for test " << (i+1) << ": "; // adds 1 so that it doesn't say test 0
        cin >> testScores[i]; // fills the array at the index of the counter with user input
    }
    
    cout << "Which score would you like to see? ";
    cin >> score;
    cout << testScores[score-1]; // subtracts 1 to account for index starting at 0
    
    return 0;    
}
