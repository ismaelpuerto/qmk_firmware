#include QMK_KEYBOARD_H

//Tap Dance Declarations
enum {
  TD_Z_LCTL = 0,
  TD_X_LGUI = 1,
  TD_C_LALT = 2,
  TD_A_TAB = 3,
  TD_Q_ESC = 4,
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_Z_LCTL]  = ACTION_TAP_DANCE_DOUBLE(KC_Z, KC_LCTL),
  [TD_X_LGUI]  = ACTION_TAP_DANCE_DOUBLE(KC_X, KC_LGUI),
  [TD_C_LALT]  = ACTION_TAP_DANCE_DOUBLE(KC_C, KC_LALT),
  [TD_A_TAB]  = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_TAB),
  [TD_Q_ESC]  = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC)
};

enum ghekin_layers {
  _QW,
  _L1,
  _L2,
  _L3,
  _L4,
  _L5
};

enum gherkin_keycodes {
    QW = SAFE_RANGE,
    L1,
    L2,
    L3,
    L4,
    L5
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QW] = LAYOUT_ortho_3x10 ( /* Qwerty*/
            TD(TD_Q_ESC),    KC_W,           KC_E,            KC_R,         KC_T,            KC_Y,             KC_U,         KC_I,        KC_O,        KC_P,
            GUI_T(KC_A),     KC_S,           KC_D,            KC_F,         KC_G,            KC_H,             KC_J,         KC_K,        KC_L,        KC_ENTER,
            LCTL_T(KC_Z),    ALT_T(KC_X),    LT(_L3, KC_C),    LT(_L4, KC_V), LT(_L2, KC_BSPC), LT(_L1, KC_SPACE), LT(_L5, KC_B), ALT_T(KC_N), CTL_T(KC_M), KC_LSFT
            ),
    [_L1] = LAYOUT_ortho_3x10 ( /* L1 */
            KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
            KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
            ),
    [_L2] = LAYOUT_ortho_3x10 ( /* L2 */
            KC_EXLM,   KC_AT,   KC_HASH,   KC_DLR,   KC_CIRC,   KC_PERC,   KC_AMPR,   KC_ASTR,   KC_LPRN,   KC_RPRN    ,
            KC_F11,    KC_F12,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_GRV  ,
            KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
            ),
    [_L3] = LAYOUT_ortho_3x10 ( /* L3 */
            KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_MINS,   KC_EQL,   KC_LBRC,   KC_RBRC,   KC_BSLS  ,
            KC_TAB,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_COMM,    KC_DOT,    KC_SLSH,    KC_SCLN,    KC_QUOT    ,
            KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT
            ),
    [_L4] = LAYOUT_ortho_3x10 ( /* L4 */
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE ,
            KC_TAB,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LT, KC_GT, KC_QUES, KC_COLN, KC_DQT ,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDOWN, KC_PGUP, KC_END
            ),
    [_L5] = LAYOUT_ortho_3x10 ( /* L5 */
            KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR,
            KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS, RESET, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
            ),
};
