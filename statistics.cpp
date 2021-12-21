#include "statistics.h"
#include "utils.h"

std::string statistics(bool pausing = false)
{
    std::string msg = "";
    std::string input = "";
    std::vector<std::vector<Word>> words=parse_to_boxes("words.txt");

    // print statistics
    std::system("clear");
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Total number of words: " << words[0].size() << "\n\n";
    for (int i=1; i<=5; i++)
      {
        std::cout << "Words in Box " << i << ": " << words[i].size() << std::endl;
      }
    
    if (pausing)
    {
      std::cout << "\nPress Enter to retun to main menu";
      std::cin.get();
    }
    else
    {
      // do nothing as designed
    }

    return msg;
}