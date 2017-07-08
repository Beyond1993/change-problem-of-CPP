/* ---------------------------------------------------------------------------------
 Thank you for your interest in software development at Ansys.

 As a rough gauge of your programming ability, we would like to see
 you deal with a relatively simple example.

 Below is a C++ class that represents a cash register.  The public
 MakeChange method is intended to mimic the actions of the salesperson
 who has accepted money from the customer and must return the difference.

 Please implement that method.

 We are looking for the ability to define and implement an algorithm.
 Dealing with error conditions is important as is style and readability.

 Most of the details are irrelevant and should be unimportant.  But if you feel
 it improves your code, you may add utility methods as needed.
 ---------------------------------------------------------------------------------
 @author Wayne Feng
 @Date 03/15/2017
 */
#include <map>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <string>
class CashRegister {
 public:
  CashRegister();
  ~CashRegister();
  // the customer has paid money,
  // that money is already in the till
  // Now, dispense change
  void MakeChange(double amountPaid, double amountOwed);

 private:
  // the cash register holds zero or more of these
  // bills and coins in the Till.
  // The value of the enum is its worth in cents
  enum denomination {
    kPenny = 1,
    kNickel = 5,
    kDime = 10,
    kQuarter = 25,
    kHalf = 50,
    kDollar = 100,
    kFive = 500,
    kTen = 1000,
    kTwenty = 2000,
    kFifty = 5000,
    kHundred = 10000
  };
  // This is the till.  All bills and coins are stored here
  std::map<denomination, int> mTill;

  // This is the LCD display on the cash register
  std::ostream mDisplay;

 private:
  // how much money is in the cash register?
  double TotalInRegister() const;

  // there is a problem!
  void ReportError(const char* text);

  // remove coins/bills from the till and give them to the customer
  void Dispense(denomination d, int count);

  // add coins/bills to till
  void Increase(denomination d, int count);

  // search in till to find the first solution
  bool MakeChangeDFS(double traget, std::vector<denomination>& result,
                     std::vector<denomination> coins, int pos, bool& isFirst,
                     denomination payment);

  // print the result with format  like <1,10$> <2,5$>
  void PrintResult(std::vector<denomination> result);
};

// -------------------------------------------------------
// Function:    CashRegister::CashRegister
// Purpose:     initialize the member variables

CashRegister::CashRegister() : mDisplay(std::cout.rdbuf()) {
  mTill[kPenny] = 10, mTill[kNickel] = 10, mTill[kDime] = 10, mTill[kQuarter] = 10,
  mTill[kHalf] = 10, mTill[kDollar] = 10, mTill[kFive] = 10, mTill[kTen] = 10,
  mTill[kTwenty] = 10, mTill[kFifty] = 10, mTill[kHundred] = 10;
}
// -------------------------------------------------------
// Function:    CashRegister::~CashRegister
// Purpose:     destroy the the member variables

CashRegister::~CashRegister() {}
// -------------------------------------------------------
// Function:    CashRegister::TotalInRegister
// Purpose:     how much money is in the cash register?

double CashRegister::TotalInRegister() const {
  int total(0);
  std::map<denomination, int>::const_iterator it = mTill.begin();
  for (; it != mTill.end(); it++) total += ((int)it->first) * it->second;
  return total / 100.0;
}

// -------------------------------------------------------
// Function:    CashRegister::Dispense
// Purpose:     remove coins/bills from the till and give them to the customer

void CashRegister::Dispense(denomination d, int count) { mTill[d] -= count; }

// -------------------------------------------------------
// Function:    CashRegister::ReportError
// Purpose:     there is a problem!

void CashRegister::ReportError(const char* text) {
  // show the problem on the display
  mDisplay << text;
}

// -------------------------------------------------------

// ******************************
//     <insert your code here>{}
// ******************************

// -------------------------------------------------------
// Function:    CashRegister::PrintResult
// Purpose:     print result with format like <1,10$> <2,5$>

void CashRegister::PrintResult(std::vector<denomination> result) {
  int resultLength = result.size();
  // result is empty, return directly
  if (resultLength == 0) {
    std::cout << "Don't need to return coins/bills " << std::endl << std::endl;
    return;
  }
  std::cout << "return  ";
  // only one coin/bill in result, print it directly
  if (resultLength == 1) {
    std::cout << 1 << "," << result[0] / 100.0 << "$" << std::endl << std::endl;
    return;
  }
  // print result with <count,denomination>
  int count = 1;
  for (int i = 1; i < resultLength; i++) {
    if (result[i] == result[i - 1]) {
      count++;
    } else {
      std::cout << count << "," << result[i - 1] / 100.0 << "$  ";
      count = 1;
    }
    // need to consider the last element
    if (i == resultLength - 1) {
      std::cout << count << "," << result[i] / 100.0 << "$" << std::endl;
    }
  }
  std::cout << std::endl << std::endl;
}

// Function:    CashRegister::Increase
// Purpose:     add coins/bills to the till
void CashRegister::Increase(denomination d, int count) { mTill[d] += count; }

// Function:    CashRegister::MakeChange
// Purpose:     make change according to the paid money and owed money.
void CashRegister::MakeChange(double amountPaid, double amountOwed) {
  double change = amountPaid - amountOwed;
  if (change < 0) {
    ReportError("payment should be larger than profit \n");
    return;
  }

  std::cout << std::fixed << std::setprecision(2);
  std::cout << "payment " << amountPaid / 100.0 << "$" << std::endl;
  std::cout << "profit  " << amountOwed / 100.0 << "$" << std::endl;
  std::cout << "change  " << change / 100.0 << "$" << std::endl;
  // C++ 11 compiler
  std::vector<denomination> coins = {kHundred, kFifty,  kTwenty, kTen,
                                     kFive,    kDollar, kHalf,   kQuarter,
                                     kDime,    kNickel, kPenny};

  std::vector<denomination> v;
  bool isFirst = true;
  double total = TotalInRegister();
  if (change > total * 100) {
    ReportError("Total money is not enough\n");
    return;
  }

  MakeChangeDFS(change, v, coins, 0, isFirst, (denomination)(int)amountPaid);
}

// -------------------------------------------------------
// Function:    CashRegister::MakeChangeDFS
// Purpose:     search the first result

bool CashRegister::MakeChangeDFS(double target,
                                 std::vector<denomination>& result,
                                 std::vector<denomination> coins, int pos,
                                 bool& isFirst, denomination payment) {
  // when getting  the first answer,  don't need to search
  if (isFirst == false) {
    return false;
  }

  // calculate the sum in coins vector after the index "pos"
  double restTotal = 0.0;
  int len = coins.size();
  for (int j = pos; j < len; j++) {
    restTotal += mTill[coins[j]] * coins[j];
  }
  // if tagert is lager than the sum of rest coins, don't need to search, show
  // the error information
  if (target > restTotal) {
    ReportError("money is enough but coins/bills are not enough\n");
    std::cout << "need coin/bill " << coins[pos] / 100.0 << "$" << std::endl;
    isFirst = false;
    return false;
  }

  // find the solution
  if (target == 0.0) {
    Increase(payment, 1);
    PrintResult(result);
    return true;
  }

  for (int i = pos; i < len; i++) {
    if (target >= coins[i] && mTill[coins[i]] >= 1) {
      Dispense(coins[i], 1);
      result.push_back(coins[i]);
      if (!MakeChangeDFS(target - (double)coins[i], result, coins, i, isFirst,
                         payment)) {
        // can not find the solution, restore the till
        Increase(coins[i], 1);
      } else {
        // find the solution, return true
        return true;
      }
      result.pop_back();
    }
  }
  ReportError("money is enough but coins/bills are not enough\n");
  return false;
}

int main() {
  std::vector<double> coins = {100.00, 50.00, 20.00, 10.00, 5.00, 1.00,
                               0.50,   0.25,  0.10,  0.05,  0.01};
  CashRegister* cr = new CashRegister();
  std::string information =
      "Entry one of these number  for payment:"
      "100.00, 50.00, 20.00, 10.00, 5.00,\n"
      "1.00,  0.50, 0.25, 0.10,0.5,0.1\n"
      "Entry any number for profit\n"
      "Entry two negative number like -1 -1 for exiting system";

  std::cout << information << std::endl << std::endl;
  while (true) {
    double paid, owned;
    std::cout << "Entry <payment profit> For example: 100 50" << std::endl;

    if (std::cin >> paid && std::cin >> owned) {
      if (paid < 0 && owned < 0) {
        std::cout << "Exit" << std::endl;
        break;
      }
      /*----customer has to use one coin/bill to pay, if customer wants to  make payment become random, just remove this part code*/
      std::vector<double>::iterator iter =
          find(coins.begin(), coins.end(), paid);
      if (iter == coins.end()) {
        std::cout << information << std::endl << std::endl;
        continue;
      }
      /*---------------------------------*/
      cr->MakeChange(paid * 100, owned * 100);
    } else {
      std::cout << "Invalid Input! Please input a numerical value.\n"
                << std::endl
                << std::endl;
      std::cin.clear();
      while (std::cin.get() != '\n')
        ;
    }
  }
  delete cr;
  cr = NULL;

  return 0;
}
