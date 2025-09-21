#include <stdio.h> // Included for standard input-output functions
#include <stdlib.h> // Included for memory allocation and deallocation functions
#include <string.h> // Included for string manipulation functions
#include <stdbool.h> // Included for boolean data type

#define ALPHABET_SIZE 26

// Trie node structure
typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE]; // Array to store child nodes
    bool isEndOfWord; // Flag to indicate end of a word
    char *description; // Description associated with the word
} TrieNode;

// Function to create a new Trie node
TrieNode *createNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode)); // Allocate memory for new node
    if (node) {
        node->isEndOfWord = false; // Initialize end of word flag
        node->description = NULL; // Initialize description pointer
        for (int i = 0; i < ALPHABET_SIZE; ++i)
            node->children[i] = NULL; // Initialize children nodes
    }
    return node;
}

// Function to validate input word and description
bool validInp(const char *input, int minWords) {
    int count = 0;
    char *copy = strdup(input); // Create a copy of the input string
    char *token = strtok(copy, " "); // Tokenize the input string
    while (token != NULL) {
        count++;
        token = strtok(NULL, " "); // Move to the next token
    }
    free(copy); // Free memory allocated for the copy
    return count >= minWords; // Return true if the number of words is greater than or equal to minWords
}

// Function to insert a word into the Trie
void insertWord(TrieNode *root, const char *word, const char *description) {
    TrieNode *current = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a'; // Calculate index of the current character
        if (!current->children[index])
            current->children[index] = createNode(); // Create a new node if it doesn't exist
        current = current->children[index]; // Move to the next node
    }
    if (current->isEndOfWord && current->description)
        free(current->description); // Free memory allocated for previous description
    current->isEndOfWord = true; // Set end of word flag
    current->description = strdup(description); // Copy description to the node
}

// Function to search for a word in the Trie
TrieNode *searchWord(TrieNode *root, const char *word) {
    TrieNode *current = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a'; // Calculate index of the current character
        if (!current->children[index])
            return NULL; // Return NULL if word is not found
        current = current->children[index]; // Move to the next node
    }
    return (current->isEndOfWord) ? current : NULL; // Return node if word is found
}

// Function to print words with a given prefix
void printWordsWPrefUtil(TrieNode *node, char *prefix, int level) {
    if (node->isEndOfWord)
        printf("%s\n", prefix); // Print the word if it's the end of a word
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            prefix[level] = 'a' + i; // Append the character to the prefix
            prefix[level + 1] = '\0'; // Ensure null termination
            printWordsWPrefUtil(node->children[i], prefix, level + 1); // Recursively print words
        }
    }
}

// Function to print all words with a given prefix
void printWordsWPref(TrieNode *root, const char *prefix) {
    TrieNode *current = root;
    char *tempPrefix = (char *)malloc(strlen(prefix) + 1); // Allocate memory for prefix
    strcpy(tempPrefix, prefix); // Copy prefix to tempPrefix
    for (int i = 0; tempPrefix[i] != '\0'; i++) {
        int index = tempPrefix[i] - 'a'; // Calculate index of the current character
        if (!current->children[index]) {
            printf("\nThere is no prefix \"%s\" in the dictionary.\n", prefix); // Print message if prefix is not found
            free(tempPrefix); // Free memory allocated for prefix
            return;
        }
        current = current->children[index]; // Move to the next node
    }
    printf("Words starts with \"%s\":\n", prefix); // Print message indicating words with prefix
    printWordsWPrefUtil(current, tempPrefix, strlen(prefix)); // Print words with prefix
    // free(tempPrefix); // Free allocated memory for tempPrefix
}

// Function to print all words in the Trie
void printAllWordsUtil(TrieNode *root, char *word, int level) {
    if (root->isEndOfWord)
        printf("%s\n", word); // Print the word if it's the end of a word
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            word[level] = 'a' + i; // Append the character to the word
            word[level + 1] = '\0'; // Ensure null termination
            printAllWordsUtil(root->children[i], word, level + 1); // Recursively print words
        }
    }
}

void printAllWords(TrieNode *root) {
    char *word = (char *)malloc(100 * sizeof(char)); // Allocate memory for word
    printAllWordsUtil(root, word, 0); // Print all words in the Trie
    free(word); // Free allocated memory for word
}

void freeTrie(TrieNode *root) {
    if (!root)
        return;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        freeTrie(root->children[i]); // Recursively free memory for children nodes
    free(root->description); // Free memory for description
    free(root); // Free memory for root node
}

int main() {
    TrieNode *root = createNode(); // Create root node of Trie
    int choice;
    char word[100];
    char description[100];
    bool isEmpty = true; // Flag to track if the dictionary is empty

    while (true) { // Main program loop
        printf("\nBoogle Slang Dictionary\n");
        printf("1. Release a new slang word\n");
        printf("2. Search a slang word\n");
        printf("3. View all slang words starting with a certain prefix word\n");
        printf("4. View all slang words\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); // Read user choice

        switch (choice) {
            case 1:
                while (true) {
                    printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
                    scanf("%s", word); // Read slang word from user
                    if (validInp(word, 1)) // Validate input
                        break;
                }
                while (true) {
                    printf("Input a new slang word description [Must be more than 2 words]: ");
                    scanf(" %[^\n]s", description); // Read description from user
                    if (validInp(description, 3)) // Validate input
                        break;
                    // Clear input buffer
                    while (getchar() != '\n');
                }
                insertWord(root, word, description); // Insert word into Trie
                isEmpty = false; // Dictionary is not empty anymore
                printf("Successfully released new slang word.\n");
                break;

            case 2:
                printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
                scanf("%s", word); // Read slang word from user
                TrieNode *found = searchWord(root, word); // Search for word in Trie
                if (found)
                    printf("Slang word: %s\nDescription: %s\n", word, found->description); // Print word and description if found
                else
                    printf("\nThere is no word \"%s\" in the dictionary.\n", word); // Print message if word not found
                break;

            case 3:
                printf("Input a prefix to be searched: ");
                scanf("%s", word); // Read prefix from user
                printWordsWPref(root, word); // Print words with prefix
                break;

            case 4:
                if (isEmpty)
                    printf("\nThere is no slang word yet in the dictionary.\n");
                else
                    printAllWords(root); // Print all words in the Trie
                break;

            case 5:
                printf("Thank you... Have a nice day :)\n");
                exit(0); // Exit the program

            default:
                printf("Invalid choice! Please try again.\n");
        }
        // Clear input buffer
        while (getchar() != '\n');
        printf("Press enter to continue...");
        getchar(); // Wait for Enter key
    }

    return 0;
}
