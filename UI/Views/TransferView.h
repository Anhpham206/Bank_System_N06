#ifndef TRANSFER_VIEW_H
#define TRANSFER_VIEW_H

#include "../../Entity/Customer/Customer.h"
#include "../../Entity/BankSystem/BankSystem.h"
#include <memory>

namespace UI {
    class TransferView {
    private:
        std::shared_ptr<Customer> _user;
        std::shared_ptr<BankSystem> _bank;
    public:
        TransferView(std::shared_ptr<BankSystem> bank, std::shared_ptr<Customer> user);
        void render();
    };
}
#endif