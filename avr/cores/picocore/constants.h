// global constants
#include <stdint.h>

enum {LOW = 0, HIGH};
enum {LED_BUILTIN = 2};
enum {NUM_DIGITAL_PINS = 6};

typedef enum {MSBFIRST = 0, LSBFIRST} _bitOrder;

typedef enum {
    INPUT = 0,  OUTPUT, INPUT_PULLUP
} _pin_mode;

typedef enum { DEFAULT = 0, INTERNAL } _analog_ref;

typedef enum { A0 = 0, A1, A2, A3, BAD_ANALOG_PIN } _analog_pin;

