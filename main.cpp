#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const char PLACEHOLDER = '\0';
const int  MAX_NODES   =  64 ;
int  weightArr[MAX_NODES];
int  leftArr  [MAX_NODES];
int  rightArr [MAX_NODES];
char charArr  [MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string &filename);
int  createLeafNodes(int freq[]);
int  buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string &filename, string codes[]);

int main()
{
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch))
    {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[])
{
    int nextFree = 0;
    for (int i = 0; i < 26; ++i)
    {
        if (freq[i] > 0)
        {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree)
{
    MinHeap heap;

    // Push indexes of found letters to heap
    for (int i = 0; i < nextFree; i++)
        if (weightArr[i] > 0)
            heap.push(i, weightArr);

    // Returning root in edge cases
    if (heap.size == 0) return -1;
    if (heap.size == 1) return heap.pop(weightArr);

    // Combine weights until one node is left
    while (heap.size > 1)
    {
        // Get smallest two nodes
        int left  = heap.pop(weightArr);
        int right = heap.pop(weightArr);

        weightArr[nextFree] = weightArr[left] + weightArr[right]; // Combine nodes
        charArr  [nextFree] = PLACEHOLDER;                        // Set terminating marker
        leftArr  [nextFree] = left;                               // Set smallest
        rightArr [nextFree] = right;                              // Set second smallest

        // Push index and increment
        heap.push(nextFree, weightArr);
        nextFree++;
    }

    // Return remaining root
    return heap.pop(weightArr);
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[])
{
    if (root < 0) return;

    stack<pair<int, string>> encoded;
    encoded.emplace(root, ""); // Start with the root (apparently implicit pair creation is a thing now? Cool!)

    while (!encoded.empty())
    {
        // Get and pop most recently pushed pair
        pair<int, string> current = encoded.top();
        encoded.pop();

        int    index = current.first;
        string code  = current.second;

        int left  = leftArr [index];
        int right = rightArr[index];

        // Check for leaf nodes
        if (left == -1 && right == -1)
        {
            if (code.empty()) code = "0"; // Prevent empty code for single letter input

            // Set code for each char
            char letter = charArr[index];
            if (letter >= 'a' && letter <= 'z')
                codes[letter - 'a'] = code;

            continue; // Skip pushing to stack
        }

        // Not leaf node, encode each char depending on which turn it takes
        if (right != -1) encoded.emplace(right, code + "1");
        if ( left != -1) encoded.emplace(left , code + "0");
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string &filename, string codes[])
{
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i)
    {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch))
    {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}
