//
//  LogGenerator.cpp
//
//  This app takes in strings as command line arguments and then randomly loops through those strings and writes them to the database
//
//  Created by Michael Mendes on 2022-10-03.
//

#include "LogGenerator.hpp"
using namespace std;

/*
 nameFinder() takes in a string and returns the last part of the string after the last "/"
 */
string nameFinder(string path) {
    string delimiter = "/";
    size_t found = path.find(delimiter);
    
    while (found != string::npos){
        path = path.substr(found+1, path.length()-1);
        found = path.find(delimiter);
    }
    return path;
}

/*
 handleSignal() outputs a message to the console when the user interrupts and ends the program 
 */
void handleSignal(int signal) {
    cout << "\nProcess interrupted." << endl;
    exit(signal);
}

/*
 main() is the main function of this app. It takes in string messages as command line arguments, randomly loops through them, and writes them to a table with the same name as this app, until the user interrupts the process
 */
int main(int argc, const char * argv[]) {
    signal(SIGINT, handleSignal);
    
    if (argc == 1) {
        cout << "No messages provided." << endl;
        return 0;
    }
    string appName = nameFinder(argv[0]);
    
    Logger newLogger(appName);
    
    srand(time(NULL));
    while (1) {
        // randomly select a message from command line args
        int num1 = rand() % (argc-1);
        newLogger.write(argv[num1+1]);
        
        //sleep for anywhere between 1s and 10s
        int num2 = (rand() % 9000001)+1000000;
        usleep(num2);
    }
    
    return 0;
    
}

