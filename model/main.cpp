#include "calculator.hpp"
#include "../controller/calculator.controller.hpp"

int main() {
    // Stack stack;

    // // Добавление элементов в стек
    // stack.push_left(1.0, Type::NUMBER, Priority::NUM);
    // stack.push_left(2.0, Type::PLUS, Priority::LOW);
    // stack.push_left(3.0, Type::NUMBER, Priority::NUM);
    // stack.push_right(4.0, Type::MUL, Priority::MID);
    // stack.push_right(5.0, Type::NUMBER, Priority::NUM);

    // // Вывод содержимого стека
    // std::cout << "Initial stack state:\n";
    // stack.printStack();

    // // Удаление элемента с головы стека
    // std::cout << "\nPopping head:\n";
    // stack.pop_head();
    // stack.printStack();

    // // Удаление элемента с хвоста стека
    // std::cout << "\nPopping tail:\n";
    // stack.pop_tail();
    // stack.printStack();

    // // Очистка всего стека
    // std::cout << "\nClearing stack:\n";
    // stack.clear_stack();
    // stack.printStack();

    // Calculator calc;

    // std::string expression_str = "yebal228/23////";
    
    // double x = 0;

    // double result = calc.parser(expression_str, x);

    // std::cout << "Result " << result;

    // return 0;

    CalculatorController CalculatorController;
    std::string input = "2^-3+0.875";
    double result = CalculatorController.calculateExpression(input, 0);
    // EXPECT_NEAR(result, 1, 1e-07);

    return 0;
}
