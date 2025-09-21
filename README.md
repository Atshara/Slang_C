# Slang_C
A simple C program to write slang words

If user choose menu 1 (“Release a new slang word”), then the program will:
- Ask the user to input the new slang word. Validate that the slang word must be more than 1 character and contains no space.
- Ask the user to input the description (meaning) of the new word. Validate that the description must be more than 1 word.
- Store the new released slang word to a Trie data structure along with its description.
- If the slang word already exists in the Trie, then update the description with the new description.

If user choose menu 2 (“Search a slang word”), then the program will:
- Ask the user to input the slang word that want to be searched. Validate that the slang word must be more than 1 character and contains
no space.
- Search the input word in the Trie data structure.
- If there is no such word, the program will show empty message for the user and go back to main menu.
- If there is such word, the program will show the word along with its description.

If user choose menu 3 (“View all slang words starting with a certain prefix word”), then the program will:
- Ask the user to input the prefix word that want to be searched.
- Search the input word in the Trie data structure.
- If there is no such word, the program will show empty message for the user.
- If there is such word, the program will show the list of words in the dictionary that starts with the prefix word in lexicographical order.

If user choose menu 4 (“View all slang words”), then the program will:
- If there is no word yet in the dictionary, the program will show empty message for the user.
- If there is words in the dictionary, the program will show the list of all words in the dictionary in lexicographical order.

If user choose menu 5 (“Exit”), then the program will be closed.
