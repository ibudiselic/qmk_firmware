#include QMK_KEYBOARD_H
#include "version.h"

#define MOON_LED_LEVEL LED_LEVEL

enum custom_keycodes {
    RGB_SLD = SAFE_RANGE,
    ST_MACRO_0,
};

enum ibud_layers {
    IBUD_LAY_BASE,
    IBUD_LAY_GAME,
    // SF6 has some fixed keyboard bindings that interfere with user bindings, so it needs
    // a special layer to get sane behavior...
    // This layer is only meant to be activated on top of the game layer, and is mostly transparent
    // with the exception of a few changes:
    // - B and M are swapped (this is necessary because SF6 has some hard-coded bindings for the B
    //   key in the combo training, which interfere with using B as the jump key)
    // - The K key doesn't have the RSFT_T mod-tap, but is just a plain K so it can be used in the
    //   game.
    // - The semicolon key is mapped to F12 so it can be bound in the game (for some reason, the
    //   semicolon can't be bound).
    IBUD_LAY_GAME_SF6,
    IBUD_LAY_NUM,
    IBUD_LAY_FKEYS,
    IBUD_LAY_CTRL,
    IBUD_LAY_SYM,
    IBUD_LAYER_TOTAL_COUNT,
};

#define IBLT(l, kc) LT(IBUD_LAY_##l, kc)
// Shifted symbol layer.
#define IB_SHIFT_SYM LM(IBUD_LAY_SYM, MOD_LSFT)

enum tap_dance_codes {
    DANCE_0,
    DANCE_1,
    DANCE_2,
    DANCE_3,
};

// clang-format off
// This whole underscore thing is a bit cringy, but I really want to reduce the noise to a minimum.
#ifdef _
#error underscore is already defined
#endif
#define _ KC_NO

#define IB_KC_TP KC_TRANSPARENT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [IBUD_LAY_BASE] = LAYOUT_moonlander(
       KC_AT,                 KC_1,                  KC_2,                  KC_3,                  KC_4,                  KC_5,                  KC_F4,                       KC_F5,                 KC_6,                  KC_7,                  KC_8,                  KC_9,                  KC_0,                  _,
       KC_TAB,                KC_Q,                  KC_W,                  KC_E,                  KC_R,                  KC_T,                  KC_HOME,                     KC_PGUP,               KC_Y,                  KC_U,                  KC_I,                  KC_O,                  KC_P,                  KC_BACKSLASH,
       KC_ESCAPE,             IBLT(CTRL, KC_A),      IBLT(FKEYS, KC_S),     LSFT_T(KC_D),          IBLT(NUM, KC_F),       KC_G,                  KC_END,                      KC_PAGE_DOWN,          KC_H,                  KC_J,                  RSFT_T(KC_K),          KC_L,                  KC_SEMICOLON,          RGUI_T(KC_QUOTE),
       KC_GRAVE,              KC_Z,                  KC_X,                  KC_C,                  KC_V,                  KC_B,                                                                      KC_N,                  KC_M,                  KC_COMMA,              KC_DOT,                KC_SLASH,              _,
       _,                     _,                     _,                     LSFT(KC_LALT),         LALT_T(KC_TAB),        TD(DANCE_0),                                                               TD(DANCE_2),           IB_SHIFT_SYM,          TD(DANCE_1),           _,                     _,                     _,
                                                                            LCTL_T(KC_SPACE),      C_S_T(KC_BACKSPACE),   LCA_T(KC_ENTER),                                                           KC_DELETE,             KC_BACKSPACE,          IBLT(SYM, KC_ENTER)
    ),

    [IBUD_LAY_GAME] = LAYOUT_moonlander(
       KC_F6,                 KC_1,                  KC_2,                  KC_3,                  KC_4,                  KC_5,                  KC_F4,                       KC_F5,                 KC_6,                  KC_7,                  KC_8,                  KC_9,                  KC_0,                  _,
       KC_TAB,                KC_Q,                  KC_W,                  KC_E,                  KC_R,                  KC_T,                  KC_HOME,                     KC_PGUP,               KC_Y,                  KC_U,                  KC_I,                  KC_O,                  KC_P,                  KC_BACKSLASH,
       KC_ESCAPE,             KC_A,                  KC_S,                  KC_D,                  KC_F,                  KC_G,                  KC_END,                      KC_PAGE_DOWN,          KC_H,                  KC_J,                  RSFT_T(KC_K),                  KC_L,                  KC_SEMICOLON,                RGUI_T(KC_QUOTE),
       KC_LEFT_SHIFT,         KC_Z,                  KC_X,                  KC_C,                  KC_V,                  KC_B,                                                                      KC_N,                  KC_M,                  KC_COMMA,              KC_DOT,                KC_SLASH,              KC_RIGHT_SHIFT,
       KC_F7,                 KC_F3,                 KC_F2,                 LCTL(KC_LALT),         KC_LALT,               KC_F8,                                                                     TD(DANCE_3),           _,                     TG(IBUD_LAY_GAME_SF6), _,                     _,                     KC_RIGHT_CTRL,
                                                                            KC_SPACE,              KC_F2,                 KC_F1,                                                                     KC_DELETE,             KC_BACKSPACE,          KC_ENTER
    ),

    [IBUD_LAY_GAME_SF6] = LAYOUT_moonlander(
       IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,                    IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,
       IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,                    IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,
       IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,                    IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              KC_K,              IB_KC_TP,              KC_F12,              IB_KC_TP,
       IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              KC_M,                                                                      IB_KC_TP,              KC_B,                  IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,
       IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,                                                                  IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,
                                                                            IB_KC_TP,              IB_KC_TP,              IB_KC_TP,                                                                  IB_KC_TP,              IB_KC_TP,              IB_KC_TP
    ),

    [IBUD_LAY_NUM] = LAYOUT_moonlander(
       IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,                    IB_KC_TP,              KC_NUM,                IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,
       IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,                    KC_ASTR,               KC_PLUS,               KC_7,                  KC_8,                  KC_9,                  KC_0,                  IB_KC_TP,
       IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,                    KC_SLASH,              KC_MINUS,              KC_4,                  KC_5,                  KC_6,                  KC_DOT,                IB_KC_TP,
       IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,                                                                  KC_EQUAL,              KC_1,                  KC_2,                  KC_3,                  IB_KC_TP,              IB_KC_TP,
       IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              IB_KC_TP,              TO(IBUD_LAY_BASE),                                                         IB_KC_TP,              KC_0,                  KC_DOT,                ST_MACRO_0,            IB_KC_TP,              IB_KC_TP,
                                                                            IB_KC_TP,              IB_KC_TP,              IB_KC_TP,                                                                  IB_KC_TP,              IB_KC_TP,              IB_KC_TP
    ),

    [IBUD_LAY_FKEYS] = LAYOUT_moonlander(
       _,                     _,                     _,                     _,                     _,                     _,                     _,                           _,                     _,                     _,                     _,                     _,                     _,                     _,
       _,                     _,                     _,                     _,                     _,                     _,                     _,                           _,                     KC_F11,                KC_F7,                 KC_F8,                 KC_F9,                 KC_F10,                _,
       _,                     _,                     _,                     _,                     _,                     _,                     _,                           _,                     KC_F12,                KC_F4,                 KC_F5,                 KC_F6,                 _,                     _,
       _,                     _,                     _,                     _,                     _,                     _,                                                                         _,                     KC_F1,                 KC_F2,                 KC_F3,                 _,                     _,
       _,                     _,                     _,                     _,                     _,                     _,                                                                         _,                     KC_F10,                _,                     _,                     _,                     _,
                                                                            _,                     _,                     _,                                                                         _,                     _,                     _
    ),

    [IBUD_LAY_CTRL] = LAYOUT_moonlander(
       _,                     _,                     _,                     _,                     _,                     _,                     _,                           KC_PRINT_SCREEN,       _,                     _,                     _,                     _,                     _,                     QK_BOOTLOADER,
       _,                     _,                     _,                     KC_MS_UP,              _,                     _,                     _,                           _,                     _,                     KC_MS_WH_DOWN,         KC_MS_WH_UP,           _,                     _,                     _,
       _,                     _,                     KC_MS_LEFT,            KC_MS_DOWN,            KC_MS_RIGHT,           _,                     _,                           _,                     KC_LEFT,               KC_DOWN,               KC_UP,                 KC_RIGHT,              _,                     _,
       _,                     _,                     _,                     _,                     KC_CAPS_LOCK,          _,                                                                         _,                     _,                     _,                     _,                     _,                     _,
       _,                     _,                     _,                     _,                     _,                     _,                                                                         _,                     _,                     TO(IBUD_LAY_BASE),     _,                     _,                     _,
                                                                            KC_MS_BTN1,            _,                     _,                                                                         _,                     _,                     KC_MS_BTN2
    ),

    [IBUD_LAY_SYM] = LAYOUT_moonlander(
       KC_AT,                 _,                     _,                     _,                     _,                     _,                     _,                           _,                     _,                     _,                     _,                     _,                     _,                     _,
       KC_TAB,                KC_1,                  KC_2,                  KC_3,                  KC_4,                  KC_5,                  _,                           _,                     KC_6,                  KC_7,                  KC_8,                  KC_9,                  KC_0,                  KC_BACKSLASH,
       KC_DQUO,               KC_COLN,               KC_EQUAL,              KC_PLUS,               KC_LPRN,               KC_ASTR,               KC_ENTER,                    _,                     KC_SLASH,              KC_RPRN,               KC_MINUS,              KC_UNDS,               KC_SEMICOLON,          KC_QUOTE,
       KC_GRAVE,              KC_EXLM,               KC_LABK,               KC_LEFT_BRACKET,       KC_LCBR,               KC_AMPR,                                                                   KC_PIPE,               KC_RCBR,               KC_RIGHT_BRACKET,      KC_RABK,               KC_QUES,               KC_CIRC,
       KC_PERC,               _,                     _,                     _,                     _,                     _,                                                                         _,                     _,                     _,                     _,                     _,                     KC_TILD,
                                                                            KC_SPACE,              _,                     _,                                                                         _,                     _,                     _
    ),
};
#undef _
// clang-format on

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [IBUD_LAY_BASE] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 183, 238}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},

    [IBUD_LAY_GAME] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 183, 238}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},

    [IBUD_LAY_GAME_SF6] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 183, 238}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},

    [IBUD_LAY_NUM] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 220, 201}, {35, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 220, 201}, {255, 220, 201}, {255, 220, 201}, {141, 255, 233}, {0, 0, 0}, {255, 220, 201}, {255, 220, 201}, {255, 220, 201}, {35, 255, 255}, {0, 0, 0}, {255, 220, 201}, {255, 220, 201}, {255, 220, 201}, {255, 220, 201}, {141, 255, 233}, {35, 255, 255}, {35, 255, 255}, {35, 255, 255}, {0, 0, 0}, {35, 255, 255}, {35, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},

    [IBUD_LAY_FKEYS] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {252, 119, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {154, 86, 255}, {154, 86, 255}, {154, 86, 255}, {0, 0, 0}, {0, 0, 0}, {154, 86, 255}, {154, 86, 255}, {154, 86, 255}, {0, 0, 0}, {0, 0, 0}, {154, 86, 255}, {154, 86, 255}, {154, 86, 255}, {252, 119, 255}, {0, 0, 0}, {252, 119, 255}, {252, 119, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},

    [IBUD_LAY_CTRL] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {32, 176, 255}, {0, 0, 0}, {0, 0, 0}, {85, 203, 158}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {85, 203, 158}, {85, 203, 158}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {85, 203, 158}, {0, 183, 238}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {85, 203, 158}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {50, 153, 244}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {134, 255, 213}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {85, 203, 158}, {134, 255, 213}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {85, 203, 158}, {134, 255, 213}, {0, 0, 0}, {0, 183, 238}, {0, 0, 0}, {0, 0, 0}, {134, 255, 213}, {0, 0, 0}, {0, 183, 238}, {0, 0, 0}, {0, 0, 0}, {85, 203, 158}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},

    [IBUD_LAY_SYM] = {{0, 183, 238}, {35, 255, 255}, {0, 183, 238}, {0, 183, 238}, {141, 255, 233}, {0, 0, 0}, {0, 0, 255}, {169, 120, 255}, {85, 203, 158}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {141, 255, 233}, {141, 255, 233}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {141, 255, 233}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {85, 203, 158}, {14, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {141, 255, 233}, {105, 255, 255}, {0, 0, 0}, {0, 0, 0}, {35, 255, 255}, {35, 255, 255}, {0, 183, 238}, {0, 183, 238}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 183, 238}, {105, 255, 255}, {105, 255, 255}, {0, 0, 0}, {0, 0, 255}, {169, 120, 255}, {85, 203, 158}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {141, 255, 233}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {141, 255, 233}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {85, 203, 158}, {14, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {141, 255, 233}, {105, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},

};

void set_layer_color(int layer) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (!hsv.h && !hsv.s && !hsv.v) {
            rgb_matrix_set_color(i, 0, 0, 0);
        } else {
            RGB   rgb = hsv_to_rgb(hsv);
            float f   = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        }
    }
}

bool rgb_matrix_indicators_user(void) {
    if (keyboard_config.disable_layer_led) {
        return false;
    }
    uint8_t layer_num = biton32(layer_state);
    if (layer_num < IBUD_LAYER_TOTAL_COUNT) {
        set_layer_color(layer_num);
        return true;
    } else if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
        rgb_matrix_set_color_all(0, 0, 0);
        return false;
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ST_MACRO_0:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_0) SS_DELAY(100) SS_TAP(X_0) SS_DELAY(100) SS_TAP(X_0));
            }
            break;
        case RGB_SLD:
            if (record->event.pressed) {
                rgblight_mode(1);
            }
            return false;
    }
    return true;
}

typedef struct {
    bool    is_press_action;
    uint8_t step;
} tap;

enum { SINGLE_TAP = 1, SINGLE_HOLD, DOUBLE_TAP, DOUBLE_HOLD, DOUBLE_SINGLE_TAP, MORE_TAPS };

static tap dance_state[6];

uint8_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)
            return SINGLE_TAP;
        else
            return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted)
            return DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return DOUBLE_HOLD;
        else
            return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

void dance_0_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case DOUBLE_TAP:
            layer_move(IBUD_LAY_NUM);
            break;
    }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {}
    dance_state[0].step = 0;
}

void dance_1_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case DOUBLE_TAP:
            layer_move(IBUD_LAY_CTRL);
            break;
    }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {}
    dance_state[1].step = 0;
}

void dance_2_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[2].step = dance_step(state);
    switch (dance_state[2].step) {
        case DOUBLE_TAP:
            layer_move(IBUD_LAY_GAME);
            break;
    }
}

void dance_2_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[2].step) {}
    dance_state[2].step = 0;
}

void dance_3_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[3].step = dance_step(state);
    switch (dance_state[3].step) {
        case DOUBLE_TAP:
            layer_move(IBUD_LAY_BASE);
            break;
    }
}

void dance_3_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[3].step) {}
    dance_state[3].step = 0;
}

// clang-format off
tap_dance_action_t tap_dance_actions[] = {
    [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_0_finished, dance_0_reset),
    [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_1_finished, dance_1_reset),
    [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_2_finished, dance_2_reset),
    [DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_3_finished, dance_3_reset),
};
// clang-format on

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_SPACE):
            return TAPPING_TERM + 100;
        default:
            return TAPPING_TERM;
    }
}

// Enables permissive hold for everything except the space/ctrl dual function key on the
// thumb cluster.
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_SPACE):
            return false;
        default:
            return true;
    }
}

enum combo_events {
    CMB_ESC,
    COMBO_LENGTH,
};

#undef COMBO_COUNT
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM cmb_esc[] = {KC_J, RSFT_T(KC_K), COMBO_END};

combo_t key_combos[] = {
    [CMB_ESC] = COMBO(cmb_esc, KC_ESCAPE),
};
