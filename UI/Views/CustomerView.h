#ifndef CUSTOMER_VIEW_H_
#define CUSTOMER_VIEW_H_

#include "../../Entity/BankSystem/BankSystem.h"
#include "../../Entity/Customer/Customer.h"

#include <vector>
#include <memory>

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

        // --- Các hàm chức năng chi tiết cho từng tài khoản ---
        // Khi chọn 1 tài khoản từ danh sách, sẽ vào màn hình này
        void showAccountDetailPage(std::string accountNumber);

        void showDepositPage(std::string accountNumber);  // Nạp tiền
        void showWithdrawPage(std::string accountNumber); // Rút tiền
        
        // Hàm hỗ trợ hiển thị và chọn menu (tái sử dụng logic W/S)
        int navigateMenu(const std::vector<std::string>& options, std::string title);

    public:
        CustomerView(std::shared_ptr<BankSystem> system, std::shared_ptr<Customer> customer); // Constructor để khởi tạo menu
        void render();  // Hàm chính để hiển thị và xử lý vòng lặp
    };

}

#endif
