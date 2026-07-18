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
// ===============================
// Save one fact
// ===============================
void saveFact(string question, string answer) {

    ofstream file("knowledge/knowledge.txt", ios::app);

    file << question << "=" << answer << endl;

    file.close();
}// ===============================
// Main Function
// ===============================

int main() {

    loadKnowledge();

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

        // Exit
        if (input == "exit") {
            cout << "OpenMind: Goodbye!\n";
            break;
        }

        // Help
        if (input == "help") {

            cout << "\n===== Commands =====\n";
            cout << "help\n";
            cout << "learn\n";
            cout << "bulklearn\n";
            cout << "import\n";
            cout << "stats\n";
            cout << "time\n";
            cout << "date\n";
            cout << "exit\n";
            cout << "====================\n\n";

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

        auto it = knowledge.find(input);

        if (it != knowledge.end()) {
            cout << "OpenMind: " << it->second << endl;
        } else {

            bool found = false;

            for (auto &fact : knowledge) {

                if (fact.first.find(input) != string::npos ||
                    input.find(fact.first) != string::npos) {

                    cout << "OpenMind: " << fact.second << endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "OpenMind: I don't know that yet.\n";
                cout << "Type 'learn' to teach me.\n";
            }
        }

} // closes while loop

    return 0;
} //closes main()
