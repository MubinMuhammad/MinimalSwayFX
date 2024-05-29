---@type ChadrcConfig
local M = {}

-- Path to overriding theme and highlights files
local highlights = require "custom.highlights"

M.plugins = "custom.plugins"

M.ui = {
  theme = "gruvchad", -- right here 
  theme_toggle = { "gruvchad", "one_light" },
  transparency = true,
  statusline = {
    theme = "vscode_colored",
  },

  hl_override = {
    -- CursorLine = {
    --   bg = "#282828"
    -- }
  },
  hl_add = highlights.add,
}

-- check core.mappings for table structure
M.mappings = require "custom.mappings"

return M
