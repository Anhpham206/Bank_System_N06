#ifndef TRANSFER_VIEW_H
#define TRANSFER_VIEW_H

#include <memory>

class Account;
class BankSystem;

namespace UI
{
    class TransferView
    {
    private:
        std::shared_ptr<Account> _account;
        std::shared_ptr<BankSystem> _bank;

    public:
        TransferView(std::shared_ptr<Account> account);
        void render();
    };
}
#endif