#include <iostream>
#include <fstream>
#include <map>
using namespace std;

char* cleanWord(const char* word)
{
    int len = strlen(word);
    char* cleaned = new char[len + 1];
    int j = 0;

    for (int i = 0; i < len; ++i) 
    {
        if (isalnum(word[i]))
        {
            cleaned[j++] = tolower(word[i]);
        }
    }
    cleaned[j] = '\0';
    return cleaned;
}

struct cmp 
{
    bool operator()(const char* a, const char* b) const 
    {
        return strcmp(a, b) < 0;
    }
};

int main() 
{
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile) 
    {
        cerr << "Error: Cannot open input file!" << endl;
        return 1;
    }

    map<char*, int, cmp> wordFrequency;
    char line[1024];

    while (inputFile.getline(line, sizeof(line))) 
    {
        char* token = strtok(line, " \t\n\r");
        while (token != nullptr) {
            char* cleanedWord = cleanWord(token);
            if (strlen(cleanedWord) > 0) {
                wordFrequency[cleanedWord]++;
            } else {
                delete[] cleanedWord;
            }
            token = strtok(nullptr, " \t\n\r");
        }
    }
    inputFile.close();

    cout << "Word frequencies:\n";
    outputFile << "Word frequencies:\n";
    for (const auto& pair : wordFrequency) 
    {
        cout << pair.first << ": " << pair.second << endl;
        outputFile << pair.first << ": " << pair.second << endl;
    }

    char* mostFrequentWord = nullptr;
    int maxFrequency = 0;
    for (const auto& pair : wordFrequency) 
    {
        if (pair.second > maxFrequency) 
        {
            maxFrequency = pair.second;
            mostFrequentWord = pair.first;
        }
    }

    cout << "\nMost frequent word: " << mostFrequentWord << " (" << maxFrequency << ")" << endl;
    outputFile << "\nMost frequent word: " << mostFrequentWord << " (" << maxFrequency << ")" << endl;

    outputFile.close();
    cout << "\nResults saved to output.txt." << endl;

    
    for (const auto& pair : wordFrequency) 
    {
        delete[] pair.first;
    }

    return 0;
}
