#include "CustomerParser.h"
#include "../../Entity/Customer/Customer.h"
#include "../../Helper/Utils.h"

#include <vector>
#include <string>
using std::string;
using std::vector;

shared_ptr<Object> CustomerParser::parse(string data)
{
    vector<string> v = Utils::split(data, ", ");
    // Constructor Customer yêu cầu 6 tham số string
    if (v.size() >= 5)
    {
        return make_shared<Customer>(v[0], v[1], v[2], v[3], v[4]);
    }
    return nullptr;
}