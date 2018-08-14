/*
#include "L5_Testing/testing_frameworks.hpp"
#include "L3_HAL/buttons.hpp"

TEST_CASE("Testing ButtonDriver", "[button_driver]")
{
    using fakeit::Fake;
    using fakeit::Mock;
    using fakeit::Verify;
    // Simulated local version of LPC_IOCON register to verify register
    // manipulation by side effect of Pin method calls
    LPC_IOCON_TypeDef local_iocon;
    memset(&local_iocon, 0, sizeof(local_iocon));

    // Substitute the memory mapped LPC_IOCON with the local_iocon test struture
    // Redirects manipulation to the 'local_iocon'
    Pin::pin_map =
        reinterpret_cast<Pin::PinMap_t *>(&local_iocon);

    // Onboard button of Port 1 and Pin 9 will be used for this test

    Mock<GpioInterface> mock_gpio;
    Mock<PinInterface> mock_pincon;

    Fake(Method(mock_gpio, SetAsInput), Method(mock_gpio, ReadPin));
    Fake(Method(mock_pincon, SetPinFunction), Method(mock_pincon, SetMode),
         Method(mock_pincon, SetAsActiveLow));

    // testing port one, pin nine
    ButtonDriver btn1_test(1, 9);

    SECTION("Initialize")
    {
        constexpr uint8_t kFunction0 = 0b000;
        constexpr uint8_t kModePosition = 3;
        constexpr uint32_t kMask        = 0b11 << kModePosition;

        constexpr uint32_t kExpectedForInactive =
            static_cast<uint8_t>(PinInterface::Mode::kInactive)
            << kModePosition;

        btn1_test.Initialize();
        CHECK(kFunction0 == (local_iocon.P1_9 & 0b111));
        CHECK(kExpectedForInactive == (local_iocon.P1_9 & kMask));
        Verify(Method(mock_gpio, SetAsInput));
    }
    SECTION("Read Button")
    {
        btn1_test.Read();
        Verify(Method(mock_gpio, ReadPin));
    }
    SECTION("Invert Button Signal")
    {
        constexpr uint8_t kInvertPosition = 6;
        constexpr uint32_t kMask          = 0b1 << kInvertPosition;
       // Source: "UM10562 LPC408x/407x User manual" table 83 page 132
       // Check that mapped pin P1.9's input inversion bit is set to 1
       btn1_test.InvertButtonSignal(true);
       CHECK(kMask == (local_iocon.P1_9 & kMask));
       // Check that mapped pin P1.9's input inversion bit is set to 0
       btn1_test.InvertButtonSignal(false);
       CHECK(0 == (local_iocon.P1_9 & kMask));
    }

    Pin::pin_map =
        reinterpret_cast<Pin::PinMap_t *>(LPC_IOCON);
}
*/
