// main.cpp
// Application entry point.

#include "Core.h"

int main(void)
{
    try {
        CG::Core core;
        core.run();
    } catch (std::string err) {
        std::cerr << "Exception: " << err << std::endl;
    }
    return 0;
}