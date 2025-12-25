#include "../Business/IParsable.h"
#include "../Helper/Utils.h"
#include "../Entity/BankSystem/BankSystem.h"

class BankSystemParser : public IParsable {
public:
    Object* parse(string data) override {
        // BankSystem trong code của bạn không có constructor nhận tham số string
        // Nên chỉ trả về một đối tượng mặc định
        return new BankSystem();
    }
};