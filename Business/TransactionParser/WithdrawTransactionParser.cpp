#include "WithdrawTransactionParser.h"
#include "../../Entity/Transaction/WithdrawTransaction.h"
#include "../../Helper/Utils.h"

#include "../AppContext.h"

#include <vector>
#include <string>
using std::string;
using std::vector;

shared_ptr<Object> WithdrawTransactionParser::parse(string data)
{
    vector<string> v = Utils::split(data, ", ");
    // Ít nhất cần srcAcc, Amount
    if (v.size() >= 2)
    {
        string srcAccNum = v[0];
        long long amount = stoll(v[1]);
        auto bank = AppContext::getInstance().getBankSystem();
        shared_ptr<Object> object = make_shared<WithdrawTransaction>(bank->getAccount(srcAccNum), amount);
        return object;
    }
    return nullptr;
}