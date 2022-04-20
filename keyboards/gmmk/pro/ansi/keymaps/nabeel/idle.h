#pragma once



#ifdef IDLE_TIMEOUT_ENABLE
        static uint16_t timeout_timer = 0;
        static uint16_t timeout_counter = 0;  //in minute intervals
        static uint16_t timeout_threshold = TIMEOUT_THRESHOLD_DEFAULT;

        uint16_t get_timeout_threshold(void) {
            return timeout_threshold;
        }

        void timeout_reset_timer(void) {
            timeout_timer = timer_read();
            timeout_counter = 0;
        };

        void timeout_update_threshold(bool increase) {
            if (increase && timeout_threshold < TIMEOUT_THRESHOLD_MAX) timeout_threshold++;
            if (!increase && timeout_threshold > 0) timeout_threshold--;
        };

        void timeout_tick_timer(void) {
            if (timeout_threshold > 0) {
                if (timer_elapsed(timeout_timer) >= 60000) { // 1 minute tick
                    timeout_counter++;
                    timeout_timer = timer_read();
                }
#ifdef RGB_MATRIX_ENABLE
                if (timeout_threshold > 0 && timeout_counter >= timeout_threshold) {
                    rgb_matrix_disable_noeeprom();
                }
#endif
            } // timeout_threshold = 0 will disable timeout
        }

#endif // IDLE_TIMEOUT_ENABLE