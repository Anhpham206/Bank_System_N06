#ifndef CUSTOMER_VIEW_H_
#define CUSTOMER_VIEW_H_

// #include "../../Entity/BankSystem/BankSystem.h"

#include <vector>
#include <memory>

using std::string;

namespace UI
{

    class CustomerView
    {
    private:
        // Danh sách các lựa chọn trong menu
        std::vector<std::string> _menuOptions;

        // Chỉ số (index) của dòng đang được chọn
        int _selectedIndex;

        // --- Các hàm điều hướng đến trang chức năng (Placeholder) ---
        void showUserInfoPage();    // Thông tin người dùng
        void showAccountListPage(); // Danh sách tài khoản
        void showAddAccountPage();  // Thêm tài khoản
        void handleLogout();        // Đăng xuất

    public:
        CustomerView(); // Constructor để khởi tạo menu
        void render();  // Hàm chính để hiển thị và xử lý vòng lặp
    };

}

#endif