/* Copyright 2017 Brian Fong
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "gherkin.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define L1 1
#define L2 2
#define L3 3
#define L4 4
#define L5 5


/////////////// TAP DANCE SECTION START ///////////////
//Tap Dance Declarations (list of my tap dance configurations)
enum {
  TD_SFT_CAPS = 0
  ,TD_Q_ESC
  ,ENT_TAP_DANCE
  ,DEL_TAP_DANCE
};

///// QUAD FUNCTION TAP DANCE GENERAL SETUP SECTION START /////
///// (no need to edit this section) /////
//Enums used to clearly convey the state of the tap dance
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5 //send SINGLE_TAP twice - NOT DOUBLE_TAP
  // Add more enums here if you want for triple, quadruple, etc.
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    if (state->interrupted) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap.
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else return 6; //magic number. At some point this method will expand to work for more presses
}
///// QUAD FUNCTION TAP DANCE GENERAL SETUP SECTION END /////
///// QUAD FUNCTION TAP DANCE PERSONALIZATION SECTION START /////
//instantialize an instance of 'tap' for the 'ENT' tap dance.
static tap ENTtap_state = {
  .is_press_action = true,
  .state = 0
};

void ENT_finished (qk_tap_dance_state_t *state, void *user_data) {
  ENTtap_state.state = cur_dance(state);
  switch (ENTtap_state.state) {
    case SINGLE_TAP: register_code(KC_SPC); break;
    case SINGLE_HOLD: register_code(KC_LSFT); break;
    case DOUBLE_TAP: register_code(KC_ENT); break;
    case DOUBLE_HOLD: register_code(KC_NO); break; // setting double hold to do nothing (change this if you want)
    case DOUBLE_SINGLE_TAP: register_code(KC_SPC); unregister_code(KC_SPC); register_code(KC_SPC);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void ENT_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (ENTtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_SPC); break;
    case SINGLE_HOLD: unregister_code(KC_LSFT); break;
    case DOUBLE_TAP: unregister_code(KC_ENT); break;
    case DOUBLE_HOLD: unregister_code(KC_NO);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_SPC);
  }
  ENTtap_state.state = 0;
}

//instanalize an instance of 'tap' for the 'DEL' tap dance.
static tap DELtap_state = {
  .is_press_action = true,
  .state = 0
};

void DEL_finished (qk_tap_dance_state_t *state, void *user_data) {
  DELtap_state.state = cur_dance(state);
  switch (DELtap_state.state) {
    case SINGLE_TAP: register_code(KC_BSPC); break;
    case SINGLE_HOLD: register_code(KC_LCTL); break;
    case DOUBLE_TAP: register_code(KC_DEL); break;
    case DOUBLE_HOLD: register_code(KC_NO); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_BSPC); unregister_code(KC_BSPC); register_code(KC_BSPC);
  }
}

void DEL_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (DELtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_BSPC); break;
    case SINGLE_HOLD: unregister_code(KC_LCTL); break;
    case DOUBLE_TAP: unregister_code(KC_DEL); break;
    case DOUBLE_HOLD: unregister_code(KC_NO);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_BSPC);
  }
  DELtap_state.state = 0;
}
///// QUAD FUNCTION TAP DANCE PERSONALIZATION SECTION END /////

//Tap Dance Definitions
//THIS SECTION HAS TO BE AT THE END OF THE TAP DANCE SECTION
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
// Other declarations would go here, separated by commas, if you have them
 ,[TD_Q_ESC]  = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC)
 ,[ENT_TAP_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ENT_finished, ENT_reset)
 ,[DEL_TAP_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, DEL_finished, DEL_reset)
};

//In Layer declaration, add tap dance item in place of a key code
//TD(TD_SFT_CAPS)

///////////// TAP DANCE SECTION END ///////////////

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /* Qwerty
 * .------------------------------------------------------------------------------------------ .
 * | Q/ESC  | W      | E      | R      | T      | Y      | U      | I      | O      | P       |
 * |        |        |        |        |        |        |        |        |        |         |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+---------|
 * | A/GUI  | S      | D      | F      | G      | H      | J      | K      | L      | ESC     |
 * |        |        |        |        |        |        |        |        |        |         |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+---------|
 * | Z      | X/ALT  | C/L3   | V/L4   |BCKSpace| Space  | B/L5   | N      | M      | ENTER   |
 * |CTRLhold|        |        |        |L2      | L1     |        |ALThold |CTRLHold|SHIFThold|
 * '------------------------------------------------------------------------------------------'
 */

 [_QW] = KEYMAP( /* Qwerty*/
   TD(TD_Q_ESC),    KC_W,           KC_E,            KC_R,         KC_T,            KC_Y,             KC_U,         KC_I,        KC_O,        KC_P,
   GUI_T(KC_A),     KC_S,           KC_D,            KC_F,         KC_G,            KC_H,             KC_J,         KC_K,        KC_L,        KC_ENTER,                                          
   LCTL_T(KC_Z),    ALT_T(KC_X),    LT(L3, KC_C),    LT(L4, KC_V), LT(L2, KC_BSPC), LT(L1, KC_SPACE), LT(L5, KC_B), ALT_T(KC_N), CTL_T(KC_M), KC_LSFT

  ),


//
///*
// *  L1
// * .-----------------------------------------------------------------------------------------.
// * | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      |
// * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
// * | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    |
// * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
// * |        |        |        |        | DEL    |        |        |        |        |        |
// * '-----------------------------------------------------------------------------------------'
// */
//
[L1] = KEYMAP( /* L1 */
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),
//
// /*
//  *  L2
//  * .-----------------------------------------------------------------------------------------.
//  * | !      | @      | #      | $      | %      | ^      | &      | *      | (      | )      |
//  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
//  * | F11    | F12    |        |        |        |        |        |        |        | `      |
//  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
//  * |        |        |        |        |        |        |        |        |        |        |
//  * '-----------------------------------------------------------------------------------------'
//  */
//
[L2] = KEYMAP ( /* L2 */
  KC_EXLM,   KC_AT,   KC_HASH,   KC_DLR,   KC_CIRC,   KC_PERC,   KC_AMPR,   KC_ASTR,   KC_LPRN,   KC_RPRN    ,
  KC_F11,    KC_F12,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_GRV  ,
  KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),
//
// /*
//  *  L3
//  * .-----------------------------------------------------------------------------------------.
//  * |        |        |        |        |        | -      | =      | [      | ]      | \      |
//  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
//  * | TAB    |        |        |        |        | ,      | .      | /      | ;      | '      |
//  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
//  * |        |        |        |        |        |        | left   | down   | up     | right  |
//  * '-----------------------------------------------------------------------------------------'
//  */
//
[L3] = KEYMAP ( /* L3 */
  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_MINS,   KC_EQL,   KC_LBRC,   KC_RBRC,   KC_BSLS  ,
  KC_TAB,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_COMM,    KC_DOT,    KC_SLSH,    KC_SCLN,    KC_QUOT    ,
  KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT
),
//
//
//  /*
//   *  L4
//   * .-----------------------------------------------------------------------------------------.
//   * |        |        |        |        |        | _      | +      | {      | }      | |      |
//   * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
//   * | TAB    |        |        |        |        | <      | >      | ?      | :      | "      |
//   * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
//   * |        |        |        |        |        |        | Home   | PgDown | PgUp   | End   |
//   * '-----------------------------------------------------------------------------------------'
//   */
//
[L4] = KEYMAP( /* L4 */
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE ,
  KC_TAB,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LT, KC_GT, KC_QUES, KC_COLN, KC_DQT ,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDOWN, KC_PGUP, KC_END
 ),
//
// /*
//  *  L5
//  * .-----------------------------------------------------------------------------------------.
//  * |        |        |        |        |        |        |        |        |        |PrntScr |
//  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
//  * |        |        |        |        |        |        |        |        |        |        |
//  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
//  * |        |        |        |        | RESET  |        |        |        |        |        |
//  * '-----------------------------------------------------------------------------------------'
//  */
//
[L5] = KEYMAP ( /* L5 */
  KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR,
  KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS, RESET, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),
};
