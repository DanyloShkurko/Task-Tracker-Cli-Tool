#include "Task.hpp"
#include "utils/TaskUtils.hpp"
#include <ctime>
#include <ostream>
#include <string>

TaskUtils Task::utils;

int Task::getId() const { return this->id; }
void Task::setId(int &id) {
    if (id >= 0) {
        this->id = id;
    }
}

std::string Task::getDescription() const { return this->description; }
void Task::setDescription(std::string &description) {
    if (!description.empty()) {
        this->description = description;
    }
}

std::string Task::getStatus() const { return this->status; }
void Task::setStatus(std::string &status) {
    if (status == "todo" || status == "in-progress" || status == "done") {
        this->status = status;
    }
}

std::string Task::getCreatedAt() const { return this->createdAt; }
void Task::setCreatedAt(std::string &createdAt) {
    if (!createdAt.empty()) {
        this->createdAt = createdAt;
    } else {
        this->createdAt = "Does not have creation date";
    }
}

std::string Task::getUpdatedAt() const { return this->updatedAt; }
void Task::setUpdatedAt(std::time_t &updatedAt) {
    std::time_t t = std::time(0);

    std::tm *upd = std::localtime(&updatedAt);

    this->updatedAt = utils.dateToString(upd);
}
void Task::setUpdatedAt(std::string &updatedAt) {
    if (!updatedAt.empty()) {
        this->updatedAt = updatedAt;
    } else {
        this->updatedAt = "Was not modified yet";
    }
}

Task::Task(int &id, std::string &description, std::string &status) {
    setId(id);
    setDescription(description);
    setStatus(status);
    std::time_t now = std::time(0);
    this->createdAt = utils.dateToString(std::localtime(&now));
    setUpdatedAt(now);
}

std::ostream &operator<<(std::ostream &os, const Task &task) {
    if (task.getStatus() == "done") {
        os << "✅ ✅ ✅ ✅ ✅ ✅" << std::endl;
    } else if (task.getStatus() == "todo") {
        os << "❌ ❌ ❌ ❌ ❌ ❌" << std::endl;
    } else {
        os << "[================>                ]" << std::endl;
    }

    std::string created = task.getCreatedAt();

    std::string updated = task.getUpdatedAt();

    os << "\n\t• Id: " << task.getId() << "\n\n";
    ;
    os << "\t• Description: " << task.getDescription() << "\n\n";
    os << "\t• Created: " << created << "\n\n";
    os << "\t• Updated: " << updated << "\n\n";

    if (task.getStatus() == "done") {
        os << "✅ ✅ ✅ ✅ ✅ ✅" << std::endl;
    } else if (task.getStatus() == "todo") {
        os << "❌ ❌ ❌ ❌ ❌ ❌" << std::endl;
    } else {
        os << "[================>                ]" << std::endl;
    }
    return os;
}
