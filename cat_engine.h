#ifndef CAT_ENGINE_H
#define CAT_ENGINE_H

#include "lvgl.h"
#include <stdbool.h>

// Estados públicos (para acceso externo si necesitas)
typedef enum {
    CAT_HAPPY,
    CAT_UNHAPPY_FOOD,
    CAT_UNHAPPY_PLAYTIME,
    CAT_UNHAPPY_AFFECTION
} cat_status_t;

typedef enum {
    STAGE_NORWAY = 0,
    STAGE_SKATER = 1,
    STAGE_STREAMER = 2,
    STAGE_JAPAN = 3
} cat_stage_t;

// Funciones públicas
void cat_engine_init(void);
void cat_engine_button_pressed(bool is_pressed);
void cat_engine_update(void);
cat_status_t cat_engine_get_status(void);
cat_stage_t cat_engine_get_stage(void);

#endif // CAT_ENGINE_H