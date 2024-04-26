#ifndef CREDIT_HPP
#define CREDIT_HPP

struct Credit_params {
  double sum_credit;
  int term_credit;
  int interest_rate;
  bool annuity;
  bool differentiated;
};

struct Credit_output {
  double monthly_payment;
  double overpayment;
  double total_payout;
  double min_payment;
  double max_payment;
};

class CreditCalculator {
 public:
  CreditCalculator() = default;
  ~CreditCalculator() = default;

  Credit_output credit_calculator(const Credit_params& credit_params);
};

#endif  // CREDIT_HPP
