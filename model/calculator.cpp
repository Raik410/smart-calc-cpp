#include "calculator.hpp"

using namespace s21;

double Calculator::parser(const std::string& expression_str, double x_value) {
    if (!check_valid_brackets(expression_str)) {
        std::cout << "Use valid brackets.\n";
        return FAILED;
    }

    size_t expression_str_length = expression_str.length();
    double result = 0.0;

    for (size_t i = 0; i <= expression_str_length; i++) {
        parse_arithmetic(expression_str, i, x_value);
        parse_trigonometry(expression_str, i);
    }

    stack.head = sharting_yard();
    result = calc_sharting_yard();

    stack.clear_stack();

    return result;
}

bool Calculator::check_valid_brackets(const std::string& expression_str) {
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

void Calculator::parse_arithmetic (const std::string& expression, size_t& index, double x_value) {
    double value = 0.0;

    switch (expression[index]) {
        case '0' ... '9':
            append_number(expression, index, value);
            stack.push_left(value, Type::NUMBER, Priority::NUM);
            if (index + 1 < expression.length() && expression[index + 1] == '(')
                stack.push_left(value, Type::MUL, Priority::HIGH);
            break;
        case '+':
            if (index == 0 || expression[index - 1] == '(' || strchr("+-*/^%", expression[index - 1]))
                return;
            stack.push_left(0, Type::PLUS, Priority::LOW);
            break;
        case '-':
            if (index == 0 || expression[index - 1] == '(' || strchr("+-*/^% ", expression[index - 1]))
                stack.push_left(0, Type::UNARY_MINUS, Priority::UNARY);
            else
                stack.push_left(0, Type::MINUS, Priority::LOW);
            break;
        case '*':
            stack.push_left(0, Type::MUL, Priority::MID);
            break;
        case '/':
            stack.push_left(0, Type::DIV, Priority::MID);
            break;
        case '(':
            stack.push_left(0, Type::LEFT_BRACKET, Priority::BRACKET);
            break;
        case ')':
            stack.push_left(0, Type::RIGHT_BRACKET, Priority::BRACKET);
            break;
        case '%':
            stack.push_left(0, Type::MOD, Priority::HIGH);
            break;
        case '^':
            stack.push_left(0, Type::POW, Priority::HIGH);
            break;
        case 'x':
            stack.push_left(x_value, Type::NUMBER, Priority::NUM);
            break;
        default:
            break;
    }
}

void Calculator::parse_trigonometry(const std::string& expression, size_t& index) {
    switch (expression[index]) {
        case 's':
            if (expression.substr(index, 3) == "sin") {
                stack.push_left(0, Type::SIN, Priority::HIGH);
                index += 2;
            } else if (expression.substr(index, 4) == "sqrt") {
                stack.push_left(0, Type::SQRT, Priority::HIGH);
                index += 3;
            }
            break;
        case 'c':
            if (expression.substr(index, 3) == "cos") {
                stack.push_left(0, Type::COS, Priority::HIGH);
                index += 2;
            }
            break;
        case 't':
            if (expression.substr(index, 3) == "tan") {
                stack.push_left(0, Type::TAN, Priority::HIGH);
                index += 2;
            }
            break;
        case 'a':
            if (expression.substr(index, 4) == "acos") {
                stack.push_left(0, Type::ACOS, Priority::HIGH);
                index += 3;
            } else if (expression.substr(index, 4) == "atan") {
                stack.push_left(0, Type::ATAN, Priority::HIGH);
                index += 3;
            } else if (expression.substr(index, 4) == "asin") {
                stack.push_left(0, Type::ASIN, Priority::HIGH);
                index += 3;
            }
            break;
        case 'l':
            if (expression.substr(index, 2) == "ln") {
                stack.push_left(0, Type::LN, Priority::HIGH);
                index += 1;
            } else if (expression.substr(index, 3) == "log") {
                stack.push_left(0, Type::LOG, Priority::HIGH);
                index += 2;
            }
            break;
        default:
            break;
    }
}

void Calculator::append_number(const std::string& expression, size_t& index, double& value) {
    size_t next_index;
    value = std::stod(expression.substr(index), &next_index);
    index += next_index - 1;
}

std::shared_ptr<Node> Calculator::sharting_yard() {
    Stack supportStack;
    Stack outputStack;
    std::shared_ptr<Node> current = stack.tail;

    while (current != nullptr) {
        if (current->type == Type::NUMBER || current->type == Type::X) {
            outputStack.push_right(current->data, current->type, current->priority);
        } else if (current->type == Type::LEFT_BRACKET || all_trigonometry_operation(current) || Type::UNARY_MINUS == current->type) {
            supportStack.push_right(current->data, current->type, current->priority);
        } else if (all_arithmetic_operation(current)) {
            while (!supportStack.isEmpty() && current->priority <= supportStack.peek_right()->priority && current->type != Type::POW) {
                auto node = supportStack.pop_tail();
                outputStack.push_right(node->data, node->type, node->priority);
            }
            supportStack.push_right(current->data, current->type, current->priority);
        } else if (current->type == Type::RIGHT_BRACKET) {
            while (supportStack.peek_right()->type != Type::LEFT_BRACKET) {
                auto node = supportStack.pop_tail();
                outputStack.push_right(node->data, node->type, node->priority);
            }
            supportStack.pop_tail();  // Remove the left bracket

            if (!supportStack.isEmpty() && all_trigonometry_operation(supportStack.peek_right())) {
                auto node = supportStack.pop_tail();
                outputStack.push_right(node->data, node->type, node->priority);
            }
        }

        current = current->prev;
    }

    while (!supportStack.isEmpty()) {
        auto node = supportStack.pop_tail();
        outputStack.push_right(node->data, node->type, node->priority);
    }

    return outputStack.head;
}

bool Calculator::all_arithmetic_operation(std::shared_ptr<Node> node) {
    return ((node->type >= Type::PLUS && node->type <= Type::MOD) || (node->type == Type::UNARY_MINUS));
}

bool Calculator::all_trigonometry_operation(std::shared_ptr<Node> node) {
    return (node->type >= Type::COS && node->type <= Type::LOG);
}

double Calculator::calc_sharting_yard() {
    Stack calculationStack;
    std::shared_ptr<Node> current = stack.head;
    double a = 0, b = 0, c = 0, result = 0;

    while (current != nullptr) {
        if (current->type == Type::NUMBER) {
            calculationStack.push_right(current->data, current->type, current->priority);
        } else if (current->type >= Type::PLUS && current->type <= Type::MOD) {
            b = calculationStack.pop_tail()->data;
            if (calculationStack.isEmpty()) {
                result = 0;
                return result;
            }
            a = calculationStack.pop_tail()->data;
            arithmetic_calculation(calculationStack, current, result, a, b);
        } else if ((current->type >= Type::COS && current->type <= Type::LOG) || current->type == Type::UNARY_MINUS) {
            c = calculationStack.pop_tail()->data;
            trigonometry_calculation(calculationStack, current, result, c);
        }
        current = current->next;
    }

    result = calculationStack.pop_head()->data;
    return result;
}

void Calculator::arithmetic_calculation(Stack& calculationStack, std::shared_ptr<Node> operation, double& result, double a, double b) {
    switch (operation->type) {
        case Type::PLUS:
            result = a + b;
            break;
        case Type::MINUS:
            result = a - b;
            break;
        case Type::MUL:
            result = a * b;
            break;
        case Type::DIV:
            if (b != 0) result = a / b;
            else throw std::runtime_error("Division by zero");
            break;
        case Type::POW:
            result = pow(a, b);
            break;
        case Type::MOD:
            result = fmod(a, b);
            break;
        default:
            break;
    }
    calculationStack.push_right(result, Type::NUMBER, Priority::NUM);
}

void Calculator::trigonometry_calculation(Stack& calculationStack, std::shared_ptr<Node> operation, double& result, double c) {
    switch (operation->type) {
        case Type::UNARY_MINUS:
            result = -c;
            break;
        case Type::SIN:
            result = sin(c);
            break;
        case Type::COS:
            result = cos(c);
            break;
        case Type::TAN:
            result = tan(c);
            break;
        case Type::ACOS:
            result = acos(c);
            break;
        case Type::ASIN:
            result = asin(c);
            break;
        case Type::ATAN:
            result = atan(c);
            break;
        case Type::SQRT:
            result = sqrt(c);
            break;
        case Type::LN:
            result = log(c);
            break;
        case Type::LOG:
            result = log10(c);
            break;
        default:
            break;
    }
    calculationStack.push_right(result, Type::NUMBER, Priority::NUM);
}
