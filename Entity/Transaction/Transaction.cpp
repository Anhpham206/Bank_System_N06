#include "Transaction.h"

Transaction::Transaction(const std::string& id, long long amount)
    : _transactionID(id), _amount(amount) {
    this->_date = "2025-12-13"; 
}