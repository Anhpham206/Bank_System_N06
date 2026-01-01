# lệnh biên dịch tất cả các file và tự động tìm hàm main

 g++ -std=c++23 -g (Get-ChildItem -Path . -Recurse -Filter *.cpp).FullName -o test.exe

để chạy hiện thị trên màn hình console thì dùng: 
start test.exe
