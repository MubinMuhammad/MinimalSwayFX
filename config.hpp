// ███╗   ███╗██╗███╗   ██╗██╗███╗   ███╗ █████╗ ██╗
// ████╗ ████║██║████╗  ██║██║████╗ ████║██╔══██╗██║
// ██╔████╔██║██║██╔██╗ ██║██║██╔████╔██║███████║██║
// ██║╚██╔╝██║██║██║╚██╗██║██║██║╚██╔╝██║██╔══██║██║
// ██║ ╚═╝ ██║██║██║ ╚████║██║██║ ╚═╝ ██║██║  ██║███████╗
// ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝
// 
// ███████╗██╗    ██╗ █████╗ ██╗   ██╗███████╗██╗  ██╗
// ██╔════╝██║    ██║██╔══██╗╚██╗ ██╔╝██╔════╝╚██╗██╔╝
// ███████╗██║ █╗ ██║███████║ ╚████╔╝ █████╗   ╚███╔╝
// ╚════██║██║███╗██║██╔══██║  ╚██╔╝  ██╔══╝   ██╔██╗
// ███████║╚███╔███╔╝██║  ██║   ██║   ██║     ██╔╝ ██╗
// ╚══════╝ ╚══╝╚══╝ ╚═╝  ╚═╝   ╚═╝   ╚═╝     ╚═╝  ╚═╝

/*
 * Only change the config meaning
 * change the options after `=`.
 *
 * Don't change anything before
 * `=` as they mean the data types.
 *
 * Don't remove the msfx_ prefix of
 * any variables otherwise you have
 * to remove it else where as well.
 *
 * If you're using Nvim with C++ LSP
 * it may show ODR Violation warning.
 * It's not that big of a concern so,
 * just ignore it.
 * */

#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

/////////////////DON'T EDIT/////////////////////
#include <string>                  /////////////
#include <vector>                  /////////////
#include "installerSrc/utils.hpp"  /////////////
#include "installerSrc/colors.hpp" /////////////
////////////////////////////////////////////////

/*
 * The window manager you are using.
 * it must be installed on your system.
 * so, make sure you have read the
 * dependency list!
 *
 * Available options: ["sway", "swayfx"]
 * */
const std::string msfx_window_manager = "swayfx";

/*
 * the name of font that should be used
 * through out the system. Better to
 * choose a nerd font.
 * */
const std::string msfx_font = "CaskaydiaCove Nerd Font";

/*
 * choose the font weight for the font.
 * Usually they are ["thin", "regular", "medium", "bold"]
 * */
const std::string msfx_font_style = "bold";

/*
 * the font size to use.
 * normal arithmatic can be applied here.
 * but make sure to not put negative values.
 * */
const unsigned int msfx_font_size = 12;

/*
 * The theme you want to use through-out
 * you're system. It includes, terminal,
 * statusbar, app menu, etc.
 *
 * Available options(for now): [
 *   gruvbox_dark,
 *   gruvbox_material_dark,
 *   nord_dark,
 *   everforest_dark,
 *   everblush_dark,
 *   rosepine_dark
 * ]
 * */
const std::vector<std::string> &msfx_theme = gruvbox_material_dark;

/*
 * The wallpaper you want to use can be
 * mentioned here. It can also be a hex
 * color with format #RRGGBB or any path
 * to a wallpaper you would like to use.
 * 
 * The wallpaper path is relative to
 * "$HOME/.config/sway/"
 *
 * Available options: [#RRGGBB(for solid colors),
 *                     <path_to_wallpaper>]
 * */
const std::string msfx_wallpaper = "$HOME/Pictures/wallpaper2.jpg";

/*
 * The gap between two or more windows.
 * This gap will also be applied to the
 * bar for consistancy.
 *
 * Available options: [none, low, medium, high]
 * */
const msfx_level msfx_gap = low;

/*
 * The thickness of border around windows.
 *
 * Availabl options: [none, low, medium, high]
 * */
const msfx_level msfx_border = low;

/*
 * The bar you would like to choose there
 * are two options "waybar" and "i3status".
 * If you choose either of them, you have
 * to make sure you have installed it on your
 * system. See dependencies on MinimalSwayFX
 * wiki for more info.
 *
 * waybar: waybar is statusbar focusing on visuals
 *         therefore it looks better than i3status
 *         but it also comes at cost in performance.
 *
 * i3status: It doesn't look as fancy as waybar,
 *                but it's faster than waybar.
 *
 * 
 * */
const std::string msfx_bar = "waybar";

/*
 * the bar position for i3status or waybar.
 *
 * Available options: top, bottom 
 *
 * TODO: 
 *   implement right & left
 * */
const msfx_position msfx_bar_pos = top;

/////////////// ONLY FOR SWAYFX USERS ///////////////
/*
 * The transparency you would want for
 * windows that may use it.
 *
 * Available options: [none, low, medium, high]
 * */
const msfx_level msfx_transparency = none;

/*
 * The level of blur for transparent
 * windows that may use it. blur will
 * only work if transparency is NOT set
 * to none.
 *
 * Available options: [none, low, medium, high]
 * */
const msfx_level msfx_blur = none;

/*
 * The option will turn on blur xray,
 * which will show the blur relative to your
 * wallpaper and not what's behind it.
 *
 * Available options: [true, false]
 * */
const bool msfx_blur_xray = false;

/*
 * Enables a nice shadow for windows
 * and the status.
 *
 * Available options: [true, false]
 * */
const bool msfx_shadow = true;

/*
 * Adds corner radius to statusbar &
 * windows.
 *
 * Available options: [none, low, medium, high]
 * */
const msfx_level msfx_corner_radius = medium;

#endif
