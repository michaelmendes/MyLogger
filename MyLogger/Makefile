all: generator dumper

generator: LogGenerator.o
	g++ LogGenerator.o -o generator -lsqlite3

dumper: LogDumper.o
	g++ LogDumper.o -o dumper -lsqlite3

LogDumper.o: LogDumper.cpp LogDumper.hpp LogMessage.cpp LogMessage.hpp Logger.cpp Logger.hpp
	g++ -c -std=c++11 LogDumper.cpp

LogGenerator.o: LogGenerator.cpp LogGenerator.hpp LogMessage.cpp LogMessage.hpp Logger.cpp Logger.hpp
	g++ -c -std=c++11 LogGenerator.cpp

