#include "CheckingAccountParser.h"
#include "../../Entity/Account/CheckingAccount.h"
#include "../../Helper/Utils.h"

#include <vector>
#include <string>
using std::vector;
using std::string;

Object* CheckingAccountParser::parse(string data) {
    vector<string> v = Utils::split(data, ", ");
    if (v.size() >= 1) {
        string accNum = v[0];
        // Constructor: CheckingAccount(accNum, Customer* owner)
        return new CheckingAccount(accNum, nullptr);
    }
    return nullptr;
}