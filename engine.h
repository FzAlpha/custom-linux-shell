#include<string>
#include<vector>


void looper();
std::vector<std::string> tokenizer(std::string);
void executeCommand(std::vector<std::string> comands);
std::vector<char*> vectorConverter(const std::vector<std::string>& comands);
void executeCustomDefinedFunctions(std::vector<char*>& args);
bool isUserDefinedFunction(std::vector<std::string>& commands);
void execute_cd_command(const std::vector<char*>& args);
std::string printCurrentWorkingDirectory();
void signalShieldCntrlC(int signalNumber);
std::string extractRedirection(std::vector<std::string>& commands);
