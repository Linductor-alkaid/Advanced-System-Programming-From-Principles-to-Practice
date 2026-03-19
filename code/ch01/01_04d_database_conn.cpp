#include <iostream>
#include <stdexcept>
#include <string>

// 模拟数据库连接
class DatabaseConnection {
    std::string connection_string;
    bool connected = false;
    bool in_transaction = false;

public:
    explicit DatabaseConnection(const std::string& conn_str)
        : connection_string(conn_str) {
        // 模拟连接数据库
        connected = true;
        std::cout << "已连接到数据库: " << conn_str << std::endl;
    }

    ~DatabaseConnection() {
        if (connected) {
            // 析构时如果有未提交的事务，自动回滚
            if (in_transaction) {
                std::cout << "事务未提交，自动回滚" << std::endl;
            }
            std::cout << "数据库连接已关闭" << std::endl;
        }
    }

    void begin_transaction() {
        if (!in_transaction) {
            std::cout << "开始事务" << std::endl;
            in_transaction = true;
        }
    }

    void commit() {
        if (in_transaction) {
            std::cout << "提交事务" << std::endl;
            in_transaction = false;
        }
    }

    void execute(const std::string& sql) {
        if (!connected) throw std::logic_error("未连接数据库");
        std::cout << "执行: " << sql << std::endl;
    }
};

// 使用示例
void transfer_money(DatabaseConnection& db) {
    db.begin_transaction();

    try {
        db.execute("UPDATE accounts SET balance = balance - 100 WHERE id = 1");
        db.execute("UPDATE accounts SET balance = balance + 100 WHERE id = 2");

        // 模拟：中途发生错误
        if (true) {
            throw std::runtime_error("银行系统故障");
        }

        db.commit();  // 只有正常执行到这里才提交
    }
    catch (...) {
        std::cout << "操作失败，事务将自动回滚" << std::endl;
        throw;  // 重新抛出，db 的析构函数会处理回滚
    }
}

int main() {
    DatabaseConnection db("localhost:5432/mydb");

    try {
        transfer_money(db);
    } catch (const std::exception& e) {
        std::cout << "捕获异常: " << e.what() << std::endl;
    }

    return 0;
}
