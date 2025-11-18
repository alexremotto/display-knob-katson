/**
 * @file display_knob_katson_gen.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "display_knob_katson_gen.h"

#if LV_USE_XML
#endif /* LV_USE_XML */

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/*----------------
 * Translations
 *----------------*/

/**********************
 *  GLOBAL VARIABLES
 **********************/

/*--------------------
 *  Permanent screens
 *-------------------*/

/*----------------
 * Global styles
 *----------------*/

/*----------------
 * Fonts
 *----------------*/

/*----------------
 * Images
 *----------------*/

const void * anim_idle_happy;
const void * anim_unhappy_food;
const void * anim_unhappy_playtime;
const void * anim_unhappy_affection;
const void * anim_action_food;
const void * anim_action_playtime;
const void * anim_action_affection;
const void * anim_transition_skater;
const void * anim_transition_streamer;
const void * anim_transition_japan;
const void * anim_transition_norway;
const void * anim_boot;
const void * frame_0001;

/*----------------
 * Subjects
 *----------------*/

lv_subject_t g_unhappy_counter;
lv_subject_t g_cat_status;
lv_subject_t g_cat_stage;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void display_knob_katson_init_gen(const char * asset_path)
{
    char buf[256];

    /*----------------
     * Global styles
     *----------------*/

    /*----------------
     * Fonts
     *----------------*/


    /*----------------
     * Images
     *----------------*/
    lv_snprintf(buf, 256, "%s%s", asset_path, "assets/anim_idle_happy.png");
    anim_idle_happy = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "assets/anim_unhappy_food.png");
    anim_unhappy_food = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "assets/anim_unhappy_playtime.png");
    anim_unhappy_playtime = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "assets/anim_unhappy_affection.png");
    anim_unhappy_affection = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "assets/anim_action_food.png");
    anim_action_food = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "assets/anim_action_playtime.png");
    anim_action_playtime = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "assets/anim_action_affection.png");
    anim_action_affection = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "assets/anim_transition_skater.png");
    anim_transition_skater = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "assets/anim_transition_streamer.png");
    anim_transition_streamer = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "assets/anim_transition_japan.png");
    anim_transition_japan = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "assets/anim_transition_norway.png");
    anim_transition_norway = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "assets/anim_boot.png");
    anim_boot = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "images/frame_0001.png");
    frame_0001 = lv_strdup(buf);

    /*----------------
     * Subjects
     *----------------*/
    lv_subject_init_int(&g_unhappy_counter, 0);
    lv_subject_init_int(&g_cat_status, 0);
    lv_subject_init_int(&g_cat_stage, 0);

    /*----------------
     * Translations
     *----------------*/

#if LV_USE_XML
    /* Register widgets */

    /* Register fonts */

    /* Register subjects */
    lv_xml_register_subject(NULL, "g_unhappy_counter", &g_unhappy_counter);
    lv_xml_register_subject(NULL, "g_cat_status", &g_cat_status);
    lv_xml_register_subject(NULL, "g_cat_stage", &g_cat_stage);

    /* Register callbacks */
#endif

    /* Register all the global assets so that they won't be created again when globals.xml is parsed.
     * While running in the editor skip this step to update the preview when the XML changes */
#if LV_USE_XML && !defined(LV_EDITOR_PREVIEW)
    /* Register images */
    lv_xml_register_image(NULL, "anim_idle_happy", anim_idle_happy);
    lv_xml_register_image(NULL, "anim_unhappy_food", anim_unhappy_food);
    lv_xml_register_image(NULL, "anim_unhappy_playtime", anim_unhappy_playtime);
    lv_xml_register_image(NULL, "anim_unhappy_affection", anim_unhappy_affection);
    lv_xml_register_image(NULL, "anim_action_food", anim_action_food);
    lv_xml_register_image(NULL, "anim_action_playtime", anim_action_playtime);
    lv_xml_register_image(NULL, "anim_action_affection", anim_action_affection);
    lv_xml_register_image(NULL, "anim_transition_skater", anim_transition_skater);
    lv_xml_register_image(NULL, "anim_transition_streamer", anim_transition_streamer);
    lv_xml_register_image(NULL, "anim_transition_japan", anim_transition_japan);
    lv_xml_register_image(NULL, "anim_transition_norway", anim_transition_norway);
    lv_xml_register_image(NULL, "anim_boot", anim_boot);
    lv_xml_register_image(NULL, "frame_0001", frame_0001);
#endif

#if LV_USE_XML == 0
    /*--------------------
     *  Permanent screens
     *-------------------*/
    /* If XML is enabled it's assumed that the permanent screens are created
     * manaully from XML using lv_xml_create() */
#endif
}

/* Callbacks */

/**********************
 *   STATIC FUNCTIONS
 **********************/