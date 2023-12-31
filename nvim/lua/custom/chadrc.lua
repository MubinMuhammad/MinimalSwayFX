---@type ChadrcConfig
local M = {}

-- Path to overriding theme and highlights files
local highlights = require "custom.highlights"

M.plugins = "custom.plugins"

M.ui = {
  theme = "gruvchad", -- right here 
  theme_toggle = { "ashes", "one_light" },
  transparency = true,
  statusline = {
    theme = "minimal",
  },

  hl_override = highlights.override,
  hl_add = highlights.add,
}

-- check core.mappings for table structure
M.mappings = require "custom.mappings"

return M
