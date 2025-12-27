#include "TransactionParser.h"
#include "../../Entity/Transaction/DepositTransaction.h"
#include "../../Entity/Transaction/WithdrawTransaction.h"
#include "../../Entity/Transaction/TransferTransaction.h"
#include "../../Helper/Utils.h"

#include <vector>
#include <string>
using std::vector;
using std::string;

Object* TransactionParser::parse(string data) {
    vector<string> v = Utils::split(data, ", ");
    // Ít nhất cần Type, ID, Amount
    if (v.size() >= 3) {
        string type = v[0];
        string id = v[1];
        long long amount = stoll(v[2]);

        if (type == "DEP") return new DepositTransaction(id,nullptr, amount);
        if (type == "WITH") return new WithdrawTransaction(id, nullptr, amount);
        if (type == "TRANS") return new TransferTransaction(id, nullptr, nullptr, amount); 
    }
    return nullptr;
}