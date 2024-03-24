# Levenshtein-distance
This is a repository to test my simplistic spellingschecker

The Levenshtein distance is a number that tells you how different two strings are. The higher the number, the more different the two strings are.

For example, the Levenshtein distance between “kitten” and “sitting” is 3 since, at a minimum, 3 edits are required to change one into the other.

- kitten → sitten (substitution of “s” for “k”)
- sitten → sittin (substitution of “i” for “e”)
- sittin → sitting (insertion of “g” at the end).

This means that you can have a list of words that do exist, and the word that the user types out.
If the word has a Levenshtein distance of 0 in comparison to a word in the list, it would mean that this word is spelled correctly.
If this is not the case it means that the lowest Levenshtein distance in the list is the word it is most likely to be as this would require the least alterations.

![image](https://github.com/driesnuttin25/Levenshtein-distance/assets/114076101/1a8c91b1-1374-421f-aecd-4c80fc2f1a40)
