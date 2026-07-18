#include <sstream>
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <ctime>

using namespace std;
namespace fs = std::filesystem;

map<string, string> knowledge;

// Convert string to lowercase
string toLower(string text) {
    transform(text.begin(), text.end(), text.begin(),
              [](unsigned char c) {
                  return tolower(c);
              });
    return text;
}
void loadKnowledge() {

    knowledge.clear();

    int count = 0;

    for (const auto &entry : fs::directory_iterator("knowledge")) {

        if (entry.path().extension() != ".txt")
            continue;

        ifstream file(entry.path());

        if (!file)
            continue;

        string line;

        while (getline(file, line)) {
        file.close();
            size_t pos = line.find('=');

            if (pos == string::npos)
                continue;

            string question = toLower(line.substr(0, pos));
            string answer = line.substr(pos + 1);

            knowledge[question] = answer;
            count++;
        }
    }
}
vector<string> splitWords(string text) {

    vector<string> words;
    string word;

    // Remove punctuation
    for (char &c : text) {
        if (!isalnum(c) && c != ' ')
            c = ' ';
    }

    stringstream ss(toLower(text));

    while (ss >> word)
        words.push_back(word);

    return words;
}
// ===============================
// Save one fact
// ===============================

void saveFact(string question, string answer) {

    ofstream file("knowledge/knowledge.txt", ios::app);

    file << question << "=" << answer << endl;

    file.close();
}

void saveMemory(string key, string value) {

    ofstream file("knowledge/memory.txt", ios::app);

    if (file)
        file << key << "=" << value << endl;
}void loadMemory() {

    ifstream file("knowledge/memory.txt");

    string line;

    while (getline(file, line)) {

        size_t pos = line.find('=');

        if (pos == string::npos)
            continue;

        string key = toLower(line.substr(0, pos));
        string value = line.substr(pos + 1);

        knowledge[key] = value;
}
}// ===============================
// Main Function
// ===============================
string autoCorrect(string input) {

    map<string, string> corrections = {
        {"captial", "capital"},
        {"capitel", "capital"},
        {"indai", "india"},
        {"jappan", "japan"},
        {"maharastra", "maharashtra"},
        {"goverment", "government"}
    };

    vector<string> words = splitWords(input);

    string result;

    for (string word : words) {

        if (corrections.count(word))
            word = corrections[word];

        if (!result.empty())
            result += " ";

        result += word;
    }

    return result;
}
// ===============================
// Conversation Logger
// ===============================
void logConversation(string user, string bot) {
    ofstream file("logs/history.txt", ios::app);

    if (file) {
        file << "You: " << user << endl;
        file << "OpenMind: " << bot << endl << endl;
    }
}
int main() {

loadKnowledge();
loadMemory();
    string input;

    cout << "=====================================\n";
    cout << "        OpenMind v0.6\n";
    cout << "     Offline AI Assistant\n";
    cout << "=====================================\n";
    cout << "Facts Loaded: " << knowledge.size() << endl;
    cout << "Type 'help' for commands.\n\n";

    while (true) {

        cout << "You: ";
        getline(cin, input);

        input = toLower(input);
input = autoCorrect(input);
        // Exit
        if (input == "exit") {
            cout << "OpenMind: Goodbye!\n";
            break;
        }

        // Help
        if (input == "help") {


cout << "\n===== OpenMind Commands =====\n";
cout << "help\n";
cout << "learn\n";
cout << "bulklearn\n";
cout << "import\n";
cout << "search\n";
cout << "remember\n";
cout << "forget\n";
cout << "reload\n";
cout << "stats\n";
cout << "version\n";
cout << "time\n";
cout << "date\n";
cout << "exit\n";
cout << "=============================\n\n";
}
// ===============================
// Remember Command
// ===============================
if (input.rfind("remember ", 0) == 0) {

    string memory = input.substr(9);

    size_t pos = memory.find(" is ");

    if (pos != string::npos) {

        string key = toLower(memory.substr(0, pos));
        string value = memory.substr(pos + 4);

        knowledge[key] = value;
        saveMemory(key, value);

        cout << "OpenMind: I'll remember that." << endl;

    } else {
        cout << "OpenMind: Use format: remember <something> is <value>" << endl;
    }

    continue;
}
// ===============================
// Personal Memory Questions
// ===============================
if (input == "what is my name" ||
    input == "who am i") {

    auto it = knowledge.find("my name");

    if (it != knowledge.end()) {
        cout << "OpenMind: Your name is " << it->second << "." << endl;
    } else {
        cout << "OpenMind: I don't know your name yet." << endl;
    }

    continue;
}
// ===============================
// Personal Memory Questions
// ===============================
if (input == "what is my name" ||
    input == "who am i") {

    auto it = knowledge.find("my name");

    if (it != knowledge.end())
        cout << "OpenMind: Your name is " << it->second << "." << endl;
    else
        cout << "OpenMind: I don't know your name yet." << endl;

    continue;
}
// ===============================
// Search Command
// ===============================
if (input.rfind("search ", 0) == 0) {

    string keyword = toLower(input.substr(7));

    int count = 0;

    for (auto &fact : knowledge) {

        if (fact.first.find(keyword) != string::npos ||
            fact.second.find(keyword) != string::npos) {

            cout << fact.first << " = " << fact.second << endl;
            count++;
        }
    }

    cout << "Found " << count << " result(s).\n";

    continue;
}
// ===============================
// Reload Knowledge
// ===============================
cout << "reload\n";
if (input == "reload") {

    knowledge.clear();
    loadKnowledge();

    cout << "OpenMind: Knowledge reloaded successfully!\n";

    continue;
}
        // Stats
        if (input == "stats") {

            cout << "\n===== OpenMind Stats =====\n";
            cout << "Version : v0.6\n";
            cout << "Facts   : " << knowledge.size() << endl;
            cout << "Memory  : knowledge/knowledge.txt\n";
            cout << "Math    : Enabled\n";
            cout << "==========================\n\n";

            continue;
        }
// ===============================
// Version Command
// ===============================
if (input == "version") {

    cout << "\n===== OpenMind =====\n";
    cout << "Version : v1.0\n";
    cout << "Facts   : " << knowledge.size() << endl;
    cout << "Build   : July 2026\n";
    cout << "====================\n\n";

    continue;
}
        // Time & Date
        if (input == "time" || input == "date") {

            time_t now = time(nullptr);
            cout << ctime(&now);

            continue;
        }
        // ===============================
        // Learn One Fact
        // ===============================
        if (input == "learn") {

            string question, answer;

            cout << "Question: ";
            getline(cin, question);

            cout << "Answer: ";
            getline(cin, answer);

            question = toLower(question);

            knowledge[question] = answer;
            saveFact(question, answer);

            cout << "OpenMind: Learned successfully!\n";

            continue;
        }

        // ===============================
        // Bulk Learn
        // ===============================
        if (input == "bulklearn") {

            cout << "\nBulk Learning Mode\n";
            cout << "Enter facts like:\n";
            cout << "question=answer\n";
            cout << "Type 'done' when finished.\n\n";

            int count = 0;

            while (true) {

                string line;
                getline(cin, line);

                if (toLower(line) == "done")
                    break;

                size_t pos = line.find('=');

                if (pos == string::npos) {
                    cout << "Invalid format! Use question=answer\n";
                    continue;
                }

                string question = toLower(line.substr(0, pos));
                string answer = line.substr(pos + 1);

                knowledge[question] = answer;
                saveFact(question, answer);

                count++;
            }

            cout << "OpenMind: Learned " << count << " new facts.\n";

            continue;
        }
// ===============================
// Forget Command
// ===============================
if (input.rfind("forget ", 0) == 0) {

    string question = toLower(input.substr(7));

    auto it = knowledge.find(question);

    if (it != knowledge.end()) {
        knowledge.erase(it);
        cout << "OpenMind: Fact removed from memory.\n";
    } else {
        cout << "OpenMind: Fact not found.\n";
    }

    continue;
}
        // ===============================
        // Import Facts From File
        // ===============================
if (input == "import") {
    cout << "DEBUG: Import command reached!" << endl;
            string filename;

            cout << "File: ";
            getline(cin, filename);

            ifstream file(filename);

            if (!file) {
                cout << "OpenMind: Cannot open file.\n";
                continue;
            }

            string line;
            int count = 0;

            while (getline(file, line)) {

                size_t pos = line.find('=');

                if (pos == string::npos)
                    continue;

                string question = toLower(line.substr(0, pos));
                string answer = line.substr(pos + 1);

                knowledge[question] = answer;
                saveFact(question, answer);

                count++;
            }

            file.close();

            cout << "OpenMind: Imported " << count << " facts.\n";

            continue;
        }
        // ===============================
        // Simple Calculator
        // ===============================

        size_t plus = input.find('+');
        size_t minus = input.find('-');
        size_t multiply = input.find('*');
        size_t divide = input.find('/');

        try {

            if (plus != string::npos) {
                double a = stod(input.substr(0, plus));
                double b = stod(input.substr(plus + 1));

                cout << "OpenMind: " << (a + b) << endl;
                continue;
            }

            if (minus != string::npos) {
                double a = stod(input.substr(0, minus));
                double b = stod(input.substr(minus + 1));

                cout << "OpenMind: " << (a - b) << endl;
                continue;
            }

            if (multiply != string::npos) {
                double a = stod(input.substr(0, multiply));
                double b = stod(input.substr(multiply + 1));

                cout << "OpenMind: " << (a * b) << endl;
                continue;
            }

            if (divide != string::npos) {
                double a = stod(input.substr(0, divide));
                double b = stod(input.substr(divide + 1));

                if (b == 0)
                    cout << "OpenMind: Cannot divide by zero.\n";
                else
                    cout << "OpenMind: " << (a / b) << endl;

                continue;
            }

        } catch (...) {
            // Not a valid math expression
        }

        // ===============================
        // Smart Answer Engine
        // ===============================
int bestScore = 0;
string bestAnswer = "";

vector<string> inputWords = splitWords(input);

for (auto &fact : knowledge) {

    int score = 0;

    vector<string> questionWords = splitWords(fact.first);

    for (auto &w1 : inputWords) {
        for (auto &w2 : questionWords) {
            if (w1 == w2)
                score++;
        }
    }

    if (score > bestScore) {
        bestScore = score;
        bestAnswer = fact.second;
    }
}

if (bestScore >= 2) {
    cout << "OpenMind: " << bestAnswer << endl;
} else {
    cout << "OpenMind: I don't know that yet.\n";
    cout << "Type 'learn' to teach me.\n";
}

} // closes while loop

    return 0;
} //closes main()
