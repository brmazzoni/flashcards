#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "utils.h"
#include "practice.h"
#include "settings.h"
#include "statistics.h"
#include "dictionnary.h"


int main()
{
    const std::string VERSION = "0.1";
    std::string msg = "";
    int selection;
    
    // init
    selection = -1;
    srand(time(NULL)); // seed random with time

    while(1)
    {
        std::system("clear");
        // msg area
        std::cout << std::endl;
        std::cout << msg << std::endl << std::endl;
        
        // Welcome msg
        std::cout << std::endl;
        std::cout << "Flashcards! v" << VERSION << "\n";

        // Menu
        std::cout << std::endl;
        std::cout << "1. Practice\n";
        std::cout << "2. Settings\n";
        std::cout << "3. Statistics\n";
        std::cout << "4. Dictionnary\n";
        std::cout << std::endl;
        std::cout << "0. Quit\n";
        std::cout << std::endl;
        std::cout << "Selection: ";
        std::cin >> selection;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Flush the buffer
        
        if (selection == 0)
        {
            std::cout << "Bye!\n\n";
            return 0;
        }
        else if (selection == 1)
        {
            selection = -1;
            msg = practice();
        }
        else if (selection == 2)
        {
            selection = -1;
            msg = settings();
        }
        else if (selection == 3)
        {
            selection = -1;
            msg = statistics();
        }
        else if (selection == 4)
        {
            selection = -1;
            msg = dictionnary();
        }
        else if (selection == -1)
        {
            //empty as designed
        }
        else
        {
            msg = "Error, unhandled input\n";
        }
    }
}

