#pragma once

class Account;

class Transaction {
 public:
  Transaction();
  virtual ~Transaction();

  bool Make(Account& from, Account& to, int sum);
  virtual int fee() const { return fee_; }
  virtual void set_fee(int fee) { fee_ = fee; }

 private:
  virtual void Credit(Account& accout, int sum);
  virtual bool Debit(Account& accout, int sum);

  // Virtual to test.
  virtual void SaveToDataBase(Account& from, Account& to, int sum);

  int fee_;
};
