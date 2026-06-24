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

#define L1_ESC LT(1, KC_NO)
#define L1_ESC_DOUBLE_TAP_TERM 200

#define L1_QUOT_GUI LGUI_T(KC_F16)
#define L1_DQUO_ALT LALT_T(KC_F16)
#define L1_PLUS_SFT LSFT_T(KC_F16)
#define L1_EQL_CTL LCTL_T(KC_F16)
#define L1_LCBR_CTL RCTL_T(KC_F16)
#define L1_LPRN_SFT RSFT_T(KC_F16)
#define L1_RPRN_ALT RALT_T(KC_F16)
#define L1_RCBR_GUI RGUI_T(KC_F16)

#define L2_CMD_A_GUI LGUI_T(KC_F17)
#define L2_CMD_S_ALT LALT_T(KC_F17)
#define L2_CMD_EQL_SFT LSFT_T(KC_F17)
#define L2_CMD_F_CTL LCTL_T(KC_F17)

static bool j_down        = false;
static bool f_registered  = false;
static bool f_intercepted = false;
static bool l1_esc_tapped = false;
static uint16_t l1_esc_timer;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for mac
  [0] = LAYOUT(
	       KC_Q             , KC_W           , KC_E           , KC_R           , KC_T           ,                               KC_Y          , KC_U          , KC_I          , KC_O          , KC_P           ,
	       LGUI_T(KC_A)     , LALT_T(KC_S)   , LSFT_T(KC_D)   , LCTL_T(KC_F)   , KC_G           ,                               KC_H          , RCTL_T(KC_J)  , RSFT_T(KC_K)  , RALT_T(KC_L)  , RGUI_T(KC_SCLN),
	       KC_Z             , KC_X           , KC_C           , KC_V           , KC_B           ,                               KC_N          , KC_M          , KC_MS_BTN1    , KC_MS_BTN2    , KC_SLSH        ,
	       LT(3,KC_CAPS)    , KC_COMM        , KC_DOT         , L1_ESC         , LT(2,KC_SPC)   , LT(4,KC_TAB),     KC_ENT    , KC_BSPC       ,                                               MO(3)
	       ),

  [1] = LAYOUT(
	       KC_GRV           , KC_CIRC        , KC_ASTR        , KC_DLR         , KC_PIPE        ,                               KC_QUES       , KC_EXLM       , KC_HASH       , KC_AT         , KC_TILD        ,
	       L1_QUOT_GUI      , L1_DQUO_ALT    , L1_PLUS_SFT    , L1_EQL_CTL     , KC_AMPR        ,                               KC_MINS       , L1_LCBR_CTL   , L1_LPRN_SFT   , L1_RPRN_ALT   , L1_RCBR_GUI    ,
	       KC_BSLS          , XXXXXXX        , XXXXXXX        , XXXXXXX        , KC_PERC        ,                               KC_UNDS       , KC_LBRC       , KC_LABK       , KC_RABK       , KC_RBRC        ,
	       KC_LSFT          , KC_LALT        , KC_LGUI        , MO(1)          , MO(5)          , LGUI_T(KC_DEL), RSFT_T(KC_ENT), KC_DEL      ,                                               KC_RSFT
	       ),

  [2] = LAYOUT(
	       LGUI(KC_Q)       , LGUI(KC_W)     , XXXXXXX        , LSFT(LGUI(KC_R)),LGUI(KC_T)     ,                               LSFT(LGUI(KC_Z)),LGUI(KC_1)   , LGUI(KC_2)    , LGUI(KC_3)    , LGUI(KC_4)     ,
	       L2_CMD_A_GUI     , L2_CMD_S_ALT   , L2_CMD_EQL_SFT , L2_CMD_F_CTL   , XXXXXXX        ,                               KC_LEFT       , KC_DOWN       , KC_UP         , KC_RIGHT      , XXXXXXX        ,
	       LGUI(KC_Z)       , LGUI(KC_X)     , LGUI(KC_C)     , LGUI(KC_V)     , XXXXXXX        ,                               XXXXXXX       , LGUI(KC_LBRC) , LSFT(LGUI(KC_LBRC)),LSFT(LGUI(KC_RBRC)),LGUI(KC_RBRC),
	       XXXXXXX          , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX       ,   XXXXXXX   , XXXXXXX       ,                                               XXXXXXX
	       ),

  [3] = LAYOUT(
	       XXXXXXX          , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        ,                               XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX        ,
	       KC_LGUI          , LALT(KC_LGUI)  , LSFT(KC_LGUI)  , LCTL(KC_LGUI)  , XXXXXXX        ,                               XXXXXXX       , LGUI(KC_MINS) , LGUI(KC_EQL)  , XXXXXXX       , XXXXXXX        ,
	       XXXXXXX          , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        ,                               XXXXXXX       , XXXXXXX       , KC_MS_BTN1    , KC_MS_BTN2    , XXXXXXX        ,
	       XXXXXXX          , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX       ,   XXXXXXX   , MO(5)         ,                                               XXXXXXX
	       ),

  [4] = LAYOUT(
	       KC_F1            , KC_F2          , KC_F3          , KC_F4          , KC_F5          ,                               XXXXXXX       , KC_7          , KC_8          , KC_9          , XXXXXXX        ,
	       KC_F6            , KC_F7          , KC_F8          , KC_F9          , KC_F10         ,                               XXXXXXX       , KC_4          , KC_5          , KC_6          , XXXXXXX        ,
	       KC_F11           , KC_F12         , KC_F13         , KC_F14         , KC_F15         ,                               KC_0          , KC_1          , KC_2          , KC_3          , KC_PDOT        ,
	       SSNP_FRE         , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX       ,   KC_ENT    , KC_BSPC       ,                                               XXXXXXX
	       ),

  [5] = LAYOUT(
	       KBC_SAVE         , CPI_I100       , CPI_D100       , CPI_I1K        , CPI_D1K        ,                               XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX        ,
	       SCRL_TO          , SCRL_MO        , SCRL_DVI       , SCRL_DVD       , AML_TO         ,                               XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX        ,
	       AML_I50          , AML_D50        , SSNP_VRT       , SSNP_HOR       , KBC_RST        ,                               XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX        ,
	       SSNP_FRE         , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX       ,   XXXXXXX   , XXXXXXX       ,                                               XXXXXXX
	       ),
};
// clang-format on

static bool process_custom_mod_tap(uint16_t tap_keycode, keyrecord_t *record) {
    if (record->tap.count) {
        if (record->event.pressed && tap_keycode != KC_NO) {
            tap_code16(tap_keycode);
        }
        return false;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case L1_ESC:
            if (record->tap.count) {
                if (record->event.pressed) {
                    if (l1_esc_tapped && timer_elapsed(l1_esc_timer) <= L1_ESC_DOUBLE_TAP_TERM) {
                        tap_code(KC_ESC);
                        l1_esc_tapped = false;
                    } else {
                        l1_esc_tapped = true;
                    }
                    l1_esc_timer = timer_read();
                }
                return false;
            }
            return true;

        case L1_QUOT_GUI:
            return process_custom_mod_tap(KC_QUOT, record);

        case L1_DQUO_ALT:
            return process_custom_mod_tap(KC_DQUO, record);

        case L1_PLUS_SFT:
            return process_custom_mod_tap(KC_PLUS, record);

        case L1_EQL_CTL:
            return process_custom_mod_tap(KC_EQL, record);

        case L1_LCBR_CTL:
            return process_custom_mod_tap(KC_LCBR, record);

        case L1_LPRN_SFT:
            return process_custom_mod_tap(KC_LPRN, record);

        case L1_RPRN_ALT:
            return process_custom_mod_tap(KC_RPRN, record);

        case L1_RCBR_GUI:
            return process_custom_mod_tap(KC_RCBR, record);

        case L2_CMD_A_GUI:
            return process_custom_mod_tap(LGUI(KC_A), record);

        case L2_CMD_S_ALT:
            return process_custom_mod_tap(LGUI(KC_S), record);

        case L2_CMD_EQL_SFT:
            return process_custom_mod_tap(LGUI(KC_EQL), record);

        case L2_CMD_F_CTL:
            return process_custom_mod_tap(LGUI(KC_F), record);

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
