//
//  LogMessage.cpp
//
//  This is a basic class which represents a log message which has been or will be written to a database. 
//
//  Created by Michael Mendes on 2022-10-03.
//

#include "LogMessage.hpp"
using namespace std;

class LogMessage{
private:
    string text, time;
    
public:
    /*
     LogMessage() is the class constructor. It takes in a message and time and stores them
     */
    LogMessage(string newText, string newTime) {
        text = newText;
        time = newTime;
    }
    
    /*
     ~LogMessage() is the destructor of the class
     */
    ~LogMessage() {
        //do nothing
    }
    
    /*
     getMessage() returns the text variable of this object
     */
    string getMessage() {
        return text;
    }
    
    /*
     getTimeStamp() returns the time variable of this object
     */
    string getTimeStamp() {
        return time;
    }
    
};

