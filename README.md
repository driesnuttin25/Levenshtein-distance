# Levenshtein Distance Spell Checker

Welcome to the Levenshtein Distance Spell Checker repository. This project utilizes the Levenshtein distance algorithm to create a simplistic but effective spell checker. The Levenshtein distance measures the minimum number of single-character edits required to change one word into another, providing a quantitative basis for spell checking.

## Understanding Levenshtein Distance
The Levenshtein distance between two strings is a measure of their dissimilarity, calculated as the minimum number of single-character edits needed to transform one string into the other. These edits include insertions, deletions, or substitutions.

## Example:
Transforming "kitten" into "sitting":
- kitten → sitten (substitute "s" for "k")
- sitten → sittin (substitute "i" for "e")
- sittin → sitting (insert "g" at the end)
This results in a Levenshtein distance of 3, indicating three edit operations are required.

## Spell Checking with Levenshtein Distance
The spell checker compares each word in a user-input sentence against a predefined list of correctly spelled words. If a word matches exactly (Levenshtein distance of 0), it is considered correctly spelled. Otherwise, the checker suggests the closest match from the list, minimizing the Levenshtein distance and, consequently, the necessary edits.
For the code that I made today I used a file called dictionary.txt to include all correctly spelled words to check if a word is misspelled and if it is see what other word has the least Levenshtein distance and use that as a replacement. The dictionary.txt file includes a total of 20K of the most used words in the English language.
This is all based on the Levenshtein algorithm which is mathametically structured as the following:

![image](https://github.com/driesnuttin25/Levenshtein-distance/assets/114076101/089d3d4f-e29f-4211-b446-bce3c584739d)

When we take this mathematical algorithm and tranfser it to a c++ code we can get the following function:

```c++
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
```


## Example 

Given the sentence:

``` this is a test to see if this program works ```

now let'S make a couple mistakes in it to see if the program works

``` thiss is a trst to see if thisp progwam workss ```

The spell checker will suggest corrections based on the smallest Levenshtein distance to known, correctly spelled words.
This we can also see when we run the code, giving us the following resutl: 

<img width="365" alt="image" src="https://github.com/driesnuttin25/Levenshtein-distance/assets/114076101/161e42bc-111e-4f07-be2a-17ad2884ab15">






