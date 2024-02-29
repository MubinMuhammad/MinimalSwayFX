local on_attach = require("plugins.configs.lspconfig").on_attach
local capabilities = require("plugins.configs.lspconfig").capabilities

local lspconfig = require "lspconfig"

-- if you just want default config for the servers then put them in a table
local servers = { 
  "html", "cssls", "tsserver", 
  "pylsp", "zls" 
}

for _, lsp in ipairs(servers) do
  lspconfig[lsp].setup {
    on_attach = on_attach,
    capabilities = capabilities
  }
end

lspconfig.rust_analyzer.setup {
  on_attach = on_attach,
  capabilities = capabilities
}

lspconfig.clangd.setup {
  on_attach = on_attach,
  capabilities = capabilities,

  cmd = {
    "clangd",
    "--offset-encoding=utf-16",
    "-header-insertion=never"
  }
}

-- 
-- lspconfig.pyright.setup { blabla}
