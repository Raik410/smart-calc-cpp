#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>
#include <memory>
#include <cctype>
#include <cstring>
#include <cmath>
#include <iostream>
#include "stack.hpp"

typedef enum {
  OK = 0,
  FAILED = 1,
  MEMORY_FAILED_ALLOCATED = 2,
} Output;

class Calculator {
public:
    Calculator() = default;

    double parser(const std::string& expression_str, double x_value);

    void append_number(const std::string& expression_str, size_t& index, double& value);
    std::shared_ptr<Node> sharting_yard(std::shared_ptr<Node> head, std::shared_ptr<Node> tail);
    double calc_sharting_yard(std::shared_ptr<Node> head);
    void arithmetic_calculation(Stack& calculationStack, std::shared_ptr<Node> operation, double& result, double a, double b);
    void trigonometry_calculation(Stack& calculationStack, std::shared_ptr<Node> operation, double& result, double c);
    void parse_trigonometry(std::shared_ptr<Node>& head, std::shared_ptr<Node>& tail, const std::string& expression_str, size_t& index);
    void parse_arithmetic(std::shared_ptr<Node>& head, std::shared_ptr<Node>& tail, const std::string& expression_str, size_t& index, double x_value);
    bool all_arithmetic_operation(std::shared_ptr<Node> node);
    bool all_trigonometry_operation(std::shared_ptr<Node> node);
    bool check_valid_brackets(const std::string& expression_str);

private:
    Stack stack;
};

#endif // CALCULATOR_HPP
