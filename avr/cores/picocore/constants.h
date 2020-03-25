// global constants
#include <stdint.h>

static const uint8_t LOW = 0;
static const uint8_t HIGH = 1;
static const uint8_t LED_BUILTIN = 2;
static const uint8_t NUM_DIGITAL_PINS = 6;

enum _bitOrder {MSBFIRST = 0, LSBFIRST};

enum _pin_mode {
    INPUT = 0,  OUTPUT, INPUT_PULLUP
};

enum _analog_ref { DEFAULT = 0, INTERNAL };

enum _analog_pin { A0 = 0, A1, A2, A3, BAD_ANALOG_PIN };

