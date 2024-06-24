#include <iostream>
#include <algorithm>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include <cstdlib>
#include <cstdint>
#include <cstring>

#include "../config.hpp"
#include "utils.hpp"
#include "colors.hpp"

#define msfxLevelToVal(level, mn, md, mx) \
  ((level == low ? mn : \
  (level == medium ? md : \
  (level == high ? mx : 0))))

void formatWord(std::string &s, std::vector<std::pair<std::string, std::string>> &options) {
  if (s.size() < 8) {
    return;
  }

  std::string option_name = "";
  std::string prefix = "";
  std::string suffix = "";

  int f = 0;

  for (int i = 0; i < s.size() - 7; i++) {
    std::string tmp = s.substr(i, 8);

    if (tmp == "msfxSet(") {
      prefix = s.substr(0, i);
      option_name = s.substr(i + 8, s.size());
      f = 1;
      break;
    }
  }

  if (!f)
    return;

  f = option_name.size() - 1;
  while (f > 0) {
    if (option_name[f] == ')')
      break;
    else
      suffix.push_back(option_name[f]);

    option_name.pop_back();
    f--;
  }
  option_name.pop_back();
  std::reverse(suffix.begin(), suffix.end());

  if (!f)
    return;

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

    for (int i = 0; i < option_name.size(); i++) 
      std::cout << "~";

    std::cout << '\n';

    std::cout << "\033[1;33mkeeping the word as is!\033[0m\n";
    return;
  }

  option_name.insert(0, prefix);
  option_name += suffix;
  s = option_name;
}

bool isStringHex(std::string s) {
  if (s.size() != 7 || s[0] != '#')
    return 0;

  for (int i = 1; i < 7; i++) {
    if (!((s[i] >= '0' && s[i] <= '9') ||
          (s[i] >= 'A' && s[i] <= 'F') ||
          (s[i] >= 'a' && s[i] <= 'f')))
      return 0;
  }

  return 1;
}

int hexCharToNum(char c) {
  int k = c;
  
  if (c >= '0' && c <= '9') k -= '0';
  else if (c >= 'a' && c <= 'f') k -= 'a' - 10;
  else if (c >= 'A' && c <= 'F') k -= 'A' - 10;

  return k;
}

std::string getWallpaperMode(std::string wallpaper) {
  return isStringHex(wallpaper) ? "solid_color" : "fill";
}

std::string hexToRGBA(std::string s, float alpha) {
  if (!isStringHex(s))
    return "INVALID_HEX";

  uint8_t r = hexCharToNum(s[1]) * 16 + hexCharToNum(s[2]);
  uint8_t g = hexCharToNum(s[3]) * 16 + hexCharToNum(s[4]);
  uint8_t b = hexCharToNum(s[5]) * 16 + hexCharToNum(s[6]);

  return 
    "rgba(" +
    std::to_string(r) + ", " +
    std::to_string(g) + ", " +
    std::to_string(b) + ", " +
    std::to_string(alpha) + ")";
}

int main(int argc, char *argv[]) {
  const std::vector<std::pair<std::string, std::string>> configs = {
    {"sway", "config"},
    {"waybar", "config.jsonc"},
    {"waybar", "style.css"},
    {"i3status", "config.toml"},
    {"tofi", "config"},
    {"mako", "config"},
    {"alacritty", "alacritty.toml"},
    {"fish", "config.fish"},
    {"fish", "ascii.sh"},
    {"fish/functions", "fish_prompt.fish"}
  };

  int msfx_border_val = msfxLevelToVal(msfx_border, 2, 4, 8);
  int msfx_gap_val = msfxLevelToVal(msfx_gap, 4, 8, 12);
  float msfx_transparency_val = msfxLevelToVal(msfx_transparency, 0.1f, 0.3f, 0.5f); 
  int msfx_blur_val = msfxLevelToVal(msfx_blur, 3, 5, 7); 
  int msfx_corner_radius_val = msfxLevelToVal(msfx_corner_radius, 4, 8, 16);
  std::string msfx_bar_pos_val = msfx_bar_pos == bottom ? "bottom" : "top";

  std::vector<std::pair<std::string, std::string>> options;

  std::vector<std::string> color_names = {
    "bg", "fg", "gray", "red", "green", "yellow",
    "orange", "blue", "aqua", "purple"
  };

  char tmp_char_arr[128];
  std::string tmp_str;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      options.push_back({ "color_" + color_names[i] + std::to_string(j + 1), msfx_theme[4 * i + j] });

      options.push_back({
        "color_" + color_names[i] + std::to_string(j + 1) + "_rgba",
        hexToRGBA(msfx_theme[4 * i + j], (1.0f - msfx_transparency_val))
      });

      snprintf(tmp_char_arr, 128, "%.2x", (int)(255 * (1.0f - msfx_transparency_val)));
      tmp_str = msfx_theme[4 * i + j] + tmp_char_arr;
      options.push_back({ "color_" + color_names[i] + std::to_string(j + 1) + "_a", tmp_str });
      memset(tmp_char_arr, '\0', sizeof(tmp_char_arr));
    }
  }

  for (int i = 2; i < color_names.size(); i++) {
    for (int j = 0; j < 2; j++) {
      options.push_back({ "color_" + color_names[i] + std::to_string(j + 1), msfx_theme[(2 * i + 4) + j] });

      options.push_back({
        "color_" + color_names[i] + std::to_string(j + 1) + "_rgba",
        hexToRGBA(msfx_theme[2 * i + 4 + j], (1.0f - msfx_transparency_val))
      });

      snprintf(tmp_char_arr, 128, "%.2x", (int)(255 * (1.0f - msfx_transparency_val)));
      tmp_str = msfx_theme[2 * i + 4 + j] + tmp_char_arr;
      options.push_back({ "color_" + color_names[i] + std::to_string(j + 1) + "_a", tmp_str });
      memset(tmp_char_arr, '\0', sizeof(tmp_char_arr));
    }
  }

  options.push_back({"window_manager", msfx_window_manager});
  options.push_back({"if_swayfx", msfx_window_manager == "swayfx" ? "" : "#"});
  options.push_back({"if_title_bar", msfx_title_bar ? "#" : ""});
  options.push_back({"font", msfx_font});
  options.push_back({"font_style", msfx_font_style});
  options.push_back({"font_size", std::to_string(msfx_font_size)});
  options.push_back({"waybar_font_size", std::to_string(msfx_font_size + 2)});
  options.push_back({"wallpaper", msfx_wallpaper});
  options.push_back({"wallpaper_mode", getWallpaperMode(msfx_wallpaper)});
  options.push_back({"border", std::to_string(msfx_border_val)});
  options.push_back({"gap", std::to_string(msfx_gap_val)});
  options.push_back({"if_swaybar", msfx_bar == "i3status" ? "" : "#"});
  options.push_back({"swaybar_height", std::to_string(msfx_font_size + 20)});
  options.push_back({"bar_gap_right", msfx_bar_pos_val == "left" ? "0" : std::to_string(msfx_gap_val * 2)});
  options.push_back({"bar_gap_left", msfx_bar_pos_val == "right" ? "0" : std::to_string(msfx_gap_val * 2)});
  options.push_back({"bar_gap_top", msfx_bar_pos_val == "bottom" ? "0" : std::to_string(msfx_gap_val * 2)});
  options.push_back({"bar_gap_bottom", msfx_bar_pos_val == "top" ? "0" : std::to_string(msfx_gap_val * 2)});
  options.push_back({"bar_cmd", msfx_bar == "waybar" ? "waybar" : "swaybar"});
  options.push_back({"bar_layercmd", msfx_bar == "waybar" ? "waybar" : "panel"});
  options.push_back({"bar_position", msfx_bar_pos_val});
  options.push_back({"transparency", std::to_string(msfx_transparency_val)});
  options.push_back({"transparency_invert", std::to_string(1.0f - msfx_transparency_val)});
  options.push_back({"blur", std::to_string(msfx_blur_val)});
  options.push_back({"is_blur", msfx_blur_val != 0 && msfx_transparency_val != 0.0f ? "enable" : "disable"});
  options.push_back({"is_blur_xray", msfx_blur_xray == true ? "enable" : "disable"});
  options.push_back({"is_shadow", msfx_shadow == false ? "disable" : "enable"});
  options.push_back({"corner_radius", std::to_string(msfx_corner_radius_val)});

  for (int i = 0; i < configs.size(); i++) {
    std::string in_config_path = "config/" + configs[i].first + "/" + configs[i].second;
    std::string out_config_path(getenv("HOME"));
    out_config_path += "/.config/" + configs[i].first;

    if (std::filesystem::is_directory(out_config_path)) {
      tmp_str = configs[i].first;
      bool f = 0;

      for (int j = 0; j < configs.size(); j++) {
        if (tmp_str == configs[j].first && i != j) {
          f = 1;
          break;
        }
      }

      if (!f) {
        std::filesystem::remove_all(out_config_path);
        std::filesystem::create_directory(out_config_path);
      }
    }
    else {
      std::filesystem::create_directory(out_config_path);
    }

    out_config_path += "/" + configs[i].second;

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
        if (out_line.size() > 0) out_line.pop_back();

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
