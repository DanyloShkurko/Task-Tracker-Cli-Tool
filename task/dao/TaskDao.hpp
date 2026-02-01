#pragma once

#include "../Task.hpp"
#include <fstream>
#include <memory>
#include <string>
#include <vector>

class TaskDao {
  private:
    std::unique_ptr<std::ifstream> in;
    std::unique_ptr<std::ofstream> out;
    std::unique_ptr<std::vector<Task>> buffer;

  public:
    TaskDao() = default;
    TaskDao(std::string &&destionation);
    ~TaskDao();

    const std::vector<Task> &getBuffer() const;
    void add(const Task &task);
    void write() const;
    void read();
};
