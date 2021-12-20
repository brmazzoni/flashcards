#include "dictionnary.h"
#include "utils.h"
#include <iostream>
#include <string>

std::string dictionnary()
{
    std::string msg = "";
    std::string input = "";
    std::vector<Word> words = read_words("words.txt");

    words = sort_words(words);

    std::system("clear");

    // msg area
    std::cout << "\n" << msg << "\n\n";

    // Print Dictionnary
    std::cout << "\nPrinting all words in Dictionnary:\n\n";
    std::cout << "French: English - Info\n\n";

    for (Word word : words)
    {
        std::cout << word.french << ": " << word.english << " - " << word.info << "\n";
    }
    
    while (input != "0")
    {
        std::cout << "\nEnter search pattern or \"0\" to exit: ";
        std::cin >> input;
        std::cout << "\n";
        for (Word word : words)
        {
            // search the pattern in french and english
            bool found_in_french = word.french.find(input) != std::string::npos;
            bool found_in_english = word.english.find(input) != std::string::npos;
            if (found_in_french || found_in_english)
            {
                std::cout << word.french << ": " << word.english << " - " << word.info << "\n";
                found_in_french = 0;
                found_in_english = 0;
            }
            else
            {
                // do nothing as designed
            }
        }
    }
    
    return msg;
}