#ifndef UTILS
#define UTILS

#include <iostream>
#include <string>
#include <vector>
#include <fstream>



// structs definitions go here (if any)
struct Word
{
    std::string french;
    std::string english;
    std::string info;
    int box;
};

struct Card
{
  std::string front;
  std::string back;
  std::string info;
  int attempts;
};


void print(Word word);
void print(std::vector<Word> words);

std::vector<std::string> split(std::string line, std::string delimiter);

Word read_word(std::string line);

void card(std::string text);
void card(std::string text, std::string info);

std::vector<Word> read_words(std::string filename);

void save_words(std::vector<Word> words, std::string filename);

Card question(Word word, std::string mode);

Card reverse_question(Card card);

std::vector<std::vector<Word>> parse_to_boxes(std::string filename);


#endif