#include <gtest/gtest.h>
#include <cmath>

#include "../controller/calculator.controller.hpp"
#include "../model/credit.hpp"

using namespace s21;
using std::string;

TEST(CalculationTest, Test1) {
    CalculatorController CalculatorController;
    string input = "3+4*2/(1-5)^2";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_DOUBLE_EQ(result, 3.5);
}

TEST(CalculationTest, TestBrackets) {
    CalculatorController CalculatorController;
    string input = "((((3+4*2/(1-5)^2";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_DOUBLE_EQ(result, 1);
}

TEST(CalculationTest, Test2) {
    CalculatorController CalculatorController;
    string input = "1+2+3+4*5*6^7";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_EQ((int)result, 5598726);
}

TEST(CalculationTest, TestPercent) {
    CalculatorController CalculatorController;
    string input = "2%2";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_EQ((int)result, 0);
}

TEST(CalculationTest, Test3) {
    CalculatorController CalculatorController;
    string input = "123.456+2*3^4";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_DOUBLE_EQ(result, 285.456);
}

TEST(CalculationTest, Test4) {
    CalculatorController CalculatorController;
    string input = "(8+2*5)/(1+3*2-4)";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_DOUBLE_EQ(result, 6);
}

TEST(CalculationTest, Test5) {
    CalculatorController CalculatorController;
    string input =
        "(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/"
        "2)))";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_DOUBLE_EQ(result, 10);
}

TEST(CalculationTest, Test6) {
    CalculatorController CalculatorController;
    string input = "cos(1*2)-1";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_NEAR(result, -1.41614683655, 1e-07);
}

TEST(CalculationTest, Test7) {
    CalculatorController CalculatorController;
    string input =
        "cos(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/"
        "2)))-1";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_NEAR(result, -1.83907152908, 1e-07);
}

TEST(CalculationTest, Test8) {
    CalculatorController CalculatorController;
    string input = "sin(cos(5))";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_NEAR(result, 0.27987335076, 1e-07);
}

TEST(CalculationTest, Test10) {
    CalculatorController CalculatorController;
    string input = "3+4*2/1-5+2^2";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_NEAR(result, 10, 1e-07);
}

TEST(CalculationTest, Test11) {
    CalculatorController CalculatorController;
    double x = 0.0003;
    string input = "asin(2*x)";
    double result = CalculatorController.calculateExpression(input, x);
    EXPECT_NEAR(result, asin(2*x), 1e-07);
}

TEST(CalculationTest, Test12) {
    CalculatorController CalculatorController;
    double x = 0.0019;
    string input = "acos(2*x)";
    double result = CalculatorController.calculateExpression(input, x);
    EXPECT_NEAR(result, 1.567, 1e-03);
}

TEST(CalculationTest, Test13) {
    CalculatorController CalculatorController;
    double x = 0.0019;
    string input = "atan(2*x)";
    double result = CalculatorController.calculateExpression(input, x);
    EXPECT_NEAR(result, 0.00379998, 1e-07);
}

TEST(CalculationTest, Test14) {
    CalculatorController CalculatorController;
    double x = 0.004;
    string input = "tan(2*x)";
    double result = CalculatorController.calculateExpression(input, x);
    EXPECT_NEAR(result, 0.00800017, 1e-07);
}

TEST(CalculationTest, Test15) {
    CalculatorController CalculatorController;
    double x = 25;
    string input = "sqrt(2*x)";
    double result = CalculatorController.calculateExpression(input, x);
    EXPECT_NEAR(result, 7.07107, 1e-05);
}

TEST(CalculationTest, Test16) {
    CalculatorController CalculatorController;
    double x = 2;
    string input = "ln(10*x)";
    double result = CalculatorController.calculateExpression(input, x);
    EXPECT_NEAR(result, 2.99573, 1e-05);
}

TEST(CalculationTest, Test17) {
    CalculatorController CalculatorController;
    double x = 2;
    string input = "log(10*x)";
    double result = CalculatorController.calculateExpression(input, x);
    EXPECT_NEAR(result, 1.30103, 1e-05);
}


TEST(CalculationTest, Test18) {
    CalculatorController CalculatorController;
    string input = "3-(-3)";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_NEAR(result, 6, 1e-07);
}

TEST(CalculationTest, Test20) {
    CalculatorController CalculatorController;
    string input = "3-(+3)";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_NEAR(result, 0, 1e-07);
}

TEST(CalculationTest, Test21) {
    CalculatorController CalculatorController;
    string input = "2^2^3";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_DOUBLE_EQ(result, 256);
}

TEST(CalculationTest, Test22) {
    CalculatorController CalculatorController;
    string input = "-5+2*3";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_NEAR(result, 1, 1e-07);
}

TEST(CalculationTest, Test23) {
    CalculatorController CalculatorController;
    string input = "3*-2+6";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_NEAR(result, 0, 1e-07);
}

TEST(CalculationTest, Test24) {
    CalculatorController CalculatorController;
    string input = "2^-3+0.875";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_NEAR(result, 1, 1e-07);
}

TEST(CalculationTest, Test25) {
    CalculatorController CalculatorController;
    string input = "2*cos(5)+5";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_NEAR(result, 5.5673244, 1e-07);
}

TEST(CalculationTest, Test26) {
    CalculatorController CalculatorController;
    string input = "1.25+3.45";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ(1.25 + 3.45, result);
}

TEST(CalculationTest, Test27) {
    CalculatorController CalculatorController;
    string input = "1.25-3.45";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ(1.25 - 3.45, result);
}

TEST(CalculationTest, Test28) {
    CalculatorController CalculatorController;
    string input = "1.25*3.45";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ(1.25 * 3.45, result);
}

TEST(CalculationTest, Test29) {
    CalculatorController CalculatorController;
    string input = "3*(4+7)";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ(3 * (4 + 7), result);
}

TEST(CalculationTest, Test30) {
    CalculatorController CalculatorController;
    string input = "1.25/3.45";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ(1.25 / 3.45, result);
}

TEST(CalculationTest, Test31) {
    CalculatorController CalculatorController;
    string input = "1.25mod3.45";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ(fmod(1.25, 3.45), result);
}

TEST(CalculationTest, Test32) {
    CalculatorController CalculatorController;
    string input = "1.25^3.45";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ(powf(1.25, 3.45), result);
}

TEST(CalculationTest, Test33) {
    CalculatorController CalculatorController;
    string input = "x";
    double result = CalculatorController.calculateExpression(input, 2.22);
    EXPECT_FLOAT_EQ(2.22, result);
}

TEST(CalculationTest, Test34) {
    CalculatorController CalculatorController;
    string input = "(+5.23+1.25)*(0.25+0.001)";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ((5.23 + 1.25) * (0.25 + 0.001), result);
}

TEST(CalculationTest, Test35) {
    CalculatorController CalculatorController;
    string input = "sin((5.23+1.25)*(0.25+0.001))";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ(sin((5.23 + 1.25) * (0.25 + 0.001)), result);
}

TEST(CalculationTest, Test36) {
    CalculatorController CalculatorController;
    string input = "cos((5.23+1.25)*(0.25+0.001))";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ(cos((5.23 + 1.25) * (0.25 + 0.001)), result);
}

TEST(CalculationTest, Test37) {
    CalculatorController CalculatorController;
    string input = "tan((5.23+1.25)*(0.25+0.001))";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ(tan((5.23 + 1.25) * (0.25 + 0.001)), result);
}

TEST(CalculationTest, Test38) {
    CalculatorController CalculatorController;
    string input = "asin(7/7.7)";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ(asin(7 / 7.7), result);
}

TEST(CalculationTest, Test39) {
    CalculatorController CalculatorController;
    string input = "acos(7/7.7)";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ(acos(7 / 7.7), result);
}

TEST(CalculationTest, Test40) {
    CalculatorController CalculatorController;
    string input = "atan(7/7.7)";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ(atan(7 / 7.7), result);
}

TEST(CalculationTest, Test41) {
    CalculatorController CalculatorController;
    string input = "sqrt(1357-245)";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ(sqrt(1357 - 245), result);
}

TEST(CalculationTest, Test42) {
    CalculatorController CalculatorController;
    string input = "ln(1357-245)";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ(log(1357 - 245), result);
}

TEST(CalculationTest, Test43) {
    CalculatorController CalculatorController;
    string input = "log(1357-245)";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ(log10(1357 - 245), result);
}

TEST(CalculationTest, Test44) {
    CalculatorController CalculatorController;
    string input = "log(32+1)*7/11*432*(sin(2)*12-45+4)/2";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ(log10(32 + 1) * 7 / 11 * 432 * (sin(2) * 12 - 45 + 4) / 2,
                    result);
}

TEST(CalculationTest, Test45) {
    CalculatorController CalculatorController;
    string input = "cos(sin(tan(-0.005)))";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_FLOAT_EQ(cos(sin(tan(-0.005))), result);
}

TEST(CalculationTest, Test46) {
    CalculatorController CalculatorController;
    string input = "(-1)^2-(-1^2)";
    double result = CalculatorController.calculateExpression(input, 0);
    EXPECT_DOUBLE_EQ(result, 2);
}

TEST(CreditCalculatorTest, AnnuityPaymentTest) {
    CalculatorController CalculatorController;
    Credit_params params = {1000, 5, 5, true, false}; // сумма в кредите, срок в месяцах, процентная ставка, аннуитетный, дифференцированный
    Credit_output output = CalculatorController.credit_calculator(params);

    EXPECT_NEAR(output.monthly_payment, 202.51, 1e-02);
    EXPECT_NEAR(output.total_payout, 1012.54, 1e-02);
    EXPECT_NEAR(output.overpayment, 12.54, 1e-02);
}

TEST(CreditCalculatorTest, DifferentiatedPaymentTest) {
    CalculatorController CalculatorController;
    Credit_params params = {1000, 5, 5, false, true}; // сумма в кредите, срок в месяцах, процентная ставка, аннуитетный, дифференцированный
    Credit_output output = CalculatorController.credit_calculator(params);

    EXPECT_NEAR(output.max_payment, 204.17, 1e-01);
    EXPECT_NEAR(output.min_payment, 200.83, 1e-01);
    EXPECT_NEAR(output.total_payout, 1012.50, 1e-01);
    EXPECT_NEAR(output.overpayment, 12.50, 1e-01);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
