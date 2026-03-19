#include <iostream>
#include <cstring>

class AccessDemo {
public:
    int publicData;
private:
    int privateData;
protected:
    int protectedData;
public:
    AccessDemo() : publicData(1), privateData(2), protectedData(3) {}

    void print() {
        std::cout << "publicData=" << publicData
                  << ", privateData=" << privateData
                  << ", protectedData=" << protectedData << std::endl;
    }
};

int main() {
    AccessDemo obj;

    // 正常访问（通过public方法）
    obj.print();  // 输出: publicData=1, privateData=2, protectedData=3

    // 直接读取整个对象的内存
    int raw[3];
    std::memcpy(raw, &obj, sizeof(obj));

    std::cout << "\nRaw memory dump:\n";
    std::cout << "Offset 0: " << raw[0] << " (publicData)\n";
    std::cout << "Offset 4: " << raw[1] << " (privateData)\n";
    std::cout << "Offset 8: " << raw[2] << " (protectedData)\n";

    return 0;
}
