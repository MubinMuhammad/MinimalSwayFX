local ls = require("luasnip")
local s = ls.snippet
local t = ls.text_node
local i = ls.insert_node
local fmt = require("luasnip.extras.fmt").fmt

ls.add_snippets("cpp", {
  s("cp", fmt(
    [[
      #include <bits/stdc++.h>
      using namespace std;

      int main() {{
        ios_base::sync_with_stdio(0);
        cin.tie(0);

        {}
        
        return 0;
      }}
    ]],
    { i(0) }
  )),
  s("cpt", fmt(
    [[
      #include <bits/stdc++.h>
      using namespace std;
      
      void solve() {{
        {}
      }}

      int main() {{
        ios_base::sync_with_stdio(0);
        cin.tie(0);

        int t; cin >> t; while (t--) solve();

        return 0;
      }}
    ]],
    { i(0) }
  ))
})
