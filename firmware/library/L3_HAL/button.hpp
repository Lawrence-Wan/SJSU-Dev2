#pragma once

#include <cstdint>

#include "L1_Drivers/gpio.hpp"

class ButtonInterface
{
 public:
    virtual void Initialize()                                         = 0;
    virtual bool Read()                                               = 0;
    virtual bool Released(bool reset_state = false)                   = 0;
    virtual bool Pressed()                                            = 0;
    virtual void InvertButtonSignal(bool enable_invert_signal = true) = 0;
};

class Button : public ButtonInterface, public Gpio
{
 public:
    // Port 5, Port 4 (used for unit-testing)
    static constexpr uint8_t kPortFive = 5;
    static constexpr uint8_t kPinFour  = 4;

    constexpr Button(uint8_t port_num, uint8_t pin_num)
        : Gpio(port_num, pin_num)
    {
    }

    // Unit test constructor
    constexpr Button() : Gpio(kPortFive, kPortFour) {}

    void Initialize() override
    {
        SetMode(PinInterface::Mode::kPullDown);
        SetAsInput();
    }

    bool Read() override
    {
        return (ReadPin()) ? true : false;
    }

    bool Released(bool reset_state = false) override
    {
        bool result = false;
        if (reset_state)
        {
            was_pressed = false;
        }
        if (ReadPin() && !was_pressed)
        {
            was_pressed = true;
        }
        else if (!ReadPin() && was_pressed)
        {
            result      = true;
            was_pressed = false;
        }
        return result;
    }

    bool Pressed(bool reset_state = false) override
    {
        bool result = false;
        if (reset_state)
        {
            was_pressed = false;
        }
        if (ReadPin() && !was_pressed)
        {
            result      = true;
            was_pressed = true;
        }
        else if (!ReadPin() && was_pressed)
        {
            was_pressed = false;
        }
        return result;
    }

    void InvertButtonSignal(bool enable_invert_signal = true) override
    {
        SetAsActiveLow(enable_invert_signal);
    }

    ~ButtonDriver() {}

 private:
    static bool was_pressed = false;
};
