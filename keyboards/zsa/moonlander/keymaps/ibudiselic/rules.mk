# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
WEBUSB_ENABLE = yes
ORYX_ENABLE = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
# See https://github.com/qmk/qmk_firmware/blob/master/docs/feature_debounce_type.md.
# The debounce time is defined in config.h.
# The default algorithm is sym_defer_g (symmetric defer global - switch to per-key so that a higher
# delay doesn't impact typing much)
DEBOUNCE_TYPE = sym_defer_pk
