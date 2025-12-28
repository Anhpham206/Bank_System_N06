#include "SavingAccountParser.h"
#include "../../Entity/Account/SavingAccount.h"
#include "../../Helper/Utils.h"
#include <vector>
#include <string>
using std::string;
using std::vector;

shared_ptr<Object> SavingAccountParser::parse(string data)
{
    vector<string> v = Utils::split(data, ", ");
    if (v.size() >= 2)
    {
        string accNum = v[0];
        double rate = stod(v[1]);
        // Constructor: SavingAccount(accNum, Customer* owner, rate)
        // LƯU Ý: Truyền nullptr cho owner, cần xử lý link owner sau khi load xong data
        return make_shared<SavingAccount>(accNum, nullptr, rate);
    }
}