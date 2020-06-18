// global constants
#include <stdint.h>

static const uint8_t LOW = 0;
static const uint8_t HIGH = 1;
//static const uint8_t LED_BUILTIN = 2;
enum {LED_BUILTIN = 2};
//static const uint8_t NUM_DIGITAL_PINS = 6;
enum {NUM_DIGITAL_PINS = 6};

typedef enum {MSBFIRST = 0, LSBFIRST} _bitOrder;

typedef enum {
    INPUT = 0,  OUTPUT, INPUT_PULLUP
} _pin_mode;

typedef enum { DEFAULT = 0, INTERNAL } _analog_ref;

typedef enum { A0 = 0, A1, A2, A3, BAD_ANALOG_PIN } _analog_pin;

