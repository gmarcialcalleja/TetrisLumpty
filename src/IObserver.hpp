#pragma once
class IObserver {
private:
public:
    virtual void onNotify(int numLines) = 0;
    virtual ~IObserver() = default; //virtual destructor
};