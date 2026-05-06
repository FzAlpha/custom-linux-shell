#include<iostream>
#include<sstream>
#include<unistd.h>
#include<sys/wait.h>
#include "engine.h"


#define print(x) std::cout<<x;


std::vector<std::string> tokenizer(std::string comand){
    std::stringstream ss(comand);
    std::string token;
    std::vector<std::string> tokens;
    while(ss>>token){
        tokens.push_back(token);
    }
    return tokens;  
}

void looper(){
    bool toStop = false;
    while(!toStop){
        print("\n");
        print("tuhin@Fz-Alpha-07:$ ");
        std::string comand;
        std::getline(std::cin,comand);
        if(comand == "exit"){toStop = true;}
        std::vector<std::string> tokens (tokenizer(comand));
       if(!tokens.empty()){executeComand(tokens);}
    }
}


void executeComand(std::vector<std::string> comands){
    pid_t p = fork();
    if(p<0) {
        print("error");
    }
    else if(p ==0) {
        print("child process"<<getpid()<<std::endl);
        exit(0);
    }
    else {
       print("parent process"<<getpid()<<std::endl);
       wait(NULL);
    }
}