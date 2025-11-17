#include "lvgl.h"
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

/* ========= ENUMS Y CONSTANTES ========= */

typedef enum {
    CAT_STATUS_HAPPY = 0,
    CAT_STATUS_UNHAPPY_FOOD,
    CAT_STATUS_UNHAPPY_PLAYTIME,
    CAT_STATUS_UNHAPPY_AFFECTION
} cat_status_t;

typedef enum {
    CAT_STAGE_NORWAY = 0,
    CAT_STAGE_SKATER,
    CAT_STAGE_STREAMER,
    CAT_STAGE_JAPAN
} cat_stage_t;

#define TIMER24_MS      (24UL * 60UL * 60UL * 1000UL)   // 24 horas
#define LONG_PRESS_EVOLVE_MS   3000UL
#define LONG_PRESS_RESET_MS   15000UL

/* ========= FORWARD DE ANIMACIONES (pon tus assets reales) ========= */

// Ejemplo: cada animación es un array de frames + duraciones
// Aquí solo las declaramos; tú las defines en otro .c
extern const void *anim_happy_frames[];
extern const uint16_t anim_happy_frame_count;
extern const uint32_t anim_happy_duration;

extern const void *anim_hungry_frames[];
extern const uint16_t anim_hungry_frame_count;
extern const uint32_t anim_hungry_duration;

extern const void *anim_bored_frames[];
extern const uint16_t anim_bored_frame_count;
extern const uint32_t anim_bored_duration;

extern const void *anim_lonely_frames[];
extern const uint16_t anim_lonely_frame_count;
extern const uint32_t anim_lonely_duration;

extern const void *anim_action_food_frames[];
extern const uint16_t anim_action_food_frame_count;
extern const uint32_t anim_action_food_duration;

extern const void *anim_action_play_frames[];
extern const uint16_t anim_action_play_frame_count;
extern const uint32_t anim_action_play_duration;

extern const void *anim_action_affection_frames[];
extern const uint16_t anim_action_affection_frame_count;
extern const uint32_t anim_action_affection_duration;

extern const void *anim_transition_skater_frames[];
extern const uint16_t anim_transition_skater_frame_count;
extern const uint32_t anim_transition_skater_duration;

extern const void *anim_transition_streamer_frames[];
extern const uint16_t anim_transition_streamer_frame_count;
extern const uint32_t anim_transition_streamer_duration;

extern const void *anim_transition_japan_frames[];
extern const uint16_t anim_transition_japan_frame_count;
extern const uint32_t anim_transition_japan_duration;

extern const void *anim_transition_final_frames[];
extern const uint16_t anim_transition_final_frame_count;
extern const uint32_t anim_transition_final_duration;

extern const void *anim_boot_frames[];
extern const uint16_t anim_boot_frame_count;
extern const uint32_t anim_boot_duration;

/* ========= ESTRUCTURA PRINCIPAL ========= */

typedef struct {
    cat_status_t CAT_STATUS;
    cat_stage_t  CAT_STAGE;

    uint8_t  UNHAPPY_COUNTER;
    bool     FLOW_COMPLETED;

    uint32_t timer24_last_reset_ms;

    bool SCREEN_ON;

    lv_obj_t   *anim_obj;   // lv_animimg del gato
    lv_timer_t *logic_timer;
} cat_engine_t;

static cat_engine_t g_cat;

/* ========= HELPERS DE TIEMPO ========= */

static uint32_t cat_now_ms(void) {
    return lv_tick_get();
}

static bool timer24_passed(void) {
    uint32_t now = cat_now_ms();
    return (now - g_cat.timer24_last_reset_ms) > TIMER24_MS;
}

static void reset_timer24(void) {
    g_cat.timer24_last_reset_ms = cat_now_ms();
}

/* ========= PLAY ANIMATION GENÉRICO ========= */

static void play_anim_frames(lv_obj_t *obj,
                             const void *frames[],
                             uint16_t frame_count,
                             uint32_t duration,
                             bool repeat_inf)
{
    lv_animimg_set_src(obj, (const void **)frames, frame_count);
    lv_animimg_set_duration(obj, duration);
    lv_animimg_set_repeat_count(obj, repeat_inf ? LV_ANIM_REPEAT_INFINITE : 1);
    lv_animimg_start(obj);
}

/* ========= ANIMACIONES DE ESTADO ========= */

static void play_animation_happy_idle(void) {
    play_anim_frames(g_cat.anim_obj,
                     anim_happy_frames,
                     anim_happy_frame_count,
                     anim_happy_duration,
                     true);
}

static void play_animation_unhappy_food(void) {
    play_anim_frames(g_cat.anim_obj,
                     anim_hungry_frames,
                     anim_hungry_frame_count,
                     anim_hungry_duration,
                     true);
}

static void play_animation_unhappy_playtime(void) {
    play_anim_frames(g_cat.anim_obj,
                     anim_bored_frames,
                     anim_bored_frame_count,
                     anim_bored_duration,
                     true);
}

static void play_animation_unhappy_affection(void) {
    play_anim_frames(g_cat.anim_obj,
                     anim_lonely_frames,
                     anim_lonely_frame_count,
                     anim_lonely_duration,
                     true);
}

static void play_animation_action_food(void) {
    play_anim_frames(g_cat.anim_obj,
                     anim_action_food_frames,
                     anim_action_food_frame_count,
                     anim_action_food_duration,
                     false);
}

static void play_animation_action_play(void) {
    play_anim_frames(g_cat.anim_obj,
                     anim_action_play_frames,
                     anim_action_play_frame_count,
                     anim_action_play_duration,
                     false);
}

static void play_animation_action_affection(void) {
    play_anim_frames(g_cat.anim_obj,
                     anim_action_affection_frames,
                     anim_action_affection_frame_count,
                     anim_action_affection_duration,
                     false);
}

static void play_animation_transition_skater(void) {
    play_anim_frames(g_cat.anim_obj,
                     anim_transition_skater_frames,
                     anim_transition_skater_frame_count,
                     anim_transition_skater_duration,
                     false);
}

static void play_animation_transition_streamer(void) {
    play_anim_frames(g_cat.anim_obj,
                     anim_transition_streamer_frames,
                     anim_transition_streamer_frame_count,
                     anim_transition_streamer_duration,
                     false);
}

static void play_animation_transition_japan(void) {
    play_anim_frames(g_cat.anim_obj,
                     anim_transition_japan_frames,
                     anim_transition_japan_frame_count,
                     anim_transition_japan_duration,
                     false);
}

static void play_animation_transition_final(void) {
    play_anim_frames(g_cat.anim_obj,
                     anim_transition_final_frames,
                     anim_transition_final_frame_count,
                     anim_transition_final_duration,
                     false);
}

static void play_animation_boot_logo(void) {
    play_anim_frames(g_cat.anim_obj,
                     anim_boot_frames,
                     anim_boot_frame_count,
                     anim_boot_duration,
                     false);
}

/* ========= LÓGICA DE TRANSICIÓN SEGÚN UNHAPPY_COUNTER ========= */

static void apply_transition_for_counter(void) {
    switch (g_cat.UNHAPPY_COUNTER) {
        case 3:
            g_cat.CAT_STAGE = CAT_STAGE_SKATER;
            g_cat.CAT_STATUS = CAT_STATUS_HAPPY;
            reset_timer24();
            play_animation_transition_skater();
            break;

        case 6:
            g_cat.CAT_STAGE = CAT_STAGE_STREAMER;
            g_cat.CAT_STATUS = CAT_STATUS_HAPPY;
            reset_timer24();
            play_animation_transition_streamer();
            break;

        case 9:
            g_cat.CAT_STAGE = CAT_STAGE_JAPAN;
            g_cat.CAT_STATUS = CAT_STATUS_HAPPY;
            reset_timer24();
            play_animation_transition_japan();
            break;

        case 12:
            g_cat.CAT_STAGE = CAT_STAGE_NORWAY;
            g_cat.CAT_STATUS = CAT_STATUS_HAPPY;
            g_cat.FLOW_COMPLETED = true;
            reset_timer24();
            play_animation_transition_final();
            break;

        default:
            break;
    }
}

/* ========= MOSTRAR ANIMACIÓN SEGÚN CAT_STATUS ========= */

static void show_current_cat_animation(void) {
    switch (g_cat.CAT_STATUS) {
        case CAT_STATUS_HAPPY:
            play_animation_happy_idle();
            break;

        case CAT_STATUS_UNHAPPY_FOOD:
            play_animation_unhappy_food();
            break;

        case CAT_STATUS_UNHAPPY_PLAYTIME:
            play_animation_unhappy_playtime();
            break;

        case CAT_STATUS_UNHAPPY_AFFECTION:
            play_animation_unhappy_affection();
            break;
    }
}

/* ========= ACCIÓN CORRECTA (VUELVE A HAPPY) ========= */

static void correct_action(void) {
    g_cat.CAT_STATUS = CAT_STATUS_HAPPY;
    reset_timer24();
    play_animation_happy_idle();
    g_cat.SCREEN_ON = false;
    // Aquí podrías apagar físicamente el backlight si quieres
}

/* ========= FLOW DE ENCENDIDO DE PANTALLA ========= */

static void on_wakeup_event(void) {
    g_cat.SCREEN_ON = true;

    if (timer24_passed()) {
        // Flow A
        if (g_cat.UNHAPPY_COUNTER != 3 &&
            g_cat.UNHAPPY_COUNTER != 6 &&
            g_cat.UNHAPPY_COUNTER != 9 &&
            g_cat.UNHAPPY_COUNTER != 12) {

            if (g_cat.CAT_STATUS == CAT_STATUS_HAPPY) {
                // Escoger UNHAPPY aleatorio de los 3
                uint32_t r = lv_rand(0, 2);
                if (r == 0) g_cat.CAT_STATUS = CAT_STATUS_UNHAPPY_FOOD;
                if (r == 1) g_cat.CAT_STATUS = CAT_STATUS_UNHAPPY_PLAYTIME;
                if (r == 2) g_cat.CAT_STATUS = CAT_STATUS_UNHAPPY_AFFECTION;

                g_cat.UNHAPPY_COUNTER += 1;
                apply_transition_for_counter();
            }
            // Si ya estaba unhappy, no cambiamos el estado
        }
    }
    // Si NO han pasado 24h, saltamos directamente al final del flow A

    show_current_cat_animation();
}

/* ========= API PÚBLICA PARA SHORT PRESS (1, 2, 3 clicks) ========= */

typedef enum {
    CAT_ACTION_FOOD = 0,
    CAT_ACTION_PLAYTIME,
    CAT_ACTION_AFFECTION
} cat_action_t;

static void handle_user_action(cat_action_t action) {
    if (!g_cat.SCREEN_ON) {
        // Si la pantalla está apagada y hay un click, es un wakeup
        on_wakeup_event();
        return;
    }

    // Mostrar animación de acción
    switch (action) {
        case CAT_ACTION_FOOD:
            play_animation_action_food();
            break;
        case CAT_ACTION_PLAYTIME:
            play_animation_action_play();
            break;
        case CAT_ACTION_AFFECTION:
            play_animation_action_affection();
            break;
    }

    if (g_cat.CAT_STATUS != CAT_STATUS_HAPPY) {
        // Si está unhappy, comprobar si la acción era la necesaria
        if (g_cat.CAT_STATUS == CAT_STATUS_UNHAPPY_FOOD &&
            action == CAT_ACTION_FOOD) {
            correct_action();
            return;
        }

        if (g_cat.CAT_STATUS == CAT_STATUS_UNHAPPY_PLAYTIME &&
            action == CAT_ACTION_PLAYTIME) {
            correct_action();
            return;
        }

        if (g_cat.CAT_STATUS == CAT_STATUS_UNHAPPY_AFFECTION &&
            action == CAT_ACTION_AFFECTION) {
            correct_action();
            return;
        }

        // Si no era la acción correcta, permanece unhappy
        return;
    }

    // Si ya está HAPPY, la acción solo reproduce animación, no cambia estado
    // TIMER_24 no se resetea aquí, sigue contando
}

/* Función que llamas desde tu HAL cuando detectas nº de pulsos cortos: */
void cat_engine_on_short_press_count(uint8_t count) {
    if (count == 1) {
        handle_user_action(CAT_ACTION_FOOD);
    } else if (count == 2) {
        handle_user_action(CAT_ACTION_PLAYTIME);
    } else if (count == 3) {
        handle_user_action(CAT_ACTION_AFFECTION);
    }
}

/* ========= API PÚBLICA PARA LONG PRESS ========= */

void cat_engine_on_long_press(uint32_t duration_ms) {
    if (duration_ms >= LONG_PRESS_RESET_MS) {
        /* Reset total */
        g_cat.CAT_STATUS = CAT_STATUS_HAPPY;
        g_cat.CAT_STAGE  = CAT_STAGE_NORWAY;
        g_cat.UNHAPPY_COUNTER = 0;
        g_cat.FLOW_COMPLETED  = false;
        reset_timer24();
        g_cat.SCREEN_ON = false;
        play_animation_boot_logo();
        return;
    }

    if (duration_ms >= LONG_PRESS_EVOLVE_MS) {
        if (g_cat.FLOW_COMPLETED) {
            // Evolución manual de stage
            g_cat.CAT_STAGE = (cat_stage_t)((g_cat.CAT_STAGE + 1) % 4);
            g_cat.SCREEN_ON = true;
            show_current_cat_animation();
        }
    }
}

/* ========= TIMER PRINCIPAL (LÓGICA SUAVE) ========= */

static void cat_logic_timer_cb(lv_timer_t *t) {
    LV_UNUSED(t);
    // Aquí podrías añadir lógica adicional si quieres,
    // ahora mismo la mayor parte va por eventos de botón y TIMER_24
}

/* ========= INIT PÚBLICO ========= */

void cat_engine_init(lv_obj_t *parent) {
    memset(&g_cat, 0, sizeof(g_cat));

    g_cat.CAT_STATUS = CAT_STATUS_HAPPY;
    g_cat.CAT_STAGE  = CAT_STAGE_NORWAY;
    g_cat.UNHAPPY_COUNTER = 0;
    g_cat.FLOW_COMPLETED  = false;
    g_cat.SCREEN_ON       = false;

    reset_timer24();

    g_cat.anim_obj = lv_animimg_create(parent);
    lv_obj_center(g_cat.anim_obj);

    play_animation_boot_logo();

    g_cat.logic_timer = lv_timer_create(cat_logic_timer_cb, 200, NULL);
}
