#include "TaskDao.hpp"
#include "../Task.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

TaskDao::TaskDao(std::string &&destionation) {
    in = std::make_unique<std::ifstream>();
    out = std::make_unique<std::ofstream>();
    buffer = std::make_unique<std::vector<Task>>();
    in->open(destionation);
    if (!in->is_open()) {
        throw("Invalid file destination '" + destionation +
              "'! Please, ensure it exists.\n");
    }
    read();

    out->open(destionation, std::ios::out);
}

TaskDao::~TaskDao() {
    in->close();
    out->close();
}

void TaskDao::read() {
    if (in->is_open()) {
        std::string line;

        while (std::getline(*in, line)) {
            std::stringstream sl(line);
            std::string cell;
            std::vector<std::string> temp;
            Task task;

            while (std::getline(sl, cell, '|')) {
                temp.push_back(cell);
            }

            int id = std::stoi(temp[0]);
            std::string description = temp[1];
            std::string status = temp[2];
            std::string createdAt = temp[3];
            std::string updatedAt = temp[4];

            task.setId(id);
            task.setDescription(description);
            task.setStatus(status);
            task.setCreatedAt(createdAt);
            task.setUpdatedAt(updatedAt);

            buffer->push_back(task);
        }
    }
}

void TaskDao::write() const {
    if (out->is_open()) {
        for (size_t i = 0; i < buffer->size(); i++) {
            (*out) << std::to_string((*buffer)[i].getId()) << '|'
                   << (*buffer)[i].getDescription() << '|'
                   << (*buffer)[i].getStatus() << '|'
                   << (*buffer)[i].getCreatedAt() << '|'
                   << (*buffer)[i].getUpdatedAt() << std::endl;
        }
    }
}

const std::vector<Task> &TaskDao::getBuffer() const { return (*buffer); }
void TaskDao::add(const Task &task) { buffer->push_back(task); }
