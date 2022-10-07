/*
 Logger.cpp
 
 When this class is called by an app, it takes the name of the app, opens a database called "3307Assign.db" (or creates it if it doesn't exist yet) and constructs a table with the same name as the app. The app can then use this class to write timestamped messages to the log or retrieve all messages written in the log as a LogMessage object.

 Created by Michael Mendes on 2022-10-02.

*/
#include "Logger.hpp"
using namespace std;

class Logger {
private:
    const string dBFile = "3307Assign.db";
    string appName;
    sqlite3* dBPtr;
    
    /*
     timeGetter() is a helper function that returns the current time to be used for logging messages
     */
    string timeGetter() {
        chrono::system_clock::time_point now = chrono::system_clock::now();
        time_t time = chrono::system_clock::to_time_t(now);
        stringstream timeStamp;
        timeStamp << put_time(localtime(&time), "%Y-%m-%d %X");
        string timeString = timeStamp.str();
        return timeString;
    }
        
    /*
     createDB() is a function that takes in the name of a database to create, creates the database if it doesn't already exist, and returns a pointer to the database.
     */
    sqlite3* createDB(string file) {
        sqlite3* dBPtr;
        int exit;
        exit = sqlite3_open(file.c_str(), &dBPtr);
        if (exit != SQLITE_OK) {
            cerr << "Could not create database." << endl;
            sqlite3_close(dBPtr);
        }
        return dBPtr;
    }
    
    /*
     createTable() is a function that takes in a pointer to the database and the name of the app, and creates a table in the database with the name of the app, if it doesn't already exist. It returns SQLITE_OK if it was created succesfully.
     */
    int createTable(sqlite3* dBPtr, string appName) {
        string sql = "CREATE TABLE IF NOT EXISTS " + appName + " (timestamp varchar(255), message varchar(255));";
        
        int exit;
        char* errorMessage;
        exit = sqlite3_exec(dBPtr, sql.c_str(), NULL, 0, &errorMessage);
        
        return exit;
    }
    
public:
    /*
     Logger() is the constructor of the class. It takes in the name of the app that is calling it, and calls createDB() and createTable() to setup the database and table.
     */
    Logger(string name) {
        appName = name;
        
        dBPtr = createDB(dBFile);
        
        int createdTable = createTable(dBPtr, appName);
        
        if (createdTable != SQLITE_OK) {
            cerr << "Table could not be created." << endl;
        }
        else {
            cout << "Table was successfully created." << endl;
        }
    }
    
    /*
     ~Logger() is the class destructor. It closes the database.
     */
    ~Logger() {
        sqlite3_close(dBPtr);
        
    }
    
    /*
     write() is a function that takes in string text, calls the timerGetter() method to retrieve the current time, and inserts the text into the table along with the timestamp
     */
    void write(string message) {
        string time = timeGetter();
        
        string query = "insert into " + appName + " values (\"" + time + "\", \"" + message + "\");";
        
        int exit;
        char* errorMessage;
        exit = sqlite3_exec(dBPtr, query.c_str(), NULL, 0, &errorMessage);
        
        if (exit != SQLITE_OK) {
            cerr << "Could not write to table. " << errorMessage << endl;
        }
        else {
            cout << "Succesfully wrote to table." << endl;
        }
        
    }
    
    /*
     read_all() is a function that retrieves all the rows from the table in the database, stores the messages and timestamps in a LogMessage object, and returns these objects in a LogMessage vector 
     */
    vector<LogMessage> read_all() {
        string text;
        string time;
        vector<LogMessage> allMessages;
        sqlite3_stmt* statement;
        
        string query = "select * from " + appName;
        
        int code;
        code = sqlite3_prepare_v2(dBPtr, query.c_str(), -1, &statement, NULL);
        
        if (code != SQLITE_OK) {
            cout << "Values not retrieved" << endl;
        }
        
        code = sqlite3_step(statement);
        while(code != SQLITE_DONE) {
            time = (const char*)sqlite3_column_text(statement, 0);
            text = (const char*)sqlite3_column_text(statement, 1);
            
            LogMessage newMessage(text, time);
            allMessages.push_back(newMessage);
            code = sqlite3_step(statement);
        }
        
        sqlite3_finalize(statement);
        
        return allMessages;
    }
    
};


