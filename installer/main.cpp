#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> configs = {
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
    // "alacritty/config.toml",
    // "neofetch/config.conf",
    // "fish/config.fish"
  };


  for (int i = 0; i < configs.size(); i++) {
    std::string in_config_path = "config/" + configs[i];
    std::string out_config_path(getenv("HOME"));
    out_config_path += "/.config/" + configs[i];

    std::ifstream input_file;
    std::ofstream output_file;
    input_file.open(in_config_path);
    output_file.open(out_config_path);

    if (input_file.is_open() && output_file.is_open()) {
      
    }
    else {
      std::cout << "failed to read/write config!" << '\n';
    }
  }


  return 0;
}
