all: 
	g++ -std=c++11 -pipe -O2 -Wall -lboost_regex-mt  main.cpp searchengine.cpp -o words