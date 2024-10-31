/* Copyright 2023 Javier Carravilla
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

#include QMK_KEYBOARD_H

enum layer_names {
   _QUERTY,
   _LOWER,
   _RAISE,
   _ADJUST,
};

enum custom_keycodes {
  DBG_EVA = SAFE_RANGE,
  SEL_COL
};

enum {
  TD_PRT_SCR,
  TD_RFS_BWR
};

// Tap dance functions
void dance_prt_scr(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    // Print screen to clipboard
    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_LCTL) SS_DOWN(X_PSCR));
  } else if (state->count >= 1) {
    // Print screen to save dialog
    SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_PSCR));
  }
  clear_keyboard();
};

void start_dance_refresh_browser(tap_dance_state_t *state, void *user_data) {
  // F5 shortcut to refresh the browser
  if (state->count == 1) {
    register_code16(KC_F5);
  } else if (state->count >= 1) {
    // With double tap hard refresh
    SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_F5));
    clear_keyboard();
  }
};

void reset_dance_refresh_browser(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code16(KC_F5);
  }
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
  // Print screen to clipboard on single tap and store it with double
  [TD_PRT_SCR] = ACTION_TAP_DANCE_FN(dance_prt_scr),
  // F5 on single tap, SHIFT + F5 on double
  [TD_RFS_BWR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, start_dance_refresh_browser, reset_dance_refresh_browser)
};

// Left-hand home rows mods
#define LALT_KS LALT_T(KC_S)
#define LSFT_KD LSFT_T(KC_D)
#define LCTL_KF LCTL_T(KC_F)

// Right-hand home rows mods
#define LALT_KL LALT_T(KC_L)
#define RSFT_KK RSFT_T(KC_K)
#define RCTL_KJ RCTL_T(KC_J)

//Tap dance alias
#define PRT_SCR TD(TD_PRT_SCR)
#define RFS_BWR TD(TD_RFS_BWR)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

   [_QUERTY] = LAYOUT_split_3x6_3(
        //|-----------------------------------------------------|        |------------------------------------------------------|
            QK_GESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,    KC_O,      KC_P, KC_BSPC,
             KC_TAB,    KC_A, LALT_KS, LSFT_KD, LCTL_KF,    KC_G,            KC_H, RCTL_KJ, RSFT_KK, LALT_KL,   KC_SCLN, KC_QUOT,
            KC_LGUI,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,            KC_N,    KC_M, KC_COMM,  KC_DOT,   KC_SLSH, KC_RSFT,
        //|-----------------------------------------------------|        |------------------------------------------------------|
                                     KC_LSFT, MO(_LOWER), KC_SPC,          KC_ENT, MO(_RAISE), KC_RALT
                                 //|----------------------------|        |----------------------------|
   ),

   [_LOWER] = LAYOUT_split_3x6_3(
        //|-----------------------------------------------------|        |-----------------------------------------------------|
            QK_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,     KC_9,    KC_0, KC_BSPC,
             KC_TAB, XXXXXXX, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX,         KC_LEFT, KC_DOWN,   KC_UP, KC_RIGHT, RFS_BWR, PRT_SCR,
            KC_LGUI, DBG_EVA,   KC_F7,   KC_F8,   KC_F9, XXXXXXX,         KC_HOME, KC_PGDN, KC_PGUP,   KC_END, SEL_COL, KC_RSFT,
        //|-----------------------------------------------------|        |-----------------------------------------------------|
                                        KC_LSFT, _______, KC_SPC,          KC_ENT, MO(_ADJUST), KC_RALT
                                 //|----------------------------|        |----------------------------|
   ),

   [_RAISE] = LAYOUT_split_3x6_3(
        //|-----------------------------------------------------|        |-----------------------------------------------------|
            QK_GESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
             KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
            KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
        //|-----------------------------------------------------|        |-----------------------------------------------------|
                                     KC_LSFT, MO(_ADJUST), KC_SPC,           KC_ENT, _______, KC_RALT
                                 //|----------------------------|        |----------------------------|
   ),

   [_ADJUST] = LAYOUT_split_3x6_3(
        //|-----------------------------------------------------|        |-----------------------------------------------------|
            QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|-----------------------------------------------------|        |-----------------------------------------------------|
                                        KC_LSFT, _______, KC_SPC,           KC_ENT, _______, KC_RALT
                                 //|----------------------------|        |----------------------------|
   )
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case DBG_EVA: // Macro to evaluate expresion while debuging
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_LSFT) SS_DOWN(X_8));
      } else {
        clear_keyboard();
      }
      break;
    case SEL_COL: // Macro to enable column selection in intelliJ
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_LALT) SS_DOWN(X_INS));
      } else {
        clear_keyboard();
      }
      break;
  }
  return true;
}

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)


//Overriding the delete key https://docs.qmk.fm/features/key_overrides#simple-example
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
  &delete_key_override
};

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  rgblight_sethsv_noeeprom(HSV_CYAN);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}
#endif
