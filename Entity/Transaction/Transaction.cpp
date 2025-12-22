#include "Transaction.h"
#include <ctime>

Transaction::Transaction(const std::string& id, long long amount)
    : _transactionID(id), _amount(amount) {
    
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    
    // Định dạng ngày: YYYY-MM-DD
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    this->_date = std::string(buf); 
}