#pragma once
#include "IObserver.hpp"
#include <memory>
class Subject {
public:
    virtual void notify(int numLines) = 0;
    virtual ~Subject() = default;
    virtual void attach_observer(IObserver* observer) = 0;
    virtual void detach_observer(IObserver* observer) = 0;
};