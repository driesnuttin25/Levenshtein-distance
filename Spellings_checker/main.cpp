/*
* Calculating the Levenshtein distance between two strings
* This is used to find possible substitutions and spelling mistakes
* Author: Dries Nuttin
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

int levenshtein(const std::string &s1, int string_length1, const std::string &s2, int string_length2);

int main()
{
    std::string userInput;
    cout << "Enter a word: ";
    cin >> userInput;

    ifstream dictionaryFile("C:/Users/dries/OneDrive/Desktop/git/Levenshtein-distance/Spellings_checker/dictionary.txt");
    std::string word;
    vector<string> closestWords;
    int minDistance = numeric_limits<int>::max();

    if (!dictionaryFile.is_open()) {
        cerr << "Failed to open dictionary.txt" << endl;
        return 1;
    }

    while (getline(dictionaryFile, word)) {
        int distance = levenshtein(userInput, userInput.length(), word, word.length());
        if(distance == 0){
            cout << endl << "This word is spelled correctly"<< endl;
            return 0;
        }
        else if (distance < minDistance) {
            minDistance = distance;
            closestWords.clear();
            closestWords.push_back(word);
        } else if (distance == minDistance) {
            closestWords.push_back(word);
        }
    }

    dictionaryFile.close();

    cout << endl << "Closest word(s) to '" << userInput << "' with a distance of " << minDistance << ":" << endl;
    for (const auto &closestWord : closestWords) {
        cout << closestWord << endl;
    }
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
