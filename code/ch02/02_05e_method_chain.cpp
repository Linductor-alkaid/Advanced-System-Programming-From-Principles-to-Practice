#include <iostream>
#include <string>

template <typename Derived>
class Builder {
public:
    Derived& setName(const std::string& name) {
        name_ = name;
        return static_cast<Derived&>(*this);
    }

    Derived& setValue(int value) {
        value_ = value;
        return static_cast<Derived&>(*this);
    }

protected:
    std::string name_;
    int value_ = 0;
};

class MyObjectBuilder : public Builder<MyObjectBuilder> {
    bool flag_ = false;
public:
    MyObjectBuilder& setFlag(bool flag) {
        flag_ = flag;
        return *this;
    }

    void build() {
        std::cout << "Building: name=" << name_
                  << ", value=" << value_
                  << ", flag=" << flag_ << "\n";
    }
};

int main() {
    MyObjectBuilder builder;
    builder.setName("test")
           .setValue(42)
           .setFlag(true)
           .build();

    return 0;
}
