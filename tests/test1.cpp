#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include <Transaction.h>
#include <Account.h>


class MockAccount: public Account{
public:
    MockAccount(int id, int balance):Account(id, balance){}
    MOCK_METHOD(void, Unlock, ());
};
TEST(Account, Init){
    MockAccount test(1,100);
    EXPECT_EQ(test.GetBalance(),100);
    EXPECT_EQ(test.id(),1);
}

class MockTransaction: public Transaction{
public:
    MOCK_METHOD1(void, set_fee, (int fee), (override));
    MOCK_METHOD2(void Credit, (Account& accout, int sum), (override));
    MOCK_METHOD3(bool Debit, (Account& accout, int sum), (override));
    MOCK_METHOD4(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};

TEST(Account, GetBalance){
MockAccount acc(1,100);
EXPECT_EQ(acc.Account::GetBalance(), 100);
}

TEST(Account, ChangeBalance){
MockAccount acc(0, 100);
EXPECT_THROW(acc.Account::ChangeBalance(50), std::runtime_error);
acc.Account::Lock();
acc.Account::ChangeBalance(50);
EXPECT_EQ(acc.Account::GetBalance(), 150);

}

TEST(Account, Lock) {
    MockAccount acc(15,213);
    acc.Lock();
    EXPECT_THROW(acc.Lock(), std::runtime_error);
}

TEST(Account, Unlock){
    MockAccount acc(0, 100);
EXPECT_CALL(acc, Unlock()).Times(1);
acc.Unlock();
}

TEST(Transaction, Make){
MockAccount from_acc(15,17650);
MockAccount to_acc(13, 18435);
MockTransaction tr;
EXPECT_THROW(tr.Make(from_acc,from_acc,0),std::logic_error);
EXPECT_THROW(tr.Make(from_acc,to_acc,0),std::logic_error);
EXPECT_THROW(tr.Make(from_acc,to_acc,-5),std::invalid_argument);
}


TEST(Transaction, set_fee){
MockTransaction tr;
tr.set_fee(5);
EXPECT_EQ(tr.fee(),5);
}

TEST(Transaction, Credit) {
MockAccount acc(15,100);
MockTransaction tr;
tr.Credit(acc,200);
EXPECT_EQ(acc.GetBalance(),200);
}

TEST(Transaction, Debit) {
MockAccount acc(15,100);
MockTransaction tr;
tr.Debit(acc,200);
EXPECT_EQ(acc.GetBalance(),300);

}




TEST(Transaction, SaveToDataBase){
MockAccount from_acc(15,17650);
MockAccount to_acc(13, 18435);
MockTransaction tr;


}
