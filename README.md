# T9-Predictive-Keyboard
T9 is an algorithm to help predict which letters, and which word overall, the user meant. 
It works by translating each word in the dictionary into its number sequence. 
For example: apple => 27753, book => 2665.
It can then check the sequence of numbers typed to see if it matches a known word from its dictionary. 
If it finds a plausible word which matches, that word is entered.
