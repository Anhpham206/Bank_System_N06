#include "BankSystemParser.h"
#include "../../Entity/BankSystem/BankSystem.h"

Object* BankSystemParser::parse(string data) {
    return new BankSystem();
}