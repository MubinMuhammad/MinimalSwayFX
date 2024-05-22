#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

#include "../config.hpp"
#include "utils.hpp"
#include "colors.hpp"

#define msfxLevelToVal(level, mn, md, mx) (\
  (level == low ? mn : \
  (level == medium ? md : \
  (level == high ? mx : 0))))

void formatWord(std::string &s, std::vector<std::pair<std::string, std::string>> &options) {
  if (s.size() < 8 || s.substr(0, 8) != "msfxSet(") {
    return;
  }

  std::string option_name = "";
  std::string extension = "";

  int f = 0;
  for (int i = 8; i < s.size(); i++) {
    if (s[i] == ')') {
      f = 1;
      continue;
    }

    (!f ? option_name : extension).push_back(s[i]);
  }

  f = 0;
  for (std::pair<std::string, std::string> &option : options) {
    if (option_name == option.first) {
      option_name = option.second;
      f = 1;
      break;
    }
  }

  if (!f) {
    std::cout 
      << "\033[1;31minvalid option\033[0m" << " `" << option_name << "`:" << '\n'
      << "  |\n  | " << s << "\n  |         ";

    for (int i = 0; i < option_name.size(); i++) std::cout << "~";
    std::cout << '\n';

    std::cout << "\033[1;33mkeeping the word as is!\033[0m\n";
    return;
  }

  option_name += extension;
  s = option_name;
}

std::string getWallpaperMode(std::string wallpaper) {
  if (wallpaper.size() != 7)
    return "fill";

  if (wallpaper[0] != '#')
    return "fill";

  for (int i = 1; i < 7; i++) {
    if (
      (wallpaper[i] >= '\0' && wallpaper[i] < '0' ) ||
      (wallpaper[i] >  '9'  && wallpaper[i] < 'a' ) ||
      (wallpaper[i] >  'f'  && wallpaper[i] < 'A' ) ||
      (wallpaper[i] >  'F'  && wallpaper[i] <= 127) 
    )
      return "fill";
  }

  return "solid_color";
}

int main() {
  system("clear");

  const std::vector<std::string> configs = {
    "sway/config",

    /*
     * below is commented
     * for testing purposes.
     * */
    // "waybar/config.jsonc",
    // "waybar/style.css",
    // "i3status/config.toml",
    // "tofi/config",
    // "mako/config",
    // "alacritty/alacritty.toml",
    // "neofetch/config.conf",
    // "fish/config.fish"
  };

  std::vector<std::pair<std::string, std::string>> options;

  options.push_back({"window_manager", msfx_window_manager});

  std::vector<std::string> color_names = {
    "bg", "fg", "gray", "red", "green", "yellow",
    "orange", "blue", "aqua", "purple"
  };

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      options.push_back({
        "color_" + color_names[i] + std::to_string(j + 1),
        msfx_theme[4 * i + j]
      });
    }
  }

  for (int i = 2; i < color_names.size(); i++) {
    for (int j = 0; j < 2; j++) {
      options.push_back({
        "color_" + color_names[i] + std::to_string(j + 1),
        msfx_theme[(2 * i + 4) + j]
      });
    }
  }

  float msfx_tansparancy_val = msfxLevelToVal(msfx_transparancy, 0.3f, 0.5f, 0.7f); 
  float msfx_tansparancy_val = msfxLevelToVal(msfx_transparancy, 0.3f, 0.5f, 0.7f); 
  float msfx_tansparancy_val = msfxLevelToVal(msfx_transparancy, 0.3f, 0.5f, 0.7f); 
  float msfx_tansparancy_val = msfxLevelToVal(msfx_transparancy, 0.3f, 0.5f, 0.7f); 
  float msfx_tansparancy_val = msfxLevelToVal(msfx_transparancy, 0.3f, 0.5f, 0.7f); 

  options.push_back({"wallpaper", msfx_wallpaper});
  options.push_back({"wallpaper_mode", getWallpaperMode(msfx_wallpaper)});
  options.push_back({"bar_cmd", msfx_bar == "waybar" ? "waybar" : "swaybar"});
  options.push_back({"bar_layercmd", msfx_bar == "waybar" ? "waybar" : "panel"});
  options.push_back({"tansparancy", msfx_window_manager});
  options.push_back({"window_manager", msfx_window_manager});
  options.push_back({"window_manager", msfx_window_manager});

  for (int i = 0; i < configs.size(); i++) {
    std::string in_config_path = "config/" + configs[i];
    /*
     * below is commented
     * for testing purposes.
     * */
    // std::string out_config_path(getenv("HOME"));
    // out_config_path += "/.config/" + configs[i];
    std::string out_config_path = "./wconfig/" + configs[i];

    std::ifstream input_file;
    std::ofstream output_file;
    input_file.open(in_config_path);
    output_file.open(out_config_path);

    if (input_file.is_open()) {
      std::string line = "";

      while (std::getline(input_file, line)) {
        std::istringstream line_stream(line);
        std::string word = "";
        std::string out_line = "";

        while (line_stream >> word) {
          formatWord(word, options);
          out_line += word + ' ';
        }

        output_file << out_line << '\n';
      }

      input_file.close();
      output_file.close();
    }
    else {
      std::cout << "failed to read " << in_config_path  << "!" << '\n';
    }
  }


  return 0;
}
