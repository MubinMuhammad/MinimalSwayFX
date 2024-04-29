#ifndef _TEXTS_H_
#define _TEXTS_H_

const char *before_header = 
"Before installation";

const char *sway_ques_header =
"Which Window Manager are you using?";

const char *setting_wallpaper_header =
"Setting Wallpaper";

const char *window_gap_header = 
"How much the window gap should be?";

const char *window_border_header =
"How much the border should be?";

const char *bar_type_header = 
"Which status bar would you like to use?";

const char *bar_pos_header =
"Where the status bar should be?";

const char *before_desc =
"\033[3;4;33mNote\033[0;0m: Make sure you have installed the required\n"
"dependencies before you begin the installation process.\n"
"If you are not sure, checkout the dependencies list in\n"
"MinimalSwayFX at Github!\n\n"

"I have read the statement above [y/n]: ";

const char *setting_wallpaper_desc =
"If you have a specific wallpaper to set,\n"
"make sure to provide the path starting from\n"
"$HOME otherwise, if you would like a solid\n"
"background, provide the solid color\n"
"in #RRGGBB hex format.\n\n"

"Input: ";

const char *window_gap_desc =
"This is the gap when you put your windows\n"
"in tiling mode. The amount you choose is\n"
"will going to have an effect on the gap\n"
"between 2 or more windows in tiling.\n\n";

const char *window_border_desc =
"This is going to be the border of each\n"
"window.\n\n";

const char *bar_type_desc = 
"The bar preference depends the on which\n"
"bar you have installed from the dependencies.\n"
"So, choose the bar you have installed.\n\n";

const char *bar_pos_desc =
"This will be the placement of the bar\n"
"Currently, It only supports top & bottom\n"
"I shall add left & right support soon.\n\n";

const char *sway_ques_options =
"a. Sway\n"
"b. SwayFX\n\n"

"Input [a <-> b]: ";

const char *bar_gap_options =
"a. None.\n"
"b. Low.\n"
"c. Medium.\n"
"d. High.\n\n"

"Input [a <-> d]: ";

const char *window_border_options =
"a. None.\n"
"b. Thin.\n"
"c. Medium.\n"
"d. Thick.\n\n"

"Input [a <-> d]: ";

const char *bar_type_options =
"a. Waybar.\n"
"b. i3status-rs.\n\n"

"Input [a <-> b]: ";

const char *bar_pos_options =
"a. Top.\n"
"b. Bottom.\n\n"

"Input [a <-> b]: ";

#endif
