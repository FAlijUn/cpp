#include <string>
#include <iostream>
// 一个类型安全的联合体
#include <variant>

struct DoorState {
    struct DoorOpened {};
    struct DoorClosed {};
    struct DoorLocked {};
    using State = std::variant<DoorOpened, DoorClosed, DoorLocked>;
    void open() {
        m_state = std::visit(OpenEvent{}, m_state);
    }
    void close() {
        m_state = std::visit(CloseEvent{}, m_state);
    }
    void lock() {
        m_state = std::visit(LockEvent{}, m_state);
    }
    void unlock() {
        m_state = std::visit(UnlockEvent{}, m_state);
    }

    State m_state; 
};

struct OpenEvent {
    State operator ()(const DoorOpened&){ return DoorOpened(); }
    State operator ()(const DoorClosed&){ return DoorOpened(); }
    // 不能打开已锁定的门
    State operator ()(const DoorLocked&){ return DoorLocked(); }
};

struct CloseEvent {
    State operator ()(const DoorOpened&){ return DoorClosed(); }
    State operator ()(const DoorClosed&){ return DoorClosed(); }
    State operator ()(const DoorLocked&){ return DoorLocked(); }
};

struct LockEvent {
    // 不能锁定已打开的门
    State operator ()(const DoorOpened&){ return DoorOpened(); }
    State operator ()(const DoorClosed&){ return DoorLocked(); }
    State operator ()(const DoorLocked&){ return DoorLocked(); }
};

struct UnlockEvent {
    // 不能解锁已打开的门
    State operator ()(const DoorOpened&){ return DoorOpened(); }
    State operator ()(const DoorClosed&){ return DoorClosed(); }
    // 解锁
    State operator ()(const DoorLocked&){ return DoorClosed(); }
};

int main() {
    DoorState door;
    door.m_state = DoorState::DoorClosed{};
    door.open();
    door.lock();
    door.close();
    door.lock();
    door.unlock();
}
