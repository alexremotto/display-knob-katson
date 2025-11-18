#include "display_knob_katson.h"

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

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void display_knob_katson_init(const char * asset_path)
{
    /* Inicializa todo lo generado por LVGL Pro / SquareLine */
    display_knob_katson_init_gen(asset_path);

    /* Obtén el objeto raíz donde quieres poner el Tamagotchi */
   /* lv_obj_t * root = get_root_screen();
*/
    /* Inicializa el motor del gato sobre ese objeto */
   /* if (root != NULL) {
        cat_engine_init(root);
    }

    /* Aquí puedes añadir más código custom si hace falta */
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * @brief Devuelve el objeto LVGL donde se pinta el Tamagotchi.
 *
 * NOTA: Aquí tienes que usar la función/variable que te genere LVGL Pro.
 * Ejemplos típicos:
 *   - extern lv_obj_t * ui_ScreenMain;
 *   - extern lv_obj_t * ui_Screen1;
 *   - o una función tipo display_knob_katson_get_main_screen();
 */

