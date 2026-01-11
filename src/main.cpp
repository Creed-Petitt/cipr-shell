#include "Core/Core.h"
#include <iostream>

int main(const int argc, char* argv[]) {
    Core core;
    core.loadConfig();

    if (argc > 2) {
        std::cout << "Usage: cipr [script]" << std::endl;
        return 64;
    } if (argc == 2) {
        core.runFile(argv[1]);
    } else {
        core.runPrompt();
    }
    return 0;
}