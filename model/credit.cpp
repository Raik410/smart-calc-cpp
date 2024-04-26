#include "credit.hpp"

#include "calculator.hpp"

Credit_output CreditCalculator::credit_calculator(
    const Credit_params& credit_params) {
  Credit_output credit_result = {0};
  double average_days_per_month = 365.2425 / 12;
  double monthly_rate = (credit_params.interest_rate / 100.0) / 12.0 *
                        (30.445 / average_days_per_month);

  if (credit_params.annuity) {
    credit_result.monthly_payment =
        credit_params.sum_credit * monthly_rate /
        (1 - std::pow(1 + monthly_rate, -credit_params.term_credit));
    credit_result.total_payout =
        credit_result.monthly_payment * credit_params.term_credit;
    credit_result.overpayment =
        credit_result.total_payout - credit_params.sum_credit;
  }

  if (credit_params.differentiated) {
    double principal_payment =
        credit_params.sum_credit / credit_params.term_credit;
    credit_result.max_payment =
        principal_payment + (credit_params.sum_credit * monthly_rate);
    credit_result.min_payment =
        principal_payment + (principal_payment * monthly_rate);

    double total_interest = 0;
    for (int month = 1; month <= credit_params.term_credit; month++) {
      total_interest +=
          (credit_params.sum_credit - principal_payment * (month - 1)) *
          monthly_rate;
    }
    credit_result.total_payout = credit_params.sum_credit + total_interest;
    credit_result.overpayment = total_interest;
  }

  return credit_result;
}