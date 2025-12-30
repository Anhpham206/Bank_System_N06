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
        return make_shared<SavingAccount>(accNum, v[1], stoll(v[2]), v[3], stod(v[4]));
    }
    return nullptr; // Thêm return nullptr; để tránh cảnh báo (warning) biến thành lỗi.
}