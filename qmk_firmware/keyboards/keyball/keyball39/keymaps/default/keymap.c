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
  // keymap for default (VIA)
  [0] = LAYOUT(
    LCTL_T(KC_Q)     , KC_W           , KC_E           , KC_R           , KC_T           ,                              KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    LCTL_T(KC_A)     , KC_S           , KC_D           , KC_F           , KC_G           ,                              KC_H     , KC_J     , KC_K     , KC_L     , KC_MINS  ,
    LSFT_T(KC_Z)     , KC_X           , KC_C           , KC_V           , KC_B           ,                              KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    LT(3,KC_LCTL)    , LALT_T(KC_DOT) , LGUI_T(KC_COMM),LT(1,KC_LNG1)   , KC_SPC         , LT(3,KC_TAB),     KC_ENT   , KC_BSPC  ,                                  MO(3)    
  ),

  [1] = LAYOUT(
    KC_TAB   , KC_LBRC  , KC_LCBR  , KC_RCBR  , KC_RBRC  ,                                                              KC_QUES  , KC_EXLM  , KC_HASH  , KC_AT    , KC_TILD  ,
    KC_LCTL  , KC_DQUO  , KC_LPRN  , KC_RPRN  , KC_QUOT  ,                                                              KC_CIRC  , KC_MINS  , KC_EQL   , KC_DLR   , KC_MINS  ,
    KC_LSFT  , KC_PERC  , KC_GRV   , KC_AMPR  , KC_ASTR  ,                                                              KC_PIPE  , KC_UNDS  , KC_PLUS  , KC_RABK  , KC_BSLS  ,
    KC_LSFT  , KC_LALT  , KC_LGUI  , _______  , MO(5)    , LGUI_T(KC_DEL)  ,                                 KC_RGUI  , KC_DEL                                    , KC_RSFT  
  ),

  [2] = LAYOUT(
    XXXXXXX  , XXXXXXX  , KC_LABK  , KC_RABK  , XXXXXXX  ,                                                              XXXXXXX  , XXXXXXX  , XXXXXXX        , XXXXXXX        , XXXXXXX  ,
    KC_LCTL  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                                              XXXXXXX  , XXXXXXX  , LGUI(KC_LBRC)  , LGUI(KC_RBRC)  , XXXXXXX  ,
    KC_SLSH  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                                              XXXXXXX  , XXXXXXX  , KC_MS_BTN1     , KC_MS_BTN2     , XXXXXXX  ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_LSFT  , XXXXXXX  , XXXXXXX         ,                                 KC_RGUI  , KC_BSPC  ,                                              XXXXXXX  
  ),

  [3] = LAYOUT(
    XXXXXXX  , LALT(KC_7)  , LALT(KC_8)  , LALT(KC_9)  , XXXXXXX     ,                                                  XXXXXXX  , XXXXXXX  , XXXXXXX     , XXXXXXX     , XXXXXXX  ,
    XXXXXXX  , LALT(KC_4)  , LALT(KC_5)  , LALT(KC_6)  , XXXXXXX     ,                                                  KC_LEFT  , KC_DOWN  , KC_UP       , KC_RIGHT    , XXXXXXX  ,
    RGB_RMOD , LALT(KC_1)  , LALT(KC_2)  , LALT(KC_3)  , LALT(KC_0)  ,                                                  XXXXXXX  , XXXXXXX  , KC_MS_BTN1  , KC_MS_BTN2  , XXXXXXX  ,
    XXXXXXX  , XXXXXXX     , XXXXXXX     , XXXXXXX     , XXXXXXX     , XXXXXXX       ,                       XXXXXXX  , XXXXXXX  ,                       XXXXXXX  
  ),

  [4] = LAYOUT(
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                                              XXXXXXX  , KC_7     , KC_8     , KC_9     , XXXXXXX  ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                                              XXXXXXX  , KC_4     , KC_5     , KC_6     , XXXXXXX  ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                                              KC_0     , KC_1     , KC_2     , KC_3     , KC_PDOT   ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                        KC_ENT   , KC_BSPC                                   , XXXXXXX  
  ),

  [5] = LAYOUT(
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                                              KBC_RST  , KBC_SAVE , CPI_I100 , CPI_D100 , CPI_I1K  ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                                              CPI_D1K  , SCRL_TO  , SCRL_MO  , SCRL_DVI , SCRL_DVD ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                                              AML_TO   , AML_I50  , AML_D50  , SSNP_VRT , SSNP_HOR ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                        XXXXXXX  , XXXXXXX  ,                                  SSNP_FRE 
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
