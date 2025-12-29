#include "DepositTransactionParser.h"
#include "../../Entity/Transaction/DepositTransaction.h"
#include "../../Helper/Utils.h"

#include "../AppContext.h"

#include <vector>
#include <string>
using std::string;
using std::vector;

shared_ptr<Object> DepositTransactionParser::parse(string data)
{
    vector<string> v = Utils::split(data, ", ");
    // Ít nhất cần srcAcc, Amount
    if (v.size() >= 2)
    {
        string srcAccNum = v[0];
        long long amount = stoll(v[1]);
        auto bank = AppContext::getInstance().getBankSystem();
        shared_ptr<Object> object = make_shared<DepositTransaction>(bank->getAccount(srcAccNum), amount);
        return object;
    }
    return nullptr;
}