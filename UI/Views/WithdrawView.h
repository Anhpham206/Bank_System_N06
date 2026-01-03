#ifndef WITHDRAW_VIEW_H
#define WITHDRAW_VIEW_H

#include <memory>

using std::shared_ptr;

class Account;

namespace UI
{
    class WithdrawView
    {
    private:
        shared_ptr<Account> _account;

    public:
        WithdrawView(shared_ptr<Account> account);
        void render();
    };
}

#endif
