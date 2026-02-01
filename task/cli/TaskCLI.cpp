#include "TaskCLI.hpp"

#define RED "\033[31m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

TaskCLI::TaskCLI(std::shared_ptr<TaskDao> dao,
                 std::shared_ptr<TaskService> service)
    : dao{dao}, service{service} {}

void TaskCLI::displayHelp() {
    std::cout << "\nExample usage" << std::endl;
    std::cout << "\t task-cli add \"[ DESCRIPTION OF THE TASK ]\"" << std::endl;
    std::cout << "\t task-cli update [ INDEX OF THE TASK ] \"[ DESCRiPTION OF "
                 "THE TASK ]\""
              << std::endl;

    std::cout << "\t task-cli delete [ INDEX OF THE TASK ]" << std::endl;
    std::cout << "\t task-cli mark-in-progress [ INDEX OF THE TASK ]"
              << std::endl;
    std::cout << "\t task-cli mark-done [ INDEX OF THE TASK ]" << std::endl;

    std::cout << "\t task-cli list" << std::endl;
    std::cout << "\t task-cli list [ SOME STATUS F.E 'todo', 'done', 'in "
                 "progress' ]\n"
              << std::endl;
}

void TaskCLI::help() { displayHelp(); }

void TaskCLI::add(int &id, std::string &description) {
    std::string status = "todo";

    Task newTask(id, description, status);

    dao->add(newTask);
    std::cout << GREEN << "Task added successfully (ID: " << id << ")" << RESET
              << std::endl;
}

void TaskCLI::list(std::string &status) {
    try {
        std::vector<Task> tasks = dao->getBuffer();
        service->printTasks(tasks, status);
    } catch (const std::string &ex) {
        std::cerr << RED << ex << RESET << std::endl;
    }
}

void TaskCLI::update(int &id, std::string &description) {
    try {
        std::vector<Task> tasks = dao->getBuffer();
        service->update(id, description, tasks);
        std::cout << GREEN << "Task updated successfully (ID: " << id << ")"
                  << RESET << std::endl;
    } catch (const std::string &ex) {
        std::cerr << RED << ex << RESET << std::endl;
    }
}

void TaskCLI::remove(int &id) {
    try {
        std::vector<Task> tasks = dao->getBuffer();
        service->remove(id, tasks);
        std::cout << GREEN << "Task deleted successfully (ID: " << id << ")"
                  << RESET << std::endl;
    } catch (const std::string &ex) {
        std::cerr << RED << ex << RESET << std::endl;
    }
}

void TaskCLI::markInProgress(int &id) {
    try {
        std::vector<Task> tasks = dao->getBuffer();
        service->markAs(id, "in-progress", tasks);
        std::cout << GREEN << "Updated status to 'in-progress' (ID: " << id
                  << ")" << RESET << std::endl;
    } catch (const std::string &ex) {
        std::cerr << RED << ex << RESET << std::endl;
    }
}

void TaskCLI::markDone(int &id) {
    try {
        std::vector<Task> tasks = dao->getBuffer();
        service->markAs(id, "done", tasks);
        std::cout << GREEN << "Updated status to 'done' (ID: " << id << ")"
                  << RESET << std::endl;
    } catch (const std::string &ex) {
        std::cerr << RED << ex << RESET << std::endl;
    }
}
