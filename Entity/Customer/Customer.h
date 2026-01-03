#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include "../Object.h"
#include <string>
#include <vector>
#include <memory> // [THÊM] Để dùng shared_ptr

class Account;

class Customer : public Object
{
private:
    std::string _customerId;
    std::string _fullName;
    std::string _username;
    std::string _password;
    std::string _phoneNumber;
    // std::vector<Account *> _ownedAccount;

    std::vector<string> _ownedAccount;
    // dung vector string chua accountNumber, lay ra Account thong qua ham getAccount tu BankSystem hien tai

public:
    Customer(); // Hàm tạo không tham số
    Customer(std::string id, std::string name, std::string user, std::string pass, std::string phone);
    std::string getCustomerId();
    std::string getName();
    bool verifyPassword(std::string pass);

    // Getters used for persistence
    std::string password() const;
    std::string phoneNumber() const;

    void addAccount(std::shared_ptr<Account> acct); // them Account vao co so du lieu cua BankSystem nua
    void removeAccount(std::string acctNum);
    std::shared_ptr<Account> getAccount(std::string acctNum);
    void addAccountNumber(string accountNumber);
    std::string info() override;

    std::vector<std::string> getOwnedAccountIds();

    std::string username();

    std::vector<std::string> getOwnedAccountIds() const;
};

#endif
