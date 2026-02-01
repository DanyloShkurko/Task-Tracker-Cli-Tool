#include "Application.hpp"
#include "task/cli/TaskCLI.hpp"
#include "task/dao/TaskDao.hpp"
#include "task/service/TaskService.hpp"
#include <getopt.h>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <string>
#include <unistd.h>

#define RED "\033[31m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

void Application::run(int &argc, char *argv[]) {
    try {
        std::shared_ptr<TaskDao> dao = std::make_shared<TaskDao>("tasks.txt");
        std::shared_ptr<TaskService> service = std::make_shared<TaskService>();

        TaskCLI cliHelper(dao, service);

        std::string opt = argc > 1 ? argv[1] : "";

        if (opt.find("help") != std::string::npos ||
            opt.find("-h") != std::string::npos) {

            cliHelper.help();

        } else if (opt == "add" && argc == 3) {

            int id =
                dao->getBuffer().empty()
                    ? 1
                    : dao->getBuffer()[dao->getBuffer().size() - 1].getId() + 1;

            std::string description = argv[2];

            cliHelper.add(id, description);

        } else if (opt == "list") {
            std::string status = (argc == 3 ? argv[2] : "");

            cliHelper.list(status);

        } else if (opt == "update" && argc == 4) {
            try {
                int id = std::stoi(argv[2]);
                std::string desc = argv[3];

                cliHelper.update(id, desc);

            } catch (const std::invalid_argument &ex) {
                std::cerr << RED << "Invalid argument type!" << RESET
                          << std::endl;
            }
        } else if (opt == "delete" && argc == 3) {

            try {
                int id = std::stoi(argv[2]);

                cliHelper.remove(id);
            } catch (const std::invalid_argument &ex) {
                std::cerr << RED << "Invalid argument type!" << RESET
                          << std::endl;
            }
        } else if (opt == "mark-in-progress" && argc == 3) {

            try {
                int id = std::stoi(argv[2]);

                cliHelper.markInProgress(id);

            } catch (const std::invalid_argument &ex) {
                std::cerr << RED << "Invalid argument type!" << RESET
                          << std::endl;
            }

        } else if (opt == "mark-done" && argc == 3) {

            try {
                int id = std::stoi(argv[2]);

                cliHelper.markDone(id);

            } catch (const std::invalid_argument &ex) {
                std::cerr << RED << "Invalid argument type!" << RESET
                          << std::endl;
            }
        } else {
            std::cout << YELLOW
                      << "To see available options please use 'task-cli help'"
                      << RESET << std::endl;
        }

    } catch (const std::string &ex) {
        std::cerr << RED << ex << RESET << std::endl;
    }
}
