#include <Arduino.h>
#include <Logger.h>
#include "Cube.h"
#include "Animator.h"
#include "Animations.h"
#include "display.h"
#include "ota.h"

Animation *animations[] = {
    new Shell(),
    new Sphere(),
    new Spiral(),
    new Gradient(),
    new Rainbow(),
    new Ripple(),

    // new Sinelon(),
    // new Sparkles(),
    // new Linear(),
    // new Solid(),
    // new Confetti(),
    // new BPM(),
};

Animator animator(animations, ARRAY_SIZE(animations));

void setup()
{
    SERIAL_BEGIN(115200);  // Logging
    DISPLAY_BEGIN(115200); // Display communication

    // Initialize 9 branches of 81 LEDs each, total of 729 LEDs
    FastLED.addLeds<LED_TYPE, PIN_LED_0, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 0, LED_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_1, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 1, LED_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_2, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 2, LED_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_3, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 3, LED_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_4, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 4, LED_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_5, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 5, LED_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_6, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 6, LED_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_7, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 7, LED_BRANCH_COUNT);
    FastLED.addLeds<LED_TYPE, PIN_LED_8, LED_COLOR_ORDER>(Cube.leds, LED_BRANCH_COUNT * 8, LED_BRANCH_COUNT);
    FastLED.clear(true); // Clear all LEDs

    initOta(); // Over the Air Update
}

void loop()
{
    handleOta();
    handleDisplay();
    animator.run();
}
