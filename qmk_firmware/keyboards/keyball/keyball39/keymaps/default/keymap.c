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

#define F_CTL LCTL_T(KC_F)
#define J_CTL RCTL_T(KC_J)

static bool j_down        = false;
static bool f_registered  = false;
static bool f_intercepted = false;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT(
	       KC_Q             , KC_W           , KC_E           , KC_R           , KC_T           ,                               KC_Y          , KC_U          , KC_I          , KC_O          , KC_P           ,
	       LGUI_T(KC_A)     , LALT_T(KC_S)   , LSFT_T(KC_D)   , LCTL_T(KC_F)   , KC_G           ,                               KC_H          , RCTL_T(KC_J)  , RSFT_T(KC_K)  , LALT_T(KC_L)  , LGUI_T(KC_SCLN),
	       KC_Z             , KC_X           , KC_C           , KC_V           , KC_B           ,                               KC_N          , KC_M          , KC_MS_BTN1    , KC_MS_BTN2    , KC_SLSH        ,
	       LT(3,KC_CAPS)    , KC_COMM        , KC_DOT         , LT(1,KC_ESC)   , LT(2,KC_SPC)   , LT(4,KC_TAB),     KC_ENT    , KC_BSPC       ,                                               MO(3)   
	       ),

  [1] = LAYOUT(
	       KC_GRV           , KC_CIRC        , KC_ASTR        , KC_DLR         , KC_PIPE        ,                               KC_QUES       , KC_EXLM       , KC_HASH       , KC_AT         , KC_TILD        ,
	       KC_QUOT          , KC_DQUO        , KC_PLUS        , KC_EQL         , KC_AMPR        ,                               KC_MINS       , KC_LCBR       , KC_LPRN       , KC_RPRN       , KC_RCBR        ,
	       KC_BSLS          , XXXXXXX        , XXXXXXX        , XXXXXXX        , KC_PERC        ,                               KC_UNDS       , KC_LBRC       , KC_LABK       , KC_RABK       , KC_RBRC        ,
	       KC_LSFT          , KC_LALT        , KC_LGUI        , MO(1)          , MO(5)          , LGUI_T(KC_DEL), RSFT_T(KC_ENT), KC_DEL      ,                                               KC_RSFT 
	       ),

  [2] = LAYOUT(
	       LGUI(KC_Q)       , LGUI(KC_W)     , XXXXXXX        , LSFT(LGUI(KC_R)),LGUI(KC_T)     ,                               LSFT(LGUI(KC_Z)),LGUI(KC_1)   , LGUI(KC_2)    , LGUI(KC_3)    , LGUI(KC_4)     ,
	       LGUI(KC_A)       , LGUI(KC_S)     , LGUI(KC_EQL)   , LGUI(KC_F)     , XXXXXXX        ,                               KC_LEFT       , KC_DOWN       , KC_UP         , KC_RIGHT      , XXXXXXX        ,
	       LGUI(KC_Z)       , LGUI(KC_X)     , LGUI(KC_C)     , LGUI(KC_V)     , XXXXXXX        ,                               XXXXXXX       , LGUI(KC_LBRC) , LSFT(LGUI(KC_LBRC)),LSFT(LGUI(KC_RBRC)),LGUI(KC_RBRC),
	       XXXXXXX          , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX       ,   XXXXXXX   , XXXXXXX       ,                                               XXXXXXX 
	       ),

  [3] = LAYOUT(
	       XXXXXXX          , KC_LGUI        , KC_LGUI        , KC_LGUI        , XXXXXXX        ,                               XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX        ,
	       KC_LGUI          , LALT(KC_LGUI)  , LSFT(KC_LGUI)  , LCTL(KC_LGUI)  , XXXXXXX        ,                               XXXXXXX       , LGUI(KC_MINS) , LGUI(KC_EQL)  , XXXXXXX       , XXXXXXX        ,
	       XXXXXXX          , KC_LGUI        , KC_LGUI        , KC_LGUI        , KC_LGUI        ,                               XXXXXXX       , XXXXXXX       , KC_MS_BTN1    , KC_MS_BTN2    , XXXXXXX        ,
	       XXXXXXX          , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX       ,   MO(5)     , XXXXXXX       ,                                               XXXXXXX 
	       ),

  [4] = LAYOUT(
	       KC_F1            , KC_F2          , KC_F3          , KC_F4          , KC_F5          ,                               XXXXXXX       , KC_7          , KC_8          , KC_9          , XXXXXXX        ,
	       KC_F6            , KC_F7          , KC_F8          , KC_F9          , KC_F10         ,                               XXXXXXX       , KC_4          , KC_5          , KC_6          , XXXXXXX        ,
	       KC_F11           , KC_F12         , KC_F13         , KC_F14         , KC_F15         ,                               KC_0          , KC_1          , KC_2          , KC_3          , KC_PDOT        ,
	       SSNP_FRE         , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX       ,   KC_ENT    , KC_BSPC       ,                                               XXXXXXX 
	       ),

  [5] = LAYOUT(
	       KBC_RST          , KBC_SAVE       , CPI_I100       , CPI_D100       , CPI_I1K        ,                               XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX        ,
	       CPI_D1K          , SCRL_TO        , SCRL_MO        , SCRL_DVI       , SCRL_DVD       ,                               XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX        ,
	       AML_TO           , AML_I50        , AML_D50        , SSNP_VRT       , SSNP_HOR       ,                               XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX        ,
	       SSNP_FRE         , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX       ,   XXXXXXX   , XXXXXXX       ,                                               XXXXXXX 
	       ),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case J_CTL:
            j_down = record->event.pressed;
            if (!j_down && f_registered) {
                unregister_code(KC_F);
                f_registered = false;
            }
            return true;

        case F_CTL:
            if (f_intercepted) {
                if (!record->event.pressed) {
                    if (f_registered) {
                        unregister_code(KC_F);
                        f_registered = false;
                    }
                    f_intercepted = false;
                }
                return false;
            }

            if (record->event.pressed && j_down && (get_mods() & MOD_BIT(KC_RCTL))) {
                register_code(KC_F);
                f_registered  = true;
                f_intercepted = true;
                return false;
            }

            return true;
    }

    return true;
}

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
