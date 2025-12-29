#include "CheckingAccountParser.h"
#include "../../Entity/Account/CheckingAccount.h"
#include "../../Helper/Utils.h"

#include <vector>
#include <string>
using std::string;
using std::vector;

shared_ptr<Object> CheckingAccountParser::parse(string data)
{
    vector<string> v = Utils::split(data, ", ");
    if (v.size() >= 1)
    {
        string accNum = v[0];
        return make_shared<CheckingAccount>(accNum, v[1], stoll(v[2]), v[3]);
    }
    return nullptr;
}