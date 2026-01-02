#ifndef CUSTOMER_VIEW_H_
#define CUSTOMER_VIEW_H_

#include "../../Entity/BankSystem/BankSystem.h"
#include "../../Entity/Customer/Customer.h"

#include <vector>
#include <string>
#include <memory>
#include "../../Entity/Account/Account.h"

using std::string;

namespace UI
{

    class CustomerView
    {
    private:
        // [MỚI] Biến để lưu ngữ cảnh làm việc
        std::shared_ptr<BankSystem> _bankSystem;
        std::shared_ptr<Customer> _currentCustomer;

        // Danh sách các lựa chọn trong menu
        std::vector<std::string> _menuOptions;

        // Danh sách lựa chọn trong menu tài khoản (Account Detail)
        std::vector<std::string> _accountMenuOptions;

        // Chỉ số (index) của dòng đang được chọn
        int _selectedIndex;

        // --- Các hàm điều hướng đến trang chức năng (Placeholder) ---
        void showUserInfoPage();    // Thông tin người dùng
        void showAccountListPage(); // Danh sách tài khoản
        void showAddAccountPage();  // Thêm tài khoản
        void handleLogout();        // Đăng xuất
        // // Thêm các hàm xử lý giao dịch mới
        // void handleDeposit();  // Xử lý nạp tiền
        // void handleWithdraw(); // Xử lý rút tiền
        // void handleTransfer(); // Xử lý chuyển khoản

        // Hàm phụ trợ để lấy tài khoản từ input
        // std::shared_ptr<Account> inputOwnedAccount(std::string prompt);

    public:
        CustomerView(); // Constructor để khởi tạo menu
        void render();  // Hàm chính để hiển thị và xử lý vòng lặp
    };

}

#endif
