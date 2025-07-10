#include <stdio.h>
#include <string.h>
#include <vector>
#include <string>

#define MAX_INPUT_LENGTH 1000

class TextAction {
private:
    std::string content;

public:
    TextAction(const char* text) : content(text) {}
    const char* getText() const { return content.c_str(); }
};

class TextEditor {
private:
    std::string currentText;
    std::vector<TextAction> undoStack;
    std::vector<TextAction> redoStack;

    void saveState() {
        if (undoStack.size() >= MAX_INPUT_LENGTH) {
            undoStack.erase(undoStack.begin());
        }
        undoStack.emplace_back(currentText.c_str());
        redoStack.clear(); // Clear redo stack when new action is performed
    }

public:
    TextEditor() {
        currentText = "";
    }

    void type(const char* text) {
        if (strlen(text) == 0) {
            printf("Error: Cannot type empty text\n");
            return;
        }
        saveState();
        currentText += text;
        printf("Added text: %s\n", text);
    }

    void undo() {
        if (undoStack.empty()) {
            printf("Nothing to undo!\n");
            return;
        }
        
        redoStack.emplace_back(currentText.c_str());
        currentText = undoStack.back().getText();
        undoStack.pop_back();
        
        printf("Undo successful. Current text: %s\n", currentText.c_str());
    }

    void redo() {
        if (redoStack.empty()) {
            printf("Nothing to redo!\n");
            return;
        }
        
        saveState();
        currentText = redoStack.back().getText();
        redoStack.pop_back();
        
        printf("Redo successful. Current text: %s\n", currentText.c_str());
    }

    void display() const {
        printf("\nCurrent text content:\n%s\n", currentText.c_str());
    }

    void clear() {
        saveState();
        currentText.clear();
        printf("Editor cleared.\n");
    }
};

void showHelp() {
    printf("\nTEXT EDITOR COMMANDS:\n");
    printf("type <text>  - Add text to editor\n");
    printf("undo         - Undo last action\n");
    printf("redo         - Redo last undone action\n");
    printf("display      - Show current text\n");
    printf("clear        - Clear all text\n");
    printf("help         - Show this help\n");
    printf("exit         - Quit editor\n");
}

int main() {
    TextEditor editor;
    char input[MAX_INPUT_LENGTH];
    char command[10];
    char text[MAX_INPUT_LENGTH];

    printf("=== TEXT EDITOR (with Undo/Redo) ===\n");
    printf("Type 'help' for commands\n");

    while (true) {
        printf("\n> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (sscanf(input, "%9s %999[^\n]", command, text) >= 1) {
            if (strcmp(command, "type") == 0) {
                editor.type(input + 5); // Skip "type "
            }
            else if (strcmp(command, "undo") == 0) {
                editor.undo();
            }
            else if (strcmp(command, "redo") == 0) {
                editor.redo();
            }
            else if (strcmp(command, "display") == 0) {
                editor.display();
            }
            else if (strcmp(command, "clear") == 0) {
                editor.clear();
            }
            else if (strcmp(command, "help") == 0) {
                showHelp();
            }
            else if (strcmp(command, "exit") == 0) {
                printf("Exiting editor. Goodbye!\n");
                break;
            }
            else {
                printf("Invalid command. Type 'help' for options.\n");
            }
        }
    }

    return 0;
}