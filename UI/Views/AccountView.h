#ifndef ACCOUNT_VIEW_H_
#define ACCOUNT_VIEW_H_

#include <vector>
#include <memory>
#include <string>

using std::shared_ptr;
using std::string;

class Account;

namespace UI
{

    class AccountView
    {
    private:
        // Danh sách các lựa chọn trong menu
        std::vector<std::string> _menuOptions;

        // Chỉ số (index) của dòng đang được chọn
        int _selectedIndex;

        // Lưu số tài khoản để hiển thị trên tiêu đề
        shared_ptr<Account> _account;

        // --- Các hàm điều hướng đến trang chức năng ---
        void showAccountInfoPage();   // Thông tin tài khoản
        void showNotificationsPage(); // Thông báo
        void showDepositPage();       // Nạp tiền
        void showWithdrawPage();      // Rút tiền
        void showTransferPage();      // Chuyển tiền
        void handleDeleteAccount();   // Xóa tài khoản

    public:
        // Constructor nhận vào số tài khoản
        AccountView(shared_ptr<Account> account);
        void render(); // Hàm chính để hiển thị và xử lý vòng lặp
    };

}

#endif