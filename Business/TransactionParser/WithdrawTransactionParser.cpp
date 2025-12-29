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
    // Ít nhất cần srcAcc, Amount, PIN
    if (v.size() >= 3)
    {
        string srcAccNum = v[0];
        long long amount = stoll(v[1]);
        string PIN = v[2];
        auto bank = AppContext::getInstance().getBankSystem();
        shared_ptr<Object> object = make_shared<WithdrawTransaction>(bank->getAccount(srcAccNum), amount, PIN);
        return object;
    }
    return nullptr;
}