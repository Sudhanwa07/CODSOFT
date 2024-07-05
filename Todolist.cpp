#include <iostream>
#include <vector>
#include <string>

struct Task {
    std::string description;
    bool completed;

    Task(const std::string &desc) : description(desc), completed(false) {}
};

class ToDoList {
public:
    void addTask(const std::string &description) {
        tasks.push_back(Task(description));
    }

    void viewTasks() const {
        if (tasks.empty()) {
            std::cout << "No tasks to display.\n";
        } else {
            for (size_t i = 0; i < tasks.size(); ++i) {
                std::cout << i + 1 << ". [" << (tasks[i].completed ? "X" : " ") << "] " << tasks[i].description << "\n";
            }
        }
    }

    void markTaskCompleted(size_t index) {
        if (index < 1 || index > tasks.size()) {
            std::cout << "Invalid task number.\n";
        } else {
            tasks[index - 1].completed = true;
        }
    }

    void removeTask(size_t index) {
        if (index < 1 || index > tasks.size()) {
            std::cout << "Invalid task number.\n";
        } else {
            tasks.erase(tasks.begin() + index - 1);
        }
    }

private:
    std::vector<Task> tasks;
};

int main() {
    ToDoList toDoList;
    int choice;
    std::string taskDescription;
    size_t taskIndex;

    while (true) {
        std::cout << "\nTo-Do List Manager\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. View Tasks\n";
        std::cout << "3. Mark Task as Completed\n";
        std::cout << "4. Remove Task\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter task description: ";
                std::cin.ignore(); // to ignore the leftover newline character
                std::getline(std::cin, taskDescription);
                toDoList.addTask(taskDescription);
                break;

            case 2:
                toDoList.viewTasks();
                break;

            case 3:
                std::cout << "Enter task number to mark as completed: ";
                std::cin >> taskIndex;
                toDoList.markTaskCompleted(taskIndex);
                break;

            case 4:
                std::cout << "Enter task number to remove: ";
                std::cin >> taskIndex;
                toDoList.removeTask(taskIndex);
                break;

            case 5:
                return 0;

            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}
