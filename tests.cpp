#include <iostream>
#include <fstream>
#include <cstdio>
#include "utils.h"
#include "utils.cpp"
#include "settings.h"
#include "settings.cpp"

struct TestMetrics
{
  int executed;
  int pass;
  int fail;
};

void assrt(bool res, std::string description, TestMetrics &metrics)
{
    metrics.executed++;
    if (res)
    {
      std::cout << "PASS " << description << "\n";
      metrics.pass++;
    }
    else
    {
      std::cout << "FAIL " << description << "\n";
      metrics.fail++;
    }
}


void test_split(TestMetrics &metrics)
{
  {
    // Description
    std::string test_description = "TC_001: Test split with a basic delimiter";
    // Init inputs
    std::string s = "one;two;three";
    std::string delimiter = ";";

    // Compute result
    bool c1 = split(s, delimiter)[0] == "one";
    bool c2 = split(s, delimiter)[1] == "two";
    bool c3 = split(s, delimiter)[2] == "three";
    bool res = c1 && c2 && c3;

    // Display result
    assrt(res, test_description, metrics);
  }
  {
    // Description
    std::string test_description = "TC_002: Test split with a 2 characters delimiter";
    // Init inputs
    std::string s = "one::two::three";
    std::string delimiter = "::";

    // Compute result
    bool c1 = split(s, delimiter)[0] == "one";
    bool c2 = split(s, delimiter)[1] == "two";
    bool c3 = split(s, delimiter)[2] == "three";
    bool res = c1 && c2 && c3;

    // Display result
    assrt(res, test_description, metrics);
  }
  {
    // Description
    std::string test_description = "TC_003: Test split with a space delimiter";
    // Init inputs
    std::string s = "one two three";
    std::string delimiter = " ";

    // Compute result
    bool c1 = split(s, delimiter)[0] == "one";
    bool c2 = split(s, delimiter)[1] == "two";
    bool c3 = split(s, delimiter)[2] == "three";
    bool res = c1 && c2 && c3;

    // Display result
    assrt(res, test_description, metrics);
  }
}

void test_read_word(TestMetrics &metrics)
{
  {
    // Description
    std::string test_description = "TC_004: Test read word function";
    // Init inputs
    std::string line = "1;tester;to test;v.; 3";
    // Init Expected result (if necessary)

    // Compute result
    bool c0 = read_word(line).id == 1;
    bool c1 = read_word(line).french == "tester";
    bool c2 = read_word(line).english == "to test";
    bool c3 = read_word(line).info == "v.";
    bool c4 = read_word(line).box == 3;
    bool res = c0 && c1 && c2 && c3 && c4;

    // Display result
    assrt(res, test_description, metrics);
  }
}

void test_read_words(TestMetrics &metrics)
{
  {
    // Description
    std::string test_description = "TC_005: Test read words function correctly reads a sample file";
    // Init inputs
    std::ofstream testfile;
    std::ifstream file;

    testfile.open("testfile");
    testfile << "1;tester1;to test1;v.;1\n2;tester2;to test2;v.;2";
    testfile.close();

    // Compute result
    std::vector<Word> words = read_words("testfile");
    file.close();
    remove("testfile"); // cleanup

    bool c0 = words[0].id == 1;
    bool c1 = words[0].french == "tester1";
    bool c2 = words[0].english == "to test1";
    bool c3 = words[0].info == "v.";
    bool c4 = words[0].box == 1;
    bool c5 = words[1].id == 2;
    bool c6 = words[1].french == "tester2";
    bool c7 = words[1].english == "to test2";
    bool c8 = words[1].info == "v.";
    bool c9 = words[1].box == 2;

    bool res = c0 && c1 && c2 && c3 && c4 && c5 && c6 && c7 && c8 && c9;

    // Display result
    assrt(res, test_description, metrics);
  }
  {
    // Description
    std::string test_description = "TC_015: Test read words function correctly reads a sample file with extra new line";
    // Init inputs
    std::ofstream testfile;
    std::ifstream file;

    testfile.open("testfile");
    testfile << "1;tester1;to test1;v.;1\n2;tester2;to test2;v.;2\n";
    testfile.close();

    // Compute result
    std::vector<Word> words = read_words("testfile");
    file.close();
    remove("testfile"); // cleanup

    bool c0 = words[0].id == 1;
    bool c1 = words[0].french == "tester1";
    bool c2 = words[0].english == "to test1";
    bool c3 = words[0].info == "v.";
    bool c4 = words[0].box == 1;
    bool c5 = words[1].id == 2;
    bool c6 = words[1].french == "tester2";
    bool c7 = words[1].english == "to test2";
    bool c8 = words[1].info == "v.";
    bool c9 = words[1].box == 2;

    bool res = c0 && c1 && c2 && c3 && c4 && c5 && c6 && c7 && c8 && c9;

    // Display result
    assrt(res, test_description, metrics);
  }
  {
    // Description
    std::string test_description = "TC_006: Test read words function correctly returns empty vector if file not found";

    // Compute result
    std::vector<Word> words = read_words("filedoesnotexist");

    bool res = words.size() == 0;

    // Display result
    assrt(res, test_description, metrics);
  }
}

void test_save_words(TestMetrics &metrics)
{
  {
    // Description
    std::string test_description = "TC_007: Test save words function correctly saves a sample file";
    
    // Init inputs
    std::ofstream file;
    std::ifstream testfile;
    Word word1 = {1, "tester1", "to test1", "v.", 1};
    Word word2 = {2, "tester2", "to test2", "v.", 2};
    std::vector<Word> words = {word1, word2};

    // Compute result
    save_words(words, "testfile");
    testfile.open("testfile");
    std::string content;
    std::string line;
    while (getline(testfile, line))
    {
      content += line + "\n";
    }

    remove("testfile"); // cleanup

    bool res = content == "1;tester1;to test1;v.;1\n2;tester2;to test2;v.;2\n";

    // Display result
    assrt(res, test_description, metrics);
  }
}

void test_question(TestMetrics &metrics)
{
  {
    // Description
    std::string test_description = "TC_009: Test question returns proper question in ENGLISH_TO_FRENCH mode";
    // Init inputs
    Word word = {1, "tester", "to test", "v.", 1};

    // Compute result
    Card q = question(word, "ENGLISH_TO_FRENCH");

    bool c1 = q.front == word.english;
    bool c2 = q.back == word.french;

    bool res = c1 && c2;

    // Display result
    assrt(res, test_description, metrics);
  }
  {
    // Description
    std::string test_description = "TC_010: Test question returns proper question in FRENCH_TO_ENGLISH mode";
    // Init inputs
    Word word = {1, "tester", "to test", "v.", 1};

    // Compute result
    Card q = question(word, "FRENCH_TO_ENGLISH");

    bool c1 = q.front == word.french;
    bool c2 = q.back == word.english;

    bool res = c1 && c2;

    // Display result
    assrt(res, test_description, metrics);
  }
  {
    // Description
    std::string test_description = "TC_011: Test question returns proper question in MIXED mode";
    // Init inputs
    Word word = {1, "tester", "to test", "v.", 1};

    // Compute result
    Card q = question(word, "MIXED");

    bool c1 = q.front == word.english;
    bool c2 = q.back == word.french;

    bool res = c1 && c2;

    // Display result
    assrt(res, test_description, metrics);
  }
}

void test_reverse_question(TestMetrics &metrics)
{
  {
    // Description
    std::string test_description = "TC_012: Test reverse_question properly reverses a card";
    // Init input
    Card card = {1, "1", "2", "info"};

    // Compute result
    Card reversed = reverse_question(card);
    bool c1 = reversed.front == card.back;
    bool c2 = reversed.back == card.front;

    bool res = c1 && c2;

    // Display result
    assrt(res, test_description, metrics);
  }
}



void test_parse_settings(TestMetrics &metrics)
{
  {
    // Description
    std::string test_description = "TC_013: Test parse_settings can parse from a file the settings properly";
    // Init inputs

    std::ofstream file;
    file.open("testsettings");
    file << "PRACTICE_LENGTH 12\nSYSTEM D\nMODE TEST\nRETRIES 3";
    file.close();
    

    // Compute output and evaluate
    Settings settings = parse_settings("testsettings");

    remove("testsettings"); // cleanup

    bool c1 = settings.length == 12;
    bool c2 = settings.system == "D";
    bool c3 = settings.mode == "TEST";
    bool c4 = settings.retries == 3;

    bool res = c1 && c2 && c3 && c4;

    // Display result
    assrt(res, test_description, metrics);
  }
}

void test_parse_to_boxes(TestMetrics &metrics)
{
  {
    // Description
    std::string test_description = "TC_014: Test parse to box correctly returns a vector of vector of words";
    // Init inputs
    std::ofstream file;

    file.open("testwordsfile");
    file << "1;tester1;to test1;v.;1\n";
    file << "2;tester2;to test2;v.;2\n";
    file << "3;tester3;to test3;v.;3\n";
    file << "4;tester4;to test4;v.;4\n";
    file << "5;tester5;to test5;v.;5\n";
    file.close();

    // Init Expected result (if necessary)

    // Compute result
    std::vector<std::vector<Word>> words = parse_to_boxes("testwordsfile");

    remove("testwordsfile"); // cleanup

    bool c1 = words[0].size() == 5;
    bool c2 = words[1].size() == 1;
    bool c3 = words[2].size() == 1;
    bool c4 = words[3].size() == 1;
    bool c5 = words[4].size() == 1;
    bool c6 = words[5].size() == 1;
    bool c7 = words[1][0].french == "tester1";
    bool c8 = words[2][0].french == "tester2";
    bool c9 = words[3][0].french == "tester3";
    bool c10 = words[4][0].french == "tester4";
    bool c11 = words[5][0].french == "tester5";

    bool res = c1 && c2 && c3 && c4 && c5 && c6 && c7 && c8 && c9 && c10 && c11;

    // Display result
    assrt(res, test_description, metrics);
  }
}

void test_utils(TestMetrics &metrics)
{
  test_split(metrics);
  test_read_word(metrics);
  test_read_words(metrics);
  test_save_words(metrics);
  test_question(metrics);
  test_reverse_question(metrics);
  test_parse_to_boxes(metrics);
}

void test_settings(TestMetrics &metrics)
{
  test_parse_settings(metrics);
}

int main(void)
{
  TestMetrics metrics;
  metrics = {0, 0, 0};

  test_utils(metrics);
  test_settings(metrics);

  std::cout << "\n\nTest Run Complete. ";
  std::cout << "Executed: " << metrics.executed << " ";
  std::cout << "Pass: " << metrics.pass << " ";
  std::cout << "Fail: " << metrics.fail << ".\n\n";
}


// TEMPLATES
/*

void test_template(metrics)
{
  {
    // Description
    std::string test_description = "TC_XXX: Test description";
    // Init inputs

    // Init Expected result (if necessary)

    // Compute result
    bool res = false;

    // Display result
    assrt(res, test_description, metrics);
  }
}

*/