/**
 * @file display_knob_katson_gen.h
 */

#ifndef DISPLAY_KNOB_KATSON_GEN_H
#define DISPLAY_KNOB_KATSON_GEN_H

#ifndef UI_SUBJECT_STRING_LENGTH
#define UI_SUBJECT_STRING_LENGTH 256
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

/*********************
 *      DEFINES
 *********************/

#define TIMER_24H_SECONDS 86400

#define TIMER_TEST_SECONDS 24

#define BTN_SHORT_PRESS_MS 300

#define BTN_LONG_PRESS_3S_MS 3000

#define BTN_LONG_PRESS_15S_MS 15000

#define MILESTONE_SKATER 3

#define MILESTONE_STREAMER 6

#define MILESTONE_JAPAN 9

#define MILESTONE_NORWAY 12

/**********************
 *      TYPEDEFS
 **********************/

typedef enum {
    CAT_STATUS_T_CAT_HAPPY = 0,
    CAT_STATUS_T_CAT_UNHAPPY_FOOD = 1,
    CAT_STATUS_T_CAT_UNHAPPY_PLAYTIME = 2,
    CAT_STATUS_T_CAT_UNHAPPY_AFFECTION = 3
}cat_status_t_t;

typedef enum {
    CAT_STAGE_T_STAGE_NORWAY = 0,
    CAT_STAGE_T_STAGE_SKATER = 1,
    CAT_STAGE_T_STAGE_STREAMER = 2,
    CAT_STAGE_T_STAGE_JAPAN = 3
}cat_stage_t_t;

typedef enum {
    ANIMATION_TYPE_T_ANIM_IDLE_HAPPY = 0,
    ANIMATION_TYPE_T_ANIM_UNHAPPY_FOOD = 1,
    ANIMATION_TYPE_T_ANIM_UNHAPPY_PLAYTIME = 2,
    ANIMATION_TYPE_T_ANIM_UNHAPPY_AFFECTION = 3,
    ANIMATION_TYPE_T_ANIM_ACTION_FOOD = 4,
    ANIMATION_TYPE_T_ANIM_ACTION_PLAYTIME = 5,
    ANIMATION_TYPE_T_ANIM_ACTION_AFFECTION = 6,
    ANIMATION_TYPE_T_ANIM_TRANSITION_SKATER = 7,
    ANIMATION_TYPE_T_ANIM_TRANSITION_STREAMER = 8,
    ANIMATION_TYPE_T_ANIM_TRANSITION_JAPAN = 9,
    ANIMATION_TYPE_T_ANIM_TRANSITION_NORWAY = 10,
    ANIMATION_TYPE_T_ANIM_BOOT = 11
}animation_type_t_t;

/**********************
 * GLOBAL VARIABLES
 **********************/

/*-------------------
 * Permanent screens
 *------------------*/

/*----------------
 * Global styles
 *----------------*/

/*----------------
 * Fonts
 *----------------*/

/*----------------
 * Images
 *----------------*/

extern const void * anim_idle_happy;
extern const void * anim_unhappy_food;
extern const void * anim_unhappy_playtime;
extern const void * anim_unhappy_affection;
extern const void * anim_action_food;
extern const void * anim_action_playtime;
extern const void * anim_action_affection;
extern const void * anim_transition_skater;
extern const void * anim_transition_streamer;
extern const void * anim_transition_japan;
extern const void * anim_transition_norway;
extern const void * anim_boot;
extern const void * frame_0001;

/*----------------
 * Subjects
 *----------------*/

extern lv_subject_t g_unhappy_counter;
extern lv_subject_t g_cat_status;
extern lv_subject_t g_cat_stage;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*----------------
 * Event Callbacks
 *----------------*/

/**
 * Initialize the component library
 */

void display_knob_katson_init_gen(const char * asset_path);

/**********************
 *      MACROS
 **********************/

/**********************
 *   POST INCLUDES
 **********************/

/*Include all the widget and components of this library*/
#include "screens/ui_ScreenMain_gen.h"

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*DISPLAY_KNOB_KATSON_GEN_H*/