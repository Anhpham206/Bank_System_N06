#include "CustomerParser.h"
#include "../../Entity/Customer/Customer.h"
#include "../../Helper/Utils.h"

#include <vector>
#include <string>
using std::vector;
using std::string;

Object* CustomerParser::parse(string data) {
    vector<string> v = Utils::split(data, ", ");
    // Constructor Customer yêu cầu 6 tham số string
    if (v.size() >= 6) {
        return new Customer(v[0], v[1], v[2], v[3], v[4], v[5]);
    }
    return nullptr;
}