#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <cctype>
#include <cmath>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

#include "stack.hpp"

namespace s21 {

typedef enum {
  OK = 0,
  FAILED = 1,
  MEMORY_FAILED_ALLOCATED = 2,
} Output;

class Calculator {
 public:
  Calculator() = default;
  ~Calculator() = default;

  double parser(const std::string& expression_str, double x_value);

  void append_number(const std::string& expression_str, size_t& index,
                     double& value);
  std::shared_ptr<Node> sharting_yard() {
    Stack supportStack;
    Stack outputStack;
    std::shared_ptr<Node> current = stack.tail;

    while (current != nullptr) {
      if (current->type == Type::NUMBER || current->type == Type::X) {
        outputStack.push_right(current->data, current->type, current->priority);
      } else if (current->type == Type::LEFT_BRACKET ||
                 all_trigonometry_operation(current) ||
                 Type::UNARY_MINUS == current->type) {
        supportStack.push_right(current->data, current->type,
                                current->priority);
      } else if (all_arithmetic_operation(current)) {
        while (!supportStack.isEmpty() &&
               current->priority <= supportStack.peek_right()->priority &&
               current->type != Type::POW) {
          auto node = supportStack.pop_tail();
          outputStack.push_right(node->data, node->type, node->priority);
        }
        supportStack.push_right(current->data, current->type,
                                current->priority);
      } else if (current->type == Type::RIGHT_BRACKET) {
        while (supportStack.peek_right()->type != Type::LEFT_BRACKET) {
          auto node = supportStack.pop_tail();
          outputStack.push_right(node->data, node->type, node->priority);
        }
        supportStack.pop_tail();  // Remove the left bracket

        if (!supportStack.isEmpty() &&
            all_trigonometry_operation(supportStack.peek_right())) {
          auto node = supportStack.pop_tail();
          outputStack.push_right(node->data, node->type, node->priority);
        }
      }

      current = (current->prev).lock();  //
    }

    while (!supportStack.isEmpty()) {
      auto node = supportStack.pop_tail();
      outputStack.push_right(node->data, node->type, node->priority);
    }

    supportStack.clear_stack();

    return outputStack.head;
  }
  double calc_sharting_yard();
  void arithmetic_calculation(Stack& calculationStack,
                              std::shared_ptr<Node> operation, double& result,
                              double a, double b);
  void trigonometry_calculation(Stack& calculationStack,
                                std::shared_ptr<Node> operation, double& result,
                                double c);
  void parse_trigonometry(const std::string& expression_str, size_t& index);
  void parse_arithmetic(const std::string& expression_str, size_t& index,
                        double x_value);
  bool all_arithmetic_operation(std::shared_ptr<Node> node);
  bool all_trigonometry_operation(std::shared_ptr<Node> node);

  // Validation
  bool check_valid_brackets(const std::string& expression_str) {
    Stack localStack;
    for (char ch : expression_str) {
      if (ch == '(') {
        localStack.push_left(0, Type::LEFT_BRACKET, Priority::BRACKET);
      } else if (ch == ')') {
        if (localStack.isEmpty()) {
          return false;
        }
        localStack.pop_head();
      }
    }

    return localStack.isEmpty();
  }

 private:
  Stack stack;
};

};  // namespace s21

#endif  // CALCULATOR_HPP
