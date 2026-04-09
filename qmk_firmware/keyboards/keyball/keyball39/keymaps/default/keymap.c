/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [0] = LAYOUT_universal(
  KC_Q            , KC_W    , KC_E    , KC_R    , KC_T    , KC_Y    , KC_U    , KC_I       , KC_O       , KC_P,
  LCTL_T(KC_A)    , KC_S    , KC_D    , KC_F    , KC_G    , KC_H    , KC_J    , KC_K       , KC_L       , KC_SCLN,
  LSFT_T(KC_Z)    , KC_X    , LT(2,KC_C), KC_V  , KC_B    , KC_N    , KC_M    , KC_BTN1    , KC_BTN2    , RSFT_T(KC_SLSH),
  LT(3,KC_ESC)    , LALT_T(KC_NO), LGUI_T(KC_NO), LT(1,KC_LNG1), KC_SPC, KC_TAB, KC_ENT, KC_BSPC, KC_NO, KC_NO, KC_NO, MO(3)
 ),

 [1] = LAYOUT_universal(
  KC_TAB          , KC_LCBR , KC_HASH , KC_RCBR , KC_EXLM , KC_QUES , KC_AT   , KC_TILD    , KC_RPRN    , KC_MINS,
  KC_LCTL         , KC_TILD , KC_LBRC , KC_RBRC , KC_QUES , KC_DQUO , KC_LPRN , KC_PLUS    , KC_EQL     , KC_UNDS,
  KC_LSFT         , KC_PERC , KC_CIRC , KC_DLR  , KC_NO   , KC_GRV  , KC_QUOT , KC_AMPR    , KC_ASTR    , KC_PIPE,
  KC_LSFT         , KC_LALT , KC_LGUI , KC_TRNS , MO(5)   , KC_DEL  , KC_DEL  , KC_RGUI    , KC_RALT, RSFT_T(KC_BSLS), KC_TRNS, KC_TRNS
 ),

 [2] = LAYOUT_universal(
  KC_NO           , KC_LT   , KC_GT   , KC_LCBR , KC_NO   , KC_LEFT , LGUI(KC_LBRC), KC_LBRC, LGUI(KC_RBRC), KC_RBRC,
  KC_LCTL         , KC_LBRC , KC_2    , KC_3    , KC_HASH , KC_PGDN , KC_BTN1 , KC_NO      , KC_BTN2    , KC_NO,
  KC_LSFT         , KC_EXLM , KC_RPRN , KC_0    , KC_TRNS , KC_TRNS , KC_NO   , KC_TRNS    , KC_TRNS    , TO(0),
  KC_TRNS         , KC_TRNS , KC_TRNS , KC_TRNS , MO(2)   , KC_TRNS , KC_TRNS , KC_LGUI    , KC_BSPC    , KC_NO, KC_NO, TO(0)
 ),

 [3] = LAYOUT_universal(
  LALT(KC_7)      , LALT(KC_8), LALT(KC_9), KC_NO, KC_NO, KC_NO, LALT(KC_7), LALT(KC_8), LALT(KC_9), KC_RALT,
  LALT(KC_4)      , LALT(KC_5), LALT(KC_6), KC_NO, KC_NO, KC_LEFT, KC_UP   , KC_RGHT   , KC_NO      , KC_NO,
  LALT(KC_1)      , LALT(KC_2), LALT(KC_3), LALT(KC_0), KC_NO, KC_TRNS, KC_BTN1, KC_BTN2, KC_NO, TO(0),
  KC_TRNS         , KC_LSFT , KC_TRNS , KC_LGUI , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RSFT_T(KC_NO), TO(0)
 ),

 [4] = LAYOUT_universal(
  KC_NO           , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_PAST , KC_8    , KC_AMPR    , KC_7       , KC_PSLS,
  KC_NO           , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_PPLS , KC_5    , KC_DLR     , KC_4       , KC_PEQL,
  KC_NO           , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_2    , KC_EXLM    , KC_1       , KC_PMNS,
  KC_NO           , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_ENT  , KC_BSPC , KC_RPRN    , KC_0       , KC_HASH, KC_3, KC_PDOT
 ),

[5] = LAYOUT_universal(
  KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KBC_RST , KBC_SAVE, CPI_I100, CPI_D100, CPI_I1K,
  KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , CPI_D1K , SCRL_TO , SCRL_MO , SCRL_DVI , SCRL_DVD,
  KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , AML_TO  , AML_I50 , AML_D50 , SSNP_VRT , SSNP_HOR,
  KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO    , KC_NO, KC_NO, SSNP_FRE
),

};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
  // Auto enable scroll mode when the highest layer is 3
  keyball_set_scroll_mode(get_highest_layer(state) == 3);
  return state;
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
  keyball_oled_render_keyinfo();
  keyball_oled_render_ballinfo();
  keyball_oled_render_layerinfo();
}
#endif
