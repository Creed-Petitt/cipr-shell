#ifndef CIPR_NATIVE_STRING_H
#define CIPR_NATIVE_STRING_H

#include "Interpreter/Callable.h"
#include "Token/Token.h" // For LiteralVector
#include <algorithm>
#include <cctype>

struct NativeSize final : Callable {
    int arity() override {
        return 1;
    }

    Literal call(Interpreter&, const std::vector<Literal> args) override {
        if (std::holds_alternative<std::shared_ptr<LiteralVector>>(args[0]))
            return static_cast<double>(std::get<std::shared_ptr<LiteralVector> >(args[0])->elements.size());
        if (std::holds_alternative<std::string>(args[0]))
            return static_cast<double>(std::get<std::string>(args[0]).length());
        return 0.0;
    }

    std::string toString() override {
        return "<native fn size>";
    }
};

struct NativeTrim final : Callable {
    int arity() override {
        return 1;
    }

    Literal call(Interpreter&, std::vector<Literal> args) override {
        if (!std::holds_alternative<std::string>(args[0])) return args[0];
        auto s = std::get<std::string>(args[0]);
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](const unsigned char ch) {
            return !std::isspace(ch);
        }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [](const unsigned char ch) {
            return !std::isspace(ch);
        }).base(), s.end());
        return s;
    }

    std::string toString() override {
        return "<native fn trim>";
    }
};

struct NativeSplit final : Callable {
    int arity() override {
        return 2;
    }

    Literal call(Interpreter&, const std::vector<Literal> args) override {
        if (!std::holds_alternative<std::string>(args[0]) || !std::holds_alternative<std::string>(args[1])) 
            return std::make_shared<LiteralVector>();
        auto s = std::get<std::string>(args[0]);
        const auto d = std::get<std::string>(args[1]);
        auto res = std::make_shared<LiteralVector>();
        size_t pos = 0;
        while ((pos = s.find(d)) != std::string::npos) {
            res->elements.emplace_back(s.substr(0, pos));
            s.erase(0, pos + d.length());
        }
        res->elements.emplace_back(s);
        return res;
    }

    std::string toString() override {
        return "<native fn split>";
    }
};

#endif