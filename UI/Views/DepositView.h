#ifndef DEPOSIT_VIEW_H
#define DEPOSIT_VIEW_H

#include <memory>

using std::shared_ptr;

class Account;

namespace UI
{
    class DepositView
    {
    private:
        shared_ptr<Account> _account;

    public:
        DepositView(shared_ptr<Account> account);
        void render();
    };
}

#endif
