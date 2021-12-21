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

void print(std::vector<Card> cards)
{
    for (Card card : cards)
    {
        std::cout << card.front << "\n";
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

    return {std::stoi(buffer[0]), buffer[1], buffer[2], buffer[3], std::stoi(buffer[4])};
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
            file << word.id << ';' << word.french << ';' << word.english << ';' << word.info << ';' << word.box << std::endl;
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
    card.id = word.id;
    card.info = word.info;
    card.attempts = 0;
    if (mode == "ENGLISH_TO_FRENCH" || mode == "MIXED")
    {
        card.front = word.english;
        card.back = word.french;
        
    }
    else if (mode == "FRENCH_TO_ENGLISH")
    {
    card.front = word.french;
    card.back = word.english;
    }
    else
    {
        card = {-1, "--- Error ---", "--- Error ---", "--- Error ---", -1};
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

std::vector<Word> sort_words(std::vector<Word> words)
{
    // bubble sorting
    bool sorted = false;
    while (sorted == false)
    {
        sorted = true;
        for (int i=0; i < words.size() - 1; i++)
        {
            if (remove_accents(words[i].french).compare(remove_accents(words[i+1].french)) >= 0)
            {
                Word temp = words[i];
                words[i] = words[i+1];
                words[i+1] = temp;
                sorted = false;
            }
        }
    }
    return words;
}

std::string remove_accents(std::string str)
{
    str = remove_accent(str, "é", "e");
    str = remove_accent(str, "è", "e");
    str = remove_accent(str, "ê", "e");
    str = remove_accent(str, "à", "a");
    str = remove_accent(str, "ù", "u");
    str = remove_accent(str, "î", "i");
    return str;
}

std::string remove_accent(std::string str, std::string c, std::string r)
{
    size_t pos;
    while((pos = str.find(c)) != std::string::npos)
    {
        str.replace(pos, 2, r);
    }
    return str;
}

