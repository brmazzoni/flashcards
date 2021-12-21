#include "practice.h"
#include "statistics.h"


std::string practice(void)
{   
    std::string msg = "";
    int random; 
    int toss;
    bool pass;
    std::string choice = "";
    std::string input;

    Settings settings;

    // Create a vector of vectors with:
    //  index 0: words list
    //  index 1: box 1
    //  ...
    //  index 5: box 5
    std::vector<std::vector<Word>> words={{}, {}, {}, {}, {}, {}};

    std::vector<Card> practice;

    settings = parse_settings("settings");

    // load words from file
    words[0] = read_words("words.txt");

    // populate boxes
    for (Word word : words[0])
    {
        if (word.box >= 1 && word.box <= 5)
        {
            words[word.box].push_back(word);
        }
        else
        {
            msg = "Error: box value out of range";
        }
    }

    std::system("clear");
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    statistics(false);
    std::cout << std::endl;
    print_settings(settings);

    // Populating the box vectors
    std::cout << "Preparing test set:\n\n";
    // First Pass:
    for (int i=1; i<=5; i++)
    {
      double ratio = (pow(2, i)-1) / pow(2, i);
      while ( (practice.size() < settings.length * ratio) && (words[i].size() > 0) )
      {
          random = rand() % words[i].size();
          Card q = question(words[i][random], settings.mode);
          
          if (settings.mode == "MIXED")
          {
            int toss = rand() % 2;
            if (toss == 0)
            {
              practice.push_back(q);
            }
            else if (toss == 1)
            {
              practice.push_back(reverse_question(q));
            }
          }
          else
          {
            practice.push_back(q);
          }
          words[i].erase(words[i].begin()+random);
          std::cout << "Drew a word from box " << i << "\n";
      }
    }

    // Second Pass:
    for (int i=1; i<=5; i++)
    {
      while ( (practice.size() < settings.length) && (words[i].size() > 0) )
      {
          random = rand() % words[i].size();
          Card q = question(words[i][random], settings.mode);
          
          if (settings.mode == "MIXED")
          {
            toss = rand() % 2;
            if (toss == 0)
            {
              practice.push_back(q);
            }
            else if (toss == 1)
            {
              practice.push_back(reverse_question(q));
            }
          }
          else
          {
            practice.push_back(q);
          }
          words[i].erase(words[i].begin()+random);
          std::cout << "Drew a word from box " << i << "\n";
      }
    }

    std::cout << "\nNumber of questions in the test set: " << practice.size() << "\n";
    std::cout << "\nReady to start practice!\n";
    std::cout << "Press ENTER to start";
    std::cin.get();

    // Start practice
    while (practice.size() > 0)
    {
        std::system("clear");
        pass = false;
        random = rand() % practice.size();
        card(practice[random].front);
        std::cout << "Guess or type \"?\" to show the answer:\n";
        std::cout << "-> ";
        getline(std::cin, input);
        if (input == "?")
        {
            card(practice[random].back, practice[random].info);
            std::cout << "1. I knew it --- 0. I did no know it\n";
            while (choice != "1" && choice != "0")
            {
              std::cin >> choice;
              if (choice == "1")
              {
                pass = true;
              }
              else if (choice == "0")
              {
                pass = false;
                practice[random].attempts++;
              }
            }
            choice = "";

        }
        else if (evaluate(input,practice[random].back))
        {
            std::cout << "\nCorrect!\n";
            pass = true;
            card(practice[random].back, practice[random].info);
        }
        else
        {
            std::cout << "\nWrong!\nAnswer was:\n";
            card(practice[random].back, practice[random].info);
            pass = false;
            practice[random].attempts++;
        }
        
        // Find word in master list and update box if necessary
        for (int i=0; i <= words[0].size(); i++)
        {
            bool match = words[0][i].id == practice[random].id;
            if (!match)
            {
              continue;
            }
            

            if (pass && words[0][i].box < 5)
            {
                words[0][i].box++;
                practice.erase(practice.begin()+random);
                break;
            }
            else if (pass && words[0][i].box >= 5)
            {
                practice.erase(practice.begin()+random);
                break;
            }
            else if (!pass && (practice[random].attempts >= settings.retries))
            {
                if (settings.system == "LEITNER")
                {
                  words[0][i].box = 1;
                  practice.erase(practice.begin()+random);
                  break;

                }
                else
                {
                  std::cout << "Error, unhandled system\n";
                }
            }
            else
            {
                // do nothing as designed
            }
        }

        
        std::cout << "Press ENTER to continue";
        std::cin.get();
    }

    // write words back to file 
    save_words(words[0], "words.txt");
    msg = "Saved progress!";
    return msg;
}

bool evaluate(std::string input, std::string answer)
{
  std::vector<std::string> answers = split(answer, "/");
  for (std::string answer : answers)
  {
    if (input == answer)
    {
      return true;
    }
  }
  return false;
}