#include "utils.h"

void print(Word word)
{
    std::cout << word.french << "\t" << word.english << "\t" << word.box << std::endl;
}

void print(std::vector<Word> words)
{
    for (Word word : words)
    {
        print(word);
    }
}

void card(std::string text)
{
    std::cout << "\n\n";
    std::cout << "------------------\n";
    std::cout << "                  \n";
    std::cout << "    " << text << "\n";
    std::cout << "                  \n";
    std::cout << "------------------\n";
    std::cout << "\n\n";
}

void card(std::string text, std::string info)
{
    std::cout << "\n\n";
    std::cout << "------------------\n";
    std::cout << "                  \n";
    std::cout << "    " << text << "\n";
    std::cout << "    " << info << "\n";
    std::cout << "                  \n";
    std::cout << "------------------\n";
    std::cout << "\n\n";
}

std::vector<std::string> split(std::string line, std::string delimiter)
{
  int start = 0;
  int end = line.find(delimiter);
  std::vector<std::string> list;

  while (end != -1)
  {
    list.push_back(line.substr(start, end-start));
    start = end + delimiter.size();
    end = line.find(delimiter, start);
  }
  list.push_back(line.substr(start, end-start));
  return list;
}

Word read_word(std::string line)
{
    const std::string DELIMITER = ";";
    std::vector<std::string> buffer;
    buffer = split(line, DELIMITER);

    return {buffer[0], buffer[1], buffer[2], std::stoi(buffer[3])};
}

std::vector<Word> read_words(std::string filename)
{
    std::ifstream file;
    std::vector<Word> words;

    file.open(filename);
    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            Word word;
            word = read_word(line);
            words.push_back(word);
        }
    }
    else
    {
        std::cout << "File error during read.\n";
        return {};
    }
    file.close();
    return words;
}

void save_words(std::vector<Word> words, std::string filename)
{
    std::ofstream file;
    
    file.open(filename);
    if (file.is_open())
    {
        for (Word word : words)
        {
            file << word.french << ';' << word.english << ';' << word.info << ';' << word.box << std::endl;
        }
    }
    else
    {
        std::cout << "File error during save.\n";
    }
    file.close();
}

Card question(Word word, std::string mode)
{
  Card card;
  if (mode == "ENGLISH_TO_FRENCH" || mode == "MIXED")
  {
    card.front = word.english;
    card.back = word.french;
    card.info = word.info;
    card.attempts = 0;
  }
  else if (mode == "FRENCH_TO_ENGLISH")
  {
    card.front = word.french;
    card.back = word.english;
    card.info = word.info;
    card.attempts = 0;
  }
  else
  {
    card = {"--- Error ---", "--- Error ---", "--- Error ---", -1};
  }
  return card;
}

Card reverse_question(Card card)
{
  Card reversed_card;
  reversed_card.front = card.back;
  reversed_card.back = card.front;
  reversed_card.info = card.info;

  return reversed_card;
}


std::vector<std::vector<Word>> parse_to_boxes(std::string filename)
{
    std::string msg = "";
    std::vector<std::vector<Word>> words={{}, {}, {}, {}, {}, {}};

    // load words from file
    words[0] = read_words(filename);

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
    return words;
}

