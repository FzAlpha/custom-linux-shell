#include<iostream>
#include<sstream>
#include<unistd.h>
#include<sys/wait.h>
#include<cstring>
#include<csignal>
#include<limits.h>
#include<fcntl.h>
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
    std::signal(SIGINT , signalShieldCntrlC);
    while(!toStop){
        print("\n")
        print("\033[32mtuhin@Fz-Alpha-07:\033[34m"<< printCurrentWorkingDirectory()<<"\033[33m$\033[0m ")
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
    std::string targetfile = "";
    targetfile = extractRedirection(commands);
    bool isUserDefined = isUserDefinedFunction(commands);
    std::vector<char*> args = vectorConverter(commands);
    if(!isUserDefined){
        
        pid_t p = fork();
    
        if(p<0) {
           perror("Fork failed");
        }
        else if(p ==0) {
           // print("child process"<<getpid()<<std::endl);
           std::signal(SIGINT , SIG_DFL);
           if(targetfile != ""){
            int file_d= open(targetfile.c_str() ,O_WRONLY | O_CREAT | O_TRUNC , 0644);
            if(file_d<0){
                perror("novashell redirection error");

                exit(1);
            }
            dup2(file_d ,1);
            close(file_d);

            
           }
            
            if(execvp(args[0] , args.data()) == -1){
                perror("execution failed");
                exit(1);
            }
        }
        else {
       // print("parent process"<<getpid()<<std::endl);
            wait(NULL);
            for(char* ptr : args){
                free(ptr);
            }
        }
    }else{
        executeCustomDefinedFunctions(args);
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

bool isUserDefinedFunction(std::vector<std::string>& commands){
    if(!commands.empty() && commands[0] == "cd"){
        return true;
    }
    return false;
}

void executeCustomDefinedFunctions(std::vector<char*>& args){
    if(std::string(args[0]) == "cd"){
        execute_cd_command(args);
    }
    
}

void execute_cd_command(const std::vector<char*>& args){


    bool physical = false; // Default is usually logical (-L)
    const char* path = nullptr;

    // 1. Parse arguments for flags and the target path
    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i][0] == '-') {
            // Handle combined flags like -LP or -PL
            for (size_t j = 1; args[i][j] != '\0'; ++j) {
                if (args[i][j] == 'P') physical = true;
                else if (args[i][j] == 'L') physical = false;
                else {
                    std::cerr << "cd: invalid option: -" << args[i][j] << std::endl;
                    return;
                }
            }
        } else {
            // First non-flag argument is the path
            path = args[i];
            break; 
        }
    }

    // 2. Handle default 'cd' (no path provided) -> go to HOME
    if (!path) {
        path = getenv("HOME");
        if (!path) {
            std::cerr << "cd: HOME not set" << std::endl;
            return;
        }
    }

    // 3. Resolve path if -P is active
    char resolved_path[PATH_MAX];
    if (physical) {
        if (realpath(path, resolved_path) == nullptr) {
            perror("cd");
            return;
        }
        path = resolved_path;
    }

    // 4. Execute the directory change
    if (chdir(path) != 0) {
        perror("cd");
    } else {
        // Optional: Update PWD environment variable after change
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != nullptr) {
            setenv("PWD", cwd, 1);
        }
    }


}

std::string printCurrentWorkingDirectory(){
    char path[PATH_MAX];
    if(getcwd(path ,sizeof(path)) != nullptr){
        return path;
    }else{
        perror("directory error");
        return "1";
    }
    return "0";
}

void signalShieldCntrlC(int signalNumber){
    if(signalNumber == SIGINT){
        print("\n")
        print("\033[32mtuhin@Fz-Alpha-07:\033[34m"<< printCurrentWorkingDirectory()<<"\033[33m$\033[0m ")
        std::cout.flush();
    }
}

std::string extractRedirection(std::vector<std::string>& commands){
    
    for(int i = 0;i<commands.size() ; i++){
        if(commands[i] == ">"){
            
            if(i+1 < commands.size()){
                std::string filename = commands[i+1];
                commands.erase(commands.begin()+i, commands.begin() +i+2);
                return filename;
            }else{
                std::cerr<<"synyax error unexpected file name after '>'\n";
                return "";
            }   
        }
    }
    return "";
}
