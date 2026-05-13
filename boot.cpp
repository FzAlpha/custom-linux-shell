#include <cstdlib>
#include <iostream>

int main() {
    std::cout << "Booting NovaShell in a new window...\n";
    
    
    int result = system("wt.exe -p \"Nova\" wsl.exe --exec ./novashell");
    
    if (result != 0) {
        std::cerr << "Failed to open new terminal. Trying fallback...\n";
        system("cmd.exe /c start wsl.exe ./novashell");
    }
    
    return 0;
}