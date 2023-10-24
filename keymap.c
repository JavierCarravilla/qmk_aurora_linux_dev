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
  PRT_SCR = SAFE_RANGE,
  DBG_EVA
};

#define LGUI_KA LGUI_T(KC_A)
#define LALT_KS LALT_T(KC_S)
#define LSFT_KD LSFT_T(KC_D)
#define LCTL_KF LCTL_T(KC_F)

#define RGUI_KSCLN RGUI_T(KC_SCLN)
#define LALT_KL LALT_T(KC_K)
#define RSFT_KK RSFT_T(KC_K)
#define RCTL_KJ RCTL_T(KC_J)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

   [_QUERTY] = LAYOUT_split_3x6_3(
        //|-----------------------------------------------------|        |------------------------------------------------------|
            QK_GESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,    KC_O,      KC_P, KC_BSPC,
             KC_TAB, LGUI_KA, LALT_KS, LSFT_KD, LCTL_KF,    KC_G,            KC_H, RCTL_KJ, RSFT_KK, LALT_KL,RGUI_KSCLN, KC_QUOT,
            KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,            KC_N,    KC_M, KC_COMM,  KC_DOT,   KC_SLSH, KC_RSFT,
        //|-----------------------------------------------------|        |------------------------------------------------------|
                                     KC_LSFT, MO(_LOWER), KC_SPC,          KC_ENT, MO(_RAISE), KC_RALT
                                 //|----------------------------|        |----------------------------|
   ),

   [_LOWER] = LAYOUT_split_3x6_3(
        //|-----------------------------------------------------|        |-----------------------------------------------------|
            QK_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,     KC_9,    KC_0, KC_BSPC,
             KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, PRT_SCR,   KC_F5,         KC_LEFT, KC_DOWN,   KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX,
            KC_LSFT, DBG_EVA,   KC_F7,   KC_F8,   KC_F9, XXXXXXX,         KC_HOME, KC_PGDN, KC_PGUP,   KC_END, XXXXXXX, KC_RSFT,
        //|-----------------------------------------------------|        |-----------------------------------------------------|
                                        KC_LSFT, _______, KC_SPC,          KC_ENT, MO(_RAISE), KC_RALT
                                 //|----------------------------|        |----------------------------|
   ),

   [_RAISE] = LAYOUT_split_3x6_3(
        //|-----------------------------------------------------|        |-----------------------------------------------------|
            QK_GESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
             KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
            KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
        //|-----------------------------------------------------|        |-----------------------------------------------------|
                                     KC_LSFT, MO(_LOWER), KC_SPC,           KC_ENT, _______, KC_RALT
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
    case PRT_SCR:  // Macro to printscreen in ubuntu.
      if (record->event.pressed) {
        SEND_STRING(SS_LSFT(SS_LCTL(X_PSCR));
      }
      return false;
    case DBG_EVA: // Macro to evaluate expresion while debuging
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_LSFT(X_8));
      }
      return false;
  }
  return true;
}

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    NULL // Null terminate the array of overrides!
};
