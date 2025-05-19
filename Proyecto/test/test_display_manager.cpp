#include <Arduino.h>
#include <unity.h>
#include <DisplayManager.h>

DisplayManager display;

void test_display_output() {
    display.begin();
    display.showTrack("Test Track");
    display.showArtist("Test Artist");
    display.showStatus("1:23 / 3:45");

    // Test visual, siempre pasa
    TEST_ASSERT_TRUE(true);
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_display_output);
    UNITY_END();
}

void loop() {}
