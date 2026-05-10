#include<iostream>
#include<sstream>
#include<unistd.h>
#include<sys/wait.h>
#include<cstring>
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
        print("\n")
        print("tuhin@Fz-Alpha-07:$ ")
        std::string comand;
        std::getline(std::cin,comand);
        if(comand == "exit"){
            print("Hope you enjoyed it\n")
            toStop = true;
            break;
        }
        std::vector<std::string> tokens (tokenizer(comand));
       if(!tokens.empty()){executeCommand(tokens);}
    }
}


void executeCommand(std::vector<std::string> commands){
    std::vector<char*> args = vectorConverter(commands);
    pid_t p = fork();
    if(p<0) {
        perror("Fork failed");
    }
    else if(p ==0) {
        // print("child process"<<getpid()<<std::endl);
        if(execvp(args[0] , args.data()) == -1){
            perror("execution failed");
            exit(1);
        }
        
    }
    else {
    //    print("parent process"<<getpid()<<std::endl);
       wait(NULL);
       for(char* ptr : args){
        free(ptr);
       }
    }
}

std::vector<char*> vectorConverter(const std::vector<std::string>& comands){
    std::vector<char*> ans;
    ans.reserve(comands.size()+1);

    for(const auto& a : comands){
        ans.push_back(strdup(a.c_str()));
    }
    ans.push_back(nullptr);

    return ans;
}