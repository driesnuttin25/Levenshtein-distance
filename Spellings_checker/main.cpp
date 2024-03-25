/*
* Calculating the Levenshtein distance between two strings
* This is used to find possible substitutions and spelling mistakes
* Author: Dries Nuttin
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

int levenshtein(const std::string &s1, int string_length1, const std::string &s2, int string_length2);
string findClosestWord(const std::string &inputWord, ifstream &dictionaryFile);

int main() {
    cout << "Enter a sentence: ";
    std::string userInput;
    getline(cin, userInput);

    ifstream dictionaryFile("C:/Users/dries/OneDrive/Desktop/git/Levenshtein-distance/Spellings_checker/dictionary.txt");

    if (!dictionaryFile.is_open()) {
        cerr << "Failed to open dictionary.txt" << endl;
        return 1;
    }

    std::istringstream iss(userInput);
    std::string word;
    std::string correctedSentence;
    std::string originalWord;
    bool isFirstWord = true;

    while (iss >> word) {
        originalWord = word;
        string correctedWord = findClosestWord(word, dictionaryFile);

        // For constructing the corrected sentence
        if (!isFirstWord) correctedSentence += " ";
        correctedSentence += correctedWord;
        isFirstWord = false;

        // Output if the word was corrected
        if (originalWord != correctedWord) {
            cout << "Corrected '" << originalWord << "' to '" << correctedWord << "'" << endl;
        }
    }

    cout << "\nOriginal sentence: " << userInput << endl;
    cout << "Corrected sentence: " << correctedSentence << endl;

    return 0;
}

int levenshtein(const std::string &s1, int string_length1, const std::string &s2, int string_length2)
{
    int sub, insert, del;
    // Check if the string is empty or not, if it is empty it would require the length of the other string as the amount of deletions to become the first string.
    if (string_length1 == 0)
    {
        return string_length2;
    }
    if (string_length2 == 0)
    {
        return string_length1;
    }

    // If the last letter is the same for both strings, we can skip this as there is no operation needed
    if (s1[string_length1 - 1] == s2[string_length2 - 1])
    {
        return levenshtein(s1, string_length1 - 1, s2, string_length2 - 1);
    }

    // Going through the string and checking if a substitution, an insertion, or a deletion needs to take place.
    sub = levenshtein(s1, string_length1 - 1, s2, string_length2 - 1);
    insert = levenshtein(s1, string_length1, s2, string_length2 - 1);
    del = levenshtein(s1, string_length1 - 1, s2, string_length2);

    // Check which method is superior
    if (sub > insert)
    {
        sub = insert;
    }
    if (sub > del)
    {
        sub = del;
    }

    // Return plus 1 to account for the last action performed
    return sub + 1;
}

// Function to find the closest word in the dictionary for a given word
string findClosestWord(const std::string &inputWord, ifstream &dictionaryFile) {
    dictionaryFile.clear();
    dictionaryFile.seekg(0, ios::beg);

    std::string dictionaryWord;
    vector<string> closestWords;
    int minDistance = numeric_limits<int>::max();

    while (getline(dictionaryFile, dictionaryWord)) {
        int distance = levenshtein(inputWord, inputWord.length(), dictionaryWord, dictionaryWord.length());

        if (distance < minDistance) {
            minDistance = distance;
            closestWords.clear();
            closestWords.push_back(dictionaryWord);
        } else if (distance == minDistance) {
            closestWords.push_back(dictionaryWord);
        }
    }

    // Assuming the first closest word is the desired correction
    return closestWords.empty() ? inputWord : closestWords.front();
}
