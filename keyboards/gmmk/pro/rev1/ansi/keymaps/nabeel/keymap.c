/* Copyright 2021 stickandgum GMMK Pro ANSI Enhanced Keymap File
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

#include "encoder.h"
#include "idle.h"
#include "rgb_matrix_map.h"

enum my_keycodes {
  LED_KEY_TILDE = SAFE_RANGE,
  LED_KEY_1,
  LED_KEY_2,
  LED_KEY_3,
  LED_KEY_4,
  LED_KEY_5,
  LED_KEY_6,
  LED_KEY_7,
  LED_KEY_8,
  LED_KEY_9,
  LED_KEY_0,
  LED_KEY_MINS,
  LED_KEY_EQL,
  QMKBEST,
  SWITCH_PC_1,
  SWITCH_PC_2
};

enum custom_user_layers {
    _BASE,
    _FN1,
    _LOWER,
    _RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5        F6       F7       F8       F9       F10      F11      F12      Prt           Rotary(Play/Pause)
//      ~        1        2        3        4        5         6        7        8        9        0         -       (=)      BackSpc           Del
//      Tab      Q        W        E        R        T         Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G         H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V         B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                                SPACE                               Alt_R    FN       Ct_R     Left     Down     Right

    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MEDIA_PLAY_PAUSE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_END,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGUP,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                             KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN1] = LAYOUT(
        _______, SWITCH_PC_1, SWITCH_PC_2, KC_MSEL, KC_MAIL,  KC_WHOM, _______, _______, _______, _______, _______, KC_WAKE, KC_SLEP, KC_PAUS,         _______,
      LED_KEY_TILDE, LED_KEY_1,  LED_KEY_2,   LED_KEY_3,   LED_KEY_4,  LED_KEY_5, LED_KEY_6, LED_KEY_7, LED_KEY_8, LED_KEY_9, LED_KEY_0, LED_KEY_MINS, LED_KEY_EQL, KC_INS, KC_SCRL,
      // tab     q         w         e        r        t       y          u        i         o       p         [       ]
        _______, RGB_SAI, RGB_VAI, RGB_HUI, RGB_TOG,  _______, _______, _______, _______, _______, _______, _______, _______, RESET,           KC_BRIU,
        // caps   a         s         d         f        g       h         j        k        l      m        n                 o                enter
       _______, RGB_RMOD, RGB_VAD, RGB_MOD, RGB_SPI, _______,  _______, _______, _______, QMKBEST, _______, _______,  _______,          KC_BRID,
        RGB_SPD,          _______, _______, _______, _______,  _______, NK_TOGG, _______, _______, _______, _______,         _______, KC_MPLY, KC_PWR,
        _______, _______, _______,                             _______,                            KC_RALT, _______, KC_APP, KC_MPRV, KC_MSTP, KC_MNXT
    ),

};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  // https://beta.docs.qmk.fm/using-qmk/simple-keycodes/feature_advanced_keycodes#alt-escape-for-alt-tab-id-alt-escape-for-alt-tab
  if (get_mods() & MOD_MASK_CTRL) { // If CTRL is held
    uint8_t mod_state = get_mods(); // Store all  modifiers that are held
    unregister_mods(MOD_MASK_CTRL); // Immediately unregister the CRTL key (don't send CTRL-PgDn) - del_mods doesn't work here (not immediate)
    if (clockwise) {
      tap_code(KC_PGDN);
    } else {
      tap_code(KC_PGUP);
    }
    set_mods(mod_state); // Add back in the CTRL key - so ctrl-key will work if ctrl was never released after paging.
  } else if (get_mods() & MOD_MASK_SHIFT) {
    uint8_t mod_state = get_mods();
    unregister_mods(MOD_MASK_SHIFT);
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE   // If using the mouse scroll - make sure MOUSEKEY is enabled
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_VOLU);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_VOLD);
      #endif
    }
    set_mods(mod_state);
  } else if (clockwise) { // All else volume.
    tap_code(KC_VOLU);
  } else {
    tap_code(KC_VOLD);
  }
  //return true; //set to return false to counteract enabled encoder in pro.c
  return false;
}

#endif //ENCODER_ENABLE

//static void send_switch_hotkey(int pc);

#ifdef RGB_MATRIX_ENABLE
static void set_rgb_caps_leds_on(void);
static void set_rgb_scroll_leds_on(void);
static void set_rgb_caps_leds_off(void);
static void set_rgb_scroll_leds_off(void);

bool rgb_matrix_indicators_kb(void) {
//    if (get_rgb_nightmode()) rgb_matrix_set_color_all(RGB_OFF);
    if (host_keyboard_led_state().scroll_lock) {
        set_rgb_scroll_leds_on();
    } else {
        set_rgb_scroll_leds_off();
    }

    if (host_keyboard_led_state().caps_lock) {
        set_rgb_caps_leds_on();
    } else {
        set_rgb_caps_leds_off();
    }

    return true;
}

// Called on powerup and is the last _init that is run.
void keyboard_post_init_user(void) {

   int mods[35] = {0,2,3,4,5,11,17,33,49,55,65,95,97,79,94,85,93,96,90,69,92,67,76,80,91,75,86,68,77,81,92,28,34,39,44};
   int j;

   /* output each array element's value */
   for (j = 0; j < 35; j++ ) {
      g_led_config.flags[mods[j]] = LED_FLAG_MODIFIER;
   }

  if (!rgb_matrix_is_enabled()) {
      rgb_matrix_enable();
#ifdef CONSOLE_ENABLE
      uprintf("ERROR! RGB Matrix Enabled and wrote to EEPROM! -How was the RGB Matrix Disabled?");
#endif
     }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
     case RGB_TOG:
      if (record->event.pressed) {
         if (rgb_matrix_get_flags() == LED_FLAG_ALL) {
              rgb_matrix_set_flags(LED_FLAG_NONE);
              rgb_matrix_set_color_all(0, 0, 0);
          } else {
              rgb_matrix_set_flags(LED_FLAG_ALL);
          }
      }
      return false;
    case LED_KEY_TILDE:
        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);          // Can use RGB_M_P built-in keycode instead.
        break;
     case LED_KEY_1:
        rgb_matrix_mode(RGB_MATRIX_CYCLE_LEFT_RIGHT);
        break;
    case LED_KEY_2:
        rgb_matrix_mode(RGB_MATRIX_GRADIENT_LEFT_RIGHT);
        break;
    case LED_KEY_3:
        rgb_matrix_mode(RGB_MATRIX_JELLYBEAN_RAINDROPS);
        break;
    case LED_KEY_4:
        rgb_matrix_mode(RGB_MATRIX_BAND_SAT);
        break;
    case LED_KEY_5:
        rgb_matrix_mode(RGB_MATRIX_BAND_VAL);
        break;
    case LED_KEY_6:
        rgb_matrix_mode(RGB_MATRIX_BAND_SPIRAL_VAL);
        break;
    case LED_KEY_7:
        rgb_matrix_mode(RGB_MATRIX_CYCLE_LEFT_RIGHT);    // Can use RGB_M_R built-in keycode instead.
        break;
    case LED_KEY_8:
        rgb_matrix_mode(RGB_MATRIX_CYCLE_PINWHEEL);      // Can use RGB_M_SW built-in keycode instead.
        break;
    case LED_KEY_9:
         rgb_matrix_mode(RGB_MATRIX_BREATHING);          // Can use RGB_M_B built-in keycode instead.
        break;
    case QMKBEST:
      if (record->event.pressed) { // when keycode QMKBEST is pressed
          SEND_STRING("QMK rocks");
        } else { // when keycode QMKBEST key is released
          SEND_STRING("!!");
        }
        break;

    /**
     * Send a hotkey to the switch to change to PC 1
     */
    case SWITCH_PC_1:
        if (record->event.pressed) {
            //send_switch_hotkey(1);
        }

        break;

    /**
     * Send a hotkey to the switch to change to PC 2
     */
    case SWITCH_PC_2:
        if (record->event.pressed) {
            //send_switch_hotkey(2);
        }

        break;
  }

  return true;
}

/**
 * @brief Send the hotkey to the switch to change from pc1 or pc 2
 *
 * @param pc 1 or 2
 */
/*
static void send_switch_hotkey(int pc) {
    SEND_STRING(SS_TAP(X_SCROLLLOCK));
    SEND_STRING(SS_DELAY(500));
    SEND_STRING(SS_TAP(X_SCROLLLOCK));
    SEND_STRING(SS_DELAY(500));

    if (pc == 1) {
        SEND_STRING(SS_TAP(X_1));
    } else {
        SEND_STRING(SS_TAP(X_2));
    }

    SEND_STRING(SS_DELAY(500));

    SEND_STRING(SS_TAP(X_WAKE));
}
*/
// RGB led number layout, function of the key

//  67, led 01   0, ESC    6, F1      12, F2      18, F3   23, F4   28, F5      34, F6   39, F7   44, F8      50, F9   56, F10   61, F11    66, F12    69, Prt       Rotary(Mute)   68, led 12
//  70, led 02   1, ~      7, 1       13, 2       19, 3    24, 4    29, 5       35, 6    40, 7    45, 8       51, 9    57, 0     62, -_     78, (=+)   85, BackSpc   72, Home       71, led 13
//  73, led 03   2, Tab    8, Q       14, W       20. E    25, R    30, T       36, Y    41, U    46, I       52, O    58, P     63, [{     89, ]}     93, \|        75, PgUp       74, led 14
//  76, led 04   3, Caps   9, A       15, S       21, D    26, F    31, G       37, H    42, J    47, K       53, L    59, ;:    64, '"                96, Enter     86, PgDn       77, led 15
//  80, led 05   4, Sh_L   10, Z      16, X       22, C    27, V    32, B       38, N    43, M    48, ,<      54, .<   60, /?               90, Sh_R   94, Up        82, End        81, led 16
//  83, led 06   5, Ct_L   11,Win_L   17, Alt_L                     33, SPACE                     49, Alt_R   55, FN             65, Ct_R   95, Left   97, Down      79, Right      84, led 17
//  87, led 07                                                                                                                                                                      88, led 18
//  91, led 08                                                                                                                                                                      92, led 19

static void set_rgb_caps_leds_on() {
    // f1 -> f12 keys
    rgb_matrix_set_color(LED_F1, 255, 0, 0);
    rgb_matrix_set_color(LED_F2, 255, 0, 0);
    rgb_matrix_set_color(LED_F3, 255, 0, 0);
    rgb_matrix_set_color(LED_F4, 255, 0, 0);
    rgb_matrix_set_color(LED_F5, 255, 0, 0);
    rgb_matrix_set_color(LED_F6, 255, 0, 0);
    rgb_matrix_set_color(LED_F7, 255, 0, 0);
    rgb_matrix_set_color(LED_F8, 255, 0, 0);
    rgb_matrix_set_color(LED_F9, 255, 0, 0);
    rgb_matrix_set_color(LED_F10, 255, 0, 0);
    rgb_matrix_set_color(LED_F11, 255, 0, 0);
    rgb_matrix_set_color(LED_F12, 255, 0, 0);
}

static void set_rgb_caps_leds_off() {
    // f1 -> f12 keys
    rgb_matrix_set_color(LED_F1, 0, 0, 0);
    rgb_matrix_set_color(LED_F2, 0, 0, 0);
    rgb_matrix_set_color(LED_F3, 0, 0, 0);
    rgb_matrix_set_color(LED_F4, 0, 0, 0);
    rgb_matrix_set_color(LED_F5, 0, 0, 0);
    rgb_matrix_set_color(LED_F6, 0, 0, 0);
    rgb_matrix_set_color(LED_F7, 0, 0, 0);
    rgb_matrix_set_color(LED_F8, 0, 0, 0);
    rgb_matrix_set_color(LED_F9, 0, 0, 0);
    rgb_matrix_set_color(LED_F10, 0, 0, 0);
    rgb_matrix_set_color(LED_F11, 0, 0, 0);
    rgb_matrix_set_color(LED_F12, 0, 0, 0);
}

static void set_rgb_scroll_leds_on() {
        rgb_matrix_set_color(72, 255, 255, 255); // Under Rotary (HOME)
}

static void set_rgb_scroll_leds_off() {
        rgb_matrix_set_color(72, 0, 0, 0); // Under Rotary (HOME)
}

#endif // RGB_MATRIX_ENABLE
