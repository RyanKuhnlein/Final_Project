// Ryan Kuhnlein
// Class: ITCS 2530
// GitHub Repo URL: https://github.com/RyanKuhnlein/Final_Project.git
// Final project: A writing aid tool that helps with idea organization and writer's block.
// Hobby mentioned in week 00 was writing, oringinally a choose your own adventure idea, turned into a writers aid.
// AI Tool(s) Used: CoPilot

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct Idea
{
    string category;
    string content;
};

class IdeaManager
{
public:
    IdeaManager(const string& file) : ideaCount(0), filename(file) 
    {
        ifstream ideaFile(filename);
        string line;
        while (getline(ideaFile, line) && ideaCount < MAX_IDEAS)
        {
            size_t sep = line.find('|');
            if (sep != string::npos)
            {
                ideas[ideaCount].category = line.substr(0, sep);
                ideas[ideaCount].content = line.substr(sep + 1);
                ideaCount++;
            }
        }
        ideaFile.close();
    }
    
    void addIdea();
    void listIdeas();
    void clearIdeas();

private:
    static const int MAX_IDEAS = 500;
    Idea ideas[MAX_IDEAS];
    int ideaCount = 0;
    const string filename;
};

class PromptManager
{
public:
    PromptManager(const string& file) : promptCount(0)
    {
        ifstream promptFile("prompts.txt");
        if (!promptFile.is_open())
        {
            cout << "ERROR: Could not open prompts.txt\n";
        }
        string line;
        while (getline(promptFile, line) && promptCount < MAX_PROMPTS)
        {
            prompts[promptCount++] = line;
        }
        promptFile.close();
        cout << "Prompts loaded: " << promptCount << "\n";
    }
    
    void showRandomPrompt();

private:
    static const int MAX_PROMPTS = 102;
    string prompts[MAX_PROMPTS];
    int promptCount = 0;

};

int main()
{   
    PromptManager prompt("prompts.txt");
    IdeaManager manager("ideas.txt");
    srand(static_cast<unsigned>(time(0)));


    int choice;
    do {
        cout << "\n = Writing Companion Menu = \n";
        cout << "1. Show Writing Prompt\n";
        cout << "2. Add Idea Fragment\n";
        cout << "3. List Stored Ideas\n";
        cout << "4. Clear All Ideas\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1: prompt.showRandomPrompt(); break;
        case 2: manager.addIdea(); break;
        case 3: manager.listIdeas(); break;
        case 4: manager.clearIdeas(); break;
        case 5: cout << "Good luck writing! You can do it!\n"; break;
        default: cout << "Invalid option. \n";
        }
    }
    while (choice != 5);

    return 0;
}

void PromptManager::showRandomPrompt()
{
    if (promptCount > 0)
    {
        int index = rand() % promptCount;
        cout << "Prompt: " << prompts[index] << "\n";
    }
    else
    {
        cout << "WARNING: No prompts found in prompts.txt\n";
    }
}

void IdeaManager::addIdea()
{
    if (ideaCount < MAX_IDEAS)
    {
        cin.ignore();
        cout << "Category: ";
        getline(cin, ideas[ideaCount].category);
        cout << "Content: ";
        getline(cin, ideas[ideaCount].content);

        ofstream outfile(filename, ios::app);
        if (outfile.is_open())
        {
            outfile << ideas[ideaCount - 1].category << "|" << ideas[ideaCount - 1].content << "\n";
            outfile.close();
            cout << "Idea saved automatically. \n";
        }
        else 
        {
            cout << "ERROR: Unable to open file for saving. \n";
        }
        ideaCount++;
    }
    else
    {
        cout << "Idea list is full. \n";
    }
}

void IdeaManager::listIdeas()
{
    cout << "\n--- Stored Ideas --\n";
    for (int i = 0; i < ideaCount; ++i)
    {
        cout << setw(10) << left << ideas[i].category << ": " << ideas[i].content << "\n";
    }
}

void IdeaManager::clearIdeas()
{
    char confirm;
    cout << "Are you sure you want to delete all ideas? (Y/N): ";
    cin >> confirm;
    confirm = toupper(confirm);
        
    if (confirm == 'Y')
    {
        ideaCount = 0;

        ofstream outfile(filename);
        if (outfile.is_open())
        {
            outfile.close();
            cout << "All ideas have been cleared. \n";
        }
        else
        {
            cout << "ERROR: Unable to clear ideas from file.\n";
        }
    }
    else {
        cout << "Whew! Nothing was deleted.\n";
    }
    
}

//
