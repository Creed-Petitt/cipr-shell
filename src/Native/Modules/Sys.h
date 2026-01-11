#ifndef CIPR_NATIVE_SYS_H
#define CIPR_NATIVE_SYS_H

#include "Interpreter/Callable.h"
#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <signal.h>

struct NativePs final : Callable {
    int arity() override {
      return 0;
    }

    Literal call(Interpreter&, const std::vector<Literal>) override {
        auto list = std::make_shared<LiteralVector>();
        try {
            for (const auto& entry : std::filesystem::directory_iterator("/proc")) {
                if (!entry.is_directory())
                    continue;

                const auto pid_str = entry.path().filename().string();
                if (!std::all_of(pid_str.begin(), pid_str.end(), ::isdigit))
                    continue;

                std::ifstream comm_file(entry.path() / "comm");
                if (std::string name; comm_file >> name) {
                    list->elements.emplace_back(pid_str + ": " + name);
                }
            }
        } catch (...) {
            return std::monostate{};
        }
        return list;
    }

    std::string toString() override {
      return "<native fn ps>";
    }
};

struct NativeKill final : Callable {
    int arity() override {
      return 1;
    }

    Literal call(Interpreter&, const std::vector<Literal> args) override {
        if (!std::holds_alternative<double>(args[0]))
          return false;
        
        const auto pid = static_cast<int>(std::get<double>(args[0]));
        return kill(pid, SIGTERM) == 0;
    }

    std::string toString() override {
      return "<native fn kill>";
    }
};

#endif