/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR
#define PERMISSIVE_HOLD

#undef RGB_DISABLE_TIMEOUT
#define RGB_DISABLE_TIMEOUT 60000

#define USB_SUSPEND_WAKEUP_DELAY 0
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 4

#define CAPS_LOCK_STATUS
#define FIRMWARE_VERSION u8"bdz0V/NwmMX"
#define RGB_MATRIX_STARTUP_SPD 60

#define TAPPING_TERM 144
#define TAPPING_TERM_PER_KEY

#undef PERMISSIVE_HOLD
#define PERMISSIVE_HOLD_PER_KEY

#define COMBO_TERM 15

// Default is 5 (unit is ms). See https://github.com/qmk/qmk_firmware/blob/master/docs/feature_debounce_type.md.
// The algorithm is defined in rules.mk.
#define DEBOUNCE 10
