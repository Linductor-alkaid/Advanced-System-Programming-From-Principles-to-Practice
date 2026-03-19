#include <iostream>
#include <functional>
#include <vector>
#include <string>

// 被观察者基类（CRTP）
template <typename Derived, typename Event>
class Observable {
    std::vector<std::function<void(const Event&)>> observers_;
public:
    void subscribe(std::function<void(const Event&)> observer) {
        observers_.push_back(observer);
    }

    template <typename... Args>
    void notify(Args&&... args) {
        Event event(std::forward<Args>(args)...);
        for (auto& observer : observers_) {
            observer(event);
        }
    }
};

// 事件类型
struct ButtonEvent {
    enum Type { Click, Hover, Leave };
    Type type;
    int x, y;
};

// 具体被观察者
class Button : public Observable<Button, ButtonEvent> {
    std::string label_;
public:
    Button(const std::string& label) : label_(label) {}

    void simulateClick(int x, int y) {
        notify(ButtonEvent{ButtonEvent::Click, x, y});
    }

    std::string getLabel() const { return label_; }
};

int main() {
    Button button("Submit");

    // 订阅事件
    button.subscribe([](const ButtonEvent& e) {
        if (e.type == ButtonEvent::Click) {
            std::cout << "Button clicked at (" << e.x << ", " << e.y << ")\n";
        }
    });

    button.simulateClick(100, 200);

    return 0;
}
