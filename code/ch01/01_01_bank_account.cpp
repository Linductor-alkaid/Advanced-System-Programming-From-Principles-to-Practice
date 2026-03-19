#include <iostream>
#include <string>
#include <stdexcept>

class BankAccount {
private:
    double balance_;
    int id_;
    std::string encrypted_password_;

    // 辅助函数：验证金额是否合法
    bool isValidAmount(double amount) const {
        return amount >= 0;
    }
    // 同理：验证id是否合法
    bool isValidId(int id) const{
        return id > 0;
    }

public:
    // 构造函数
    BankAccount(double initialBalance,int id) : balance_(0),id_(-1) {
        if (isValidAmount(initialBalance)) {
            balance_ = initialBalance;
        }
        if (isValidId(id)){
            id_ = id;
        }
    }

    // 接口：获取余额（只读）
    double getBalance() const {
        return balance_;
    }

    // 接口：存款（带校验）
    bool deposit(double amount) {
        if (!isValidAmount(amount)) {
            return false;  // 存款金额不能为负
        }
        balance_ += amount;
        return true;
    }

    // 接口：取款（带校验）
    bool withdraw(double amount) {
        if (!isValidAmount(amount)) {
            return false;  // 取款金额不能为负
        }
        if (amount > balance_) {
            return false;  // 余额不足
        }
        balance_ -= amount;
        return true;
    }

    // 接口：修改密码（带验证）
    bool changePassword(const std::string& oldPwd,
                       const std::string& newPwd) {
        if (!verifyPassword(oldPwd)) {
            return false;  // 旧密码错误
        }
        if (newPwd.length() < 6) {
            return false;  // 新密码太短
        }
        encrypted_password_ = encrypt(newPwd);
        return true;
    }

private:
    //简单的加密实现
    std::string encrypt(const std::string& pwd) const {
        std::string temp=pwd;
        for(size_t i=0;i<pwd.size();i++){
            temp[i]=char(int(temp[i])^id_);
            //基于a^b^b=a实现的简单加密
            //对于部分字符可能会加密出现不可见特殊字符
        }
        return temp;
    }

    bool verifyPassword(const std::string& pwd) const {
        if(encrypt(encrypted_password_) != pwd) return false;
        return true;
    }


};

void goodExample() {
    BankAccount account(1000,32);

    // account.balance_ = -1000;  // 编译错误！balance_是私有的

    account.deposit(500);   // 正确：通过接口操作
    account.withdraw(200);

    if (account.getBalance() > 0) {
        // 余额为正，可以继续操作
    }

    std::cout << "账户余额: " << account.getBalance() << std::endl;

    // 数据的合法性始终得到保证
}

int main() {
    goodExample();
    return 0;
}
