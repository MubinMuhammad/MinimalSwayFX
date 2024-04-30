/*
 * Do NOT edit lines starting with
 * #ifndef, #include, #endif.
 *
 * Just focus on changing #define lines,
 * exeption to this line is `#define _CONFIG_H_`
 * make sure to not change this line.
 * */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "src/installer/types.h"

/*
 * It will highly depend on the dependencies list.
 * If you have installed sway and not swayfx, choose,
 * SWAY otherwise choose SWAYFX.
 *
 * Available options: SWAY, SWAYFX
 * */
#define WINDOW_MANAGER SWAYFX

/*
 * The wallpaper can be the path
 * to a wallpaper or a #RRGGBB hex format
 * for solid colors. Make sure to put
 * "" around the your choice.
 * */
#define WALLPAPER "#1d2021"

/*
 * This will determine the gap between
 * windows in tiling mode. 
 *
 * Available options: NONE, LOW, MEDIUM, HIGH
 * */
#define WINDOW_GAP MEDIUM

/*
 * This will determine the border of windows
 * and the bar (waybar). 
 * 
 * Available options: NONE, THIN, MEDIUM, THICK
 * */
#define WINDOW_BORDER THIN

/*
 * This will be the bar you are going to use
 * it does depend on the dependencies. e.g. if you have
 * installed waybar you can't choose I3_STATUS here.
 *
 * Available options: WAYBAR, I3_STATUS
 * */
#define BAR_TYPE WAYBAR

/*
 * This will determine the bar placement.
 * Currently only supports top & bottom.
 * Though left & right shall come soon.
 *
 * Available options: TOP, BOTTOM
 * */
#define BAR_POSITION TOP

/*
 * Determines how transparent an winodow should
 * be (if the has the feature). If you want to
 * apply blur, Make sure to enable it to some
 * extent (don't set it to NONE).
 *
 * Available options: NONE, LOW, MEDIUM, HIGH
 * */
#define SWAYFX_TRANSPARANCY LOW

/*
 * If enabled, will give the blur effect to
 * transparent windows. Make sure the SWAYFX_TRANSPARANCY
 * is set. Otherwise, this effect will be ignored.
 *
 * Available options: NONE, LOW, MEDIUM, HIGH
 * */
#define SWAYFX_BLUR MEDIUM

/*
 * If enabled, windows will have shadows.
 * 
 * Available options: TRUE, FALSE
 * */
#define SWAYFX_SHADOW FALSE

/*
 * If enabled, windows & the bar will have
 * rounded corners.
 *
 * Available options: NONE, LOW, MEDIUM, HIGH
 * */
#define SWAYFX_CORNER_RADIUS MEDIUM

/*
 * If enabled, when a winodw goes unfocused,
 * the window will be dim.
 *
 * Available options: NONE, LOW, MEDIUM, HIGH
 * */
#define SWAYFX_INACTIVE_DIM LOW

#endif