#include <iostream>
#include <string>
#include <zmq.hpp>
#include <fstream>
#include <vector>
#include <limits>

// Assuming levenshtein and findClosestWord functions are defined here
using namespace std;
int levenshtein(const std::string &s1, int string_length1, const std::string &s2, int string_length2);
string findClosestWord(const std::string &inputWord, ifstream &dictionaryFile);

int main() {
    try {
        zmq::context_t context(1);

        zmq::socket_t subscriber(context, ZMQ_SUB);
        subscriber.connect("tcp://benternet.pxl-ea-ict.be:24042");
        std::string subscribeTopic = "dries>spelling>";
        subscriber.setsockopt(ZMQ_SUBSCRIBE, subscribeTopic.c_str(), subscribeTopic.length());

        zmq::socket_t responder(context, ZMQ_PUSH);
        responder.connect("tcp://benternet.pxl-ea-ict.be:24041");

        std::ifstream dictionaryFile("C:/Users/dries/OneDrive/Desktop/git/Levenshtein-distance/Benthernet/dictionary.txt");
        if (!dictionaryFile.is_open()) {
            std::cerr << "Failed to open dictionary file." << std::endl;
            return 1;
        }

        zmq::message_t message;
        while(true) {
            subscriber.recv(&message);
            std::string receivedMessage(static_cast<char*>(message.data()), message.size());
            std::cout << "Received: [" << receivedMessage << "]" << std::endl;

            // Extracting the word from the received message
            std::string word = receivedMessage.substr(subscribeTopic.length(), receivedMessage.find_last_of(">") - subscribeTopic.length());

            // Correcting the word
            std::string correctedWord = findClosestWord(word, dictionaryFile);

            // Sending back the corrected word
            std::string response = "dries>correct>" + correctedWord + ">";
            responder.send(response.c_str(), response.size());
        }
    }
    catch(zmq::error_t& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
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

// Function to find the closest word in the dictionary for a given word
string findClosestWord(const std::string &inputWord, ifstream &dictionaryFile) {
    dictionaryFile.clear();
    dictionaryFile.seekg(0, ios::beg);

    std::string dictionaryWord;
    vector<string> closestWords;
    int minDistance = numeric_limits<int>::max();

    while (getline(dictionaryFile, dictionaryWord)) {
        int lengthDifference = abs(static_cast<int>(inputWord.length()) - static_cast<int>(dictionaryWord.length()));

        if (lengthDifference <= 1) {
            int distance = levenshtein(inputWord, inputWord.length(), dictionaryWord, dictionaryWord.length());

            if (distance < minDistance) {
                minDistance = distance;
                closestWords.clear();
                closestWords.push_back(dictionaryWord);
            } else if (distance == minDistance) {
                closestWords.push_back(dictionaryWord);
            }
        }
    }

    // At the moment we're just going to assume that the word with the least Levenshtein distance is the correct word,
    // not very efficient in finding the actual correct word but works well enough for now
    return closestWords.empty() ? inputWord : closestWords.front();
}

