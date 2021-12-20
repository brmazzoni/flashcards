#include "settings.h"
#include "utils.h"

std::string settings(void)
{
    int selection = -1;
    int length;
    int retries;
    std::string mode;
    std::string system;
    std::string msg = "";

    Settings settings;

    settings = parse_settings("settings");
    
    while(1)
    {
        std::system("clear");
        // msg area
        std::cout << "\n" << msg << "\n";
        // Menu
        std::cout << std::endl;
        std::cout << "Settings:\n";
        std::cout << std::endl;
        std::cout << "1. Change Length (" << settings.length << ")\n";
        std::cout << "2. Change Mode (" << settings.mode << ")\n";
        std::cout << "3. Change System (" << settings.system << ")\n";
        std::cout << "4. Change Retries (" << settings.retries << ")\n";
        std::cout << "5. Reset Boxes\n";
        std::cout << std::endl;
        std::cout << "9. Cancel\n";
        std::cout << "0. Save and Quit\n";
        std::cout << std::endl;
        std::cout << "Selection: ";
        std::cin >> selection;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Flush the buffer
        
        if (selection == 0)
        {
            // TODO: Write settings to file
            std::ofstream file;
            file.open("settings");
            if (file.is_open())
            {
              file << "PRACTICE_LENGTH " << settings.length << std::endl
                   << "MODE " << settings.mode << std::endl
                   << "SYSTEM " << settings.system << std::endl
                   << "RETRIES " << settings.retries;
              file.close();
              msg = "Settings saved!";
            }
            else
            {
              msg = "File error";
            }
            return msg;
        }
        else if (selection == 1)
        {
            selection = -1;
            std::cout << "New Length: ";
            std::cin >> settings.length;
        }
        else if (selection == 2)
        {
            selection = -1;
            std::cout << "New Mode: ";
            std::cin >> settings.mode;
        }
        else if (selection == 3)
        {
            selection = -1;
            std::cout << "New System: ";
            std::cin >> settings.system;
        }
        else if (selection == 4)
        {
            selection = -1;
            std::cout << "New Retries number: ";
            std::cin >> settings.retries;
        }
        else if (selection == 5)
        {
            selection = -1;
            std::vector<Word> words = read_words("words.txt");
            for (int i = 0; i < words.size(); i++)
            {
              words[i].box = 1;
            }
            save_words(words, "words.txt");
            msg =  "Resetting boxes (all words put in box 1)\n";
        }
        else if (selection == 9)
        {
          selection = -1;
          msg = "Settings not saved!";
          return msg;
        }
        else if (selection == -1)
        {
            //empty as designed
        }
        else
        {
            msg = "Error, unhandled input";
        }
    }
}

Settings parse_settings(std::string filename)
{
  Settings settings;
  std::ifstream file;
  
  // init settings to defaults
  settings = {20, "MIXED", "LEITNER", 3};

  file.open(filename);
  if (file.is_open())
  {
    std::string line;
    while (getline(file, line))
    {
        std::vector<std::string> buffer = {};
        buffer = split(line, " ");
        if (buffer[0] == "PRACTICE_LENGTH")
        {
          settings.length = std::stoi(buffer[1]);
        }
        else if (buffer[0] == "MODE")
        {
          settings.mode = buffer[1];
        }
        else if (buffer[0] == "SYSTEM")
        {
          settings.system = buffer[1];
        }
        else if (buffer[0] == "RETRIES")
        {
          settings.retries = std::stoi(buffer[1]);
        }
        else
        {
          std::cout << "Error unhandled setting";
        }
    }
    file.close();
  }
  else
  {
    std::cout << "File Error";
  }
  return settings;
}

void print_settings(Settings settings)
{
  std::cout << "Settings: \n\n";
  std::cout << "Practice length: " << settings.length << std::endl;
  std::cout << "Practice mode: " << settings.mode << std::endl;
  std::cout << "Spaced Repetition System: " << settings.system << std::endl;
  std::cout << "Retries: " << settings.retries << std::endl;
  std::cout << std::endl;
}