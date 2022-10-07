//
//  LogDumper.cpp
//
//  This app retrieves all the log messages from the database, along with their timestamps, and outputs them to the console 
//
//  Created by Michael Mendes on 2022-10-03.
//

#include "LogDumper.hpp"

/*
 main() takes in the name of a table in the database as the command line arguments and prints out all messages from the table with their timestamps 
 */
int main(int argc, const char * argv[]) {
    vector<LogMessage> messages;
    string appName = argv[1];
    
    Logger retriever(appName);
    messages = retriever.read_all();
    
    for (LogMessage msg : messages) {
        cout << msg.getTimeStamp() << ":  " << msg.getMessage() << endl;
    }
    return 0;
}

