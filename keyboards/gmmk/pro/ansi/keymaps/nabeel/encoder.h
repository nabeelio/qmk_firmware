#pragma once

// ENCODER ACTIONS
#ifdef ENCODER_ENABLE
    void encoder_action_volume(bool clockwise);
    void encoder_action_mediatrack(bool clockwise);
    void encoder_action_navword(bool clockwise);
    void encoder_action_navpage(bool clockwise);

    uint8_t get_selected_layer(void);
    void encoder_action_layerchange(bool clockwise);

    #if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
        void encoder_action_rgb_speed(bool clockwise);
        void encoder_action_rgb_hue(bool clockwise);
        void encoder_action_rgb_saturation(bool clockwise);
        void encoder_action_rgb_brightness(bool clockwise);
        void encoder_action_rgb_mode(bool clockwise);
    #endif // RGB_MATRIX_ENABLE / RGBLIGHT_ENABLE

    #ifdef ALTTAB_SCROLL_ENABLE
        void encoder_action_alttabscroll(bool clockwise);
        void encoder_toggle_alttabscroll(void);
        void encoder_tick_alttabscroll(void);
    #endif // ALTTAB_SCROLL_ENABLE

    #ifndef DYNAMIC_KEYMAP_LAYER_COUNT
        #define DYNAMIC_KEYMAP_LAYER_COUNT 4  //default in case this is not already defined elsewhere
    #endif
    #ifndef ENCODER_DEFAULTACTIONS_INDEX
        #define ENCODER_DEFAULTACTIONS_INDEX 0  // can select encoder index if there are multiple encoders
    #endif

    void encoder_action_volume(bool clockwise) {
        if (clockwise)
            tap_code_delay(KC_VOLU, 10);
        else
            tap_code_delay(KC_VOLD, 10);
    }

    void encoder_action_mediatrack(bool clockwise) {
        if (clockwise)
            tap_code_delay(KC_MEDIA_NEXT_TRACK, 10);
        else
            tap_code_delay(KC_MEDIA_PREV_TRACK, 10);
    }

    void encoder_action_navword(bool clockwise) {
        if (clockwise)
            tap_code16(LCTL(KC_RGHT));
        else
            tap_code16(LCTL(KC_LEFT));
    }

    void encoder_action_navpage(bool clockwise) {
        if (clockwise)
            tap_code16(KC_PGUP);
        else
            tap_code16(KC_PGDN);
    }

    // LAYER HANDLING
    uint8_t selected_layer = 0;

    uint8_t get_selected_layer(void) {
        return selected_layer;
    }

    void encoder_action_layerchange(bool clockwise) {
        if (clockwise) {
            if(selected_layer  < (DYNAMIC_KEYMAP_LAYER_COUNT - 1)) {
                selected_layer ++;
                layer_move(selected_layer);
            }
        } else {
            if (selected_layer  > 0) {
                selected_layer --;
                layer_move(selected_layer);
            }
        }
    }

    #ifdef RGB_MATRIX_ENABLE
        void encoder_action_rgb_speed(bool clockwise) {
            if (clockwise)
                rgb_matrix_increase_speed_noeeprom();
            else
                rgb_matrix_decrease_speed_noeeprom();
        }
        void encoder_action_rgb_hue(bool clockwise) {
            if (clockwise)
                rgb_matrix_increase_hue_noeeprom();
            else
                rgb_matrix_decrease_hue_noeeprom();
        }
        void encoder_action_rgb_saturation(bool clockwise) {
            if (clockwise)
                rgb_matrix_increase_sat_noeeprom();
            else
                rgb_matrix_decrease_sat_noeeprom();
        }
        void encoder_action_rgb_brightness(bool clockwise) {
            if (clockwise)
                rgb_matrix_increase_val_noeeprom();
            else
                rgb_matrix_decrease_val_noeeprom();
        }
        void encoder_action_rgb_mode(bool clockwise) {
            if (clockwise)
                rgb_matrix_step_noeeprom();
            else
                rgb_matrix_step_reverse_noeeprom();
        }
    #elif defined(RGBLIGHT_ENABLE)
        void encoder_action_rgb_speed(bool clockwise) {
            if (clockwise)
                rgblight_increase_speed_noeeprom();
            else
                rgblight_decrease_speed_noeeprom();
        }
        void encoder_action_rgb_hue(bool clockwise) {
            if (clockwise)
                rgblight_increase_hue_noeeprom();
            else
                rgblight_decrease_hue_noeeprom();
        }
        void encoder_action_rgb_saturation(bool clockwise) {
            if (clockwise)
                rgblight_increase_sat_noeeprom();
            else
                rgblight_decrease_sat_noeeprom();
        }
        void encoder_action_rgb_brightness(bool clockwise) {
            if (clockwise)
                rgblight_increase_val_noeeprom();
            else
                rgblight_decrease_val_noeeprom();
        }
        void encoder_action_rgb_mode(bool clockwise) {
            if (clockwise)
                rgblight_step_noeeprom();
            else
                rgblight_step_reverse_noeeprom();
        }
    #endif // RGB_MATRIX_ENABLE || RGBLIGHT_ENABLE

    #ifdef ALTTAB_SCROLL_ENABLE
        bool is_tab_scrolling = false;
        bool is_alt_tab_active = false;
        uint16_t alt_tab_timer = 0;


        void encoder_toggle_alttabscroll(void) {
            is_tab_scrolling = !is_tab_scrolling;
        }

        void encoder_action_alttabscroll(bool clockwise) {
            if (clockwise) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_mods(MOD_RALT);
                }
                tap_code16(KC_TAB);
            }
            else {
                tap_code16(S(KC_TAB));
            }
            alt_tab_timer = timer_read();
        }

        void encoder_tick_alttabscroll(void) {
            if (is_alt_tab_active) {
                if (timer_elapsed(alt_tab_timer) > 600) {
                    unregister_mods(MOD_RALT);
                    is_alt_tab_active = false;
                }
            }
        }
    #endif // ALTTAB_SCROLL_ENABLE
#endif // ENCODER_ENABLE