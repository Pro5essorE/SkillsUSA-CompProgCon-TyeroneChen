// Tyerone Chen 
// Last Edit: 4/2/2025
// Program - Fibonacci Sequences - Terminal

#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;


// Fibonaccie Function
void fibonacciGenerator(int count, int index, vector<long> &return_vector) {
    if (index == count) {
        return; // End Recursion
    }

    if (index - 1 >= 0) { // Checks index to see if there is ONE accesable value behind it
        if (index - 2 >= 0) { // Checks index to see if there are TWO accesable value behind it
            return_vector.push_back(return_vector[index - 1] + return_vector[index -2]); // Grabs the two previous numbers, then gets the sum and push that back to the list
            index++;
            fibonacciGenerator(count, index, return_vector);
        }
        else {
            return_vector.push_back(1); // Push back 1 as that will always be the second value
            index++;
            fibonacciGenerator(count, index, return_vector); // Recall function
        }
    }
    else {
        return_vector.push_back(0); // Pushes back 0 as that will always be the first value
        index++;
        fibonacciGenerator(count, index, return_vector); // Recall function
    }
}

// Quick Help Print out so it doesnt clog the code with a bunch of couts
void printHelp(){
    cout << endl << "--help : Print this Help" << endl;
    cout << endl << "--count|-c : Calculate to this many places. IE 0, 1, 2, 3, 4, 5 would be the result of -c 6" << endl;
    cout << endl << "--one-line : Print all the numbers on one line, sperated by commas. Without this option, each number in the sequence on a new line" << endl;
    cout << endl << "--numbering : Preface each number in the sequence with it's place: IE for, -c 6 -numbering -one-line, you;d get this , 1:0, 2:1, 3:1, 4:2, 5:3, 6:5, where the first number is the count and the seconds is the Fibonacci Sequence" << endl;
    cout << endl << "--last-only : Only print the last number" << endl;
    cout << endl << "-1 : Exits Program" << endl;
}


int extractNum(string input_string) {
    string string_int_holder;
    for (char c : input_string) { // Checks to see if the char is a digit in the string
        if (isdigit(c)) {
            string_int_holder += c; // Holds that num
        }
    }
    return stoi(string_int_holder); // Returns all nums unadded
}


int main()
{
    // Variable Initialization / Definemnt
    vector<long> fib_vector = {};
    string user_input;
    string display_fib_method;
    int index = 0;
    int current_num = 0;

    while (user_input != "-1") {
        cout << endl; // For formatting to look nice
        getline(cin, user_input);

        if (user_input.find("--help") != string::npos) { // Checks to see if the inputted command includes --help
            printHelp();
        }
        else if(user_input.find("--count") != string::npos || user_input.find("-c") != string::npos) { // Conditional check when -c / --count is inputted;
            // Resets fib function parameters
            index = 0;
            current_num = extractNum(user_input);
            fib_vector.clear();
            fibonacciGenerator(current_num, index, fib_vector);
            if (string::npos && user_input.find("--last-only") != string::npos) {
                // Checks if --numbering, --one-line, & --last-only is inputted
                if (user_input.find("--numbering") != string::npos && string::npos && user_input.find("--one-line") != string::npos) {
                    cout << to_string(fib_vector.size()) << ":" << fib_vector.back(); // Prints out last value with also the position it is at
                }
                // Checks if --numbering, & --last-only is inputted
                else if (user_input.find("--numbering") != string::npos) {
                    cout << to_string(fib_vector.size()) << ":" << fib_vector.back(); // Prints out last value with also the position it is at
                }
                // Checks if --one-line, & --last-only is inputted
                else if (user_input.find("--one-line") != string::npos) {
                    cout << fib_vector.back(); // This is basically the same as --last-only, --one-line doesnt change much
                }
                // Checks if --last-only is inputted
                else {
                    cout << fib_vector.back(); // Returns out only ther last value
                }
            }

            else if (user_input.find("--numbering") != string::npos) {
                int sub_index = 1;
                if (string::npos && user_input.find("--one-line") != string::npos) {
                    // Checks if --one-line and --numbering was inputed
                    for (int num : fib_vector)
                    {
                        cout << sub_index << ":" << to_string(num) << ", ";
                        sub_index++;
                    }
                }
                else {
                    // Checks if --numbering was inputed
                    for (int num : fib_vector)
                    {
                        cout << sub_index << ":" << to_string(num) << endl;
                        sub_index++;
                    }
                }
            }

            else if (string::npos && user_input.find("--one-line") != string::npos) {
                for (int num : fib_vector)
                {
                    cout << to_string(num) + ", ";
                }
            }
            else {
                for (int num : fib_vector)
                {
                    cout << to_string(num) << endl;
                }
            }
            cout << endl; // For nice formatting :]
        }
        else {
            cout << endl << "Unknown Command Inputted type --help for options" << endl;
        }
    }

}


