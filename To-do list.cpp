#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Task {
	std::string name;
	std::string description;
	bool completed;
};

class ToDoList {
private:
	std::vector<Task> tasks;

public:
	void addTask(const std::string& name, const std::string& description) {
		tasks.push_back({ name, description, false });
	}

	void displayTasks() {
		for (size_t i = 0; i < tasks.size(); ++i) {
			std::cout << i + 1 << ". " << tasks[i].name
				<< " - " << (tasks[i].completed ? "Completed" : "Pending") << std::endl;
		}
	}

	void completeTask(int index) {
		if (index >= 0 && index < tasks.size()) {
			tasks[index].completed = true;
		}
		else {
			std::cout << "Invalid task index!" << std::endl;
		}
	}

	void deleteTask(int index) {
		if (index >= 0 && index < tasks.size()) {
			tasks.erase(tasks.begin() + index);
		}
		else {
			std::cout << "Invalid task index!" << std::endl;
		}
	}

	void viewTaskDescription(int index) {
		if (index >= 0 && index < tasks.size()) {
			std::cout << "Description for task '" << tasks[index].name << "': "
				<< tasks[index].description << std::endl;
		}
		else {
			std::cout << "Invalid task index!" << std::endl;
		}
	}

	void saveToFile(const std::string& filename) {
		std::ofstream outFile(filename);
		for (const auto& task : tasks) {
			outFile << task.name << "|" << task.description << "|" << task.completed << "\n";
		}
		outFile.close();
	}

	void loadFromFile(const std::string& filename) {
		std::ifstream inFile(filename);
		if (inFile) {
			Task task;
			std::string completedStr;
			while (std::getline(inFile, task.name, '|') &&
				std::getline(inFile, task.description, '|') &&
				std::getline(inFile, completedStr)) {
				task.completed = (completedStr == "1");
				tasks.push_back(task);
			}
			inFile.close();
		}
	}
};

int main() {
	ToDoList myList;
	myList.loadFromFile("tasks.txt"); // Load tasks from file

	int choice;
	do {
		system("cls");
		std::cout << "\nCurrent Tasks:" << std::endl;
		myList.displayTasks();
		std::cout << "Choose an option:\n1. Add a new task\n2. Complete a task\n3. Delete a task\n4. View task description\n5. Exit\n";
		std::cin >> choice;

		if (choice == 1) {
			std::string name, description;
			std::cout << "Enter task name: ";
			std::cin.ignore(); // Clear the newline character from the input buffer
			std::getline(std::cin, name);
			std::cout << "Enter task description: ";
			std::getline(std::cin, description);
			myList.addTask(name, description);
		}
		else if (choice == 2) {
			int taskIndex;
			std::cout << "Enter task number to complete: ";
			std::cin >> taskIndex;
			myList.completeTask(taskIndex - 1); // Adjust for zero-based index
		}
		else if (choice == 3) {
			int taskIndex;
			std::cout << "Enter task number to delete: ";
			std::cin >> taskIndex;
			myList.deleteTask(taskIndex - 1); // Adjust for zero-based index
		}
		else if (choice == 4) {
			int taskIndex;
			std::cout << "Enter task number to view description: ";
			std::cin >> taskIndex;
			myList.viewTaskDescription(taskIndex - 1); // Adjust for zero-based index
		}
	} while (choice != 5);

	myList.saveToFile("tasks.txt"); // Save tasks to file
	return 0;
}
