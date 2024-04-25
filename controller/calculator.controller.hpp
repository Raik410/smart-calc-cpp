#include "../model/calculator.hpp"
#include "../model/credit.hpp"

using namespace s21;

class CalculatorController {
public:

    CalculatorController() = default;
    ~CalculatorController() = default;
    
    double calculateExpression(const std::string& expression, double xValue) {
        Calculator calculator;
        return calculator.parser(expression, xValue);
    }

    Credit_output credit_calculator(Credit_params credit_params) {
        CreditCalculator calculator;
        return calculator.credit_calculator(credit_params);
    }
};