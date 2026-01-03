#include "TransferTransactionParser.h"
#include "../../Entity/Transaction/TransferTransaction.h"
#include "../../Helper/Utils.h"

#include "../AppContext.h"

#include <vector>
#include <string>
using std::string;
using std::vector;

shared_ptr<Object> TransferTransactionParser::parse(string data)
{
    vector<string> v = Utils::split(data, ", ");
    // Ít nhất cần srcAcc, destAcc, Amount
    if (v.size() >= 3)
    {
        string srcAccNum = v[0];
        string destAccNum = v[1];
        long long amount = stoll(v[2]);
        auto bank = AppContext::getInstance().getBankSystem();
        shared_ptr<Object> object = make_shared<TransferTransaction>(bank->getAccount(srcAccNum), bank->getAccount(destAccNum), amount);
        return object;
    }
    return nullptr;
}