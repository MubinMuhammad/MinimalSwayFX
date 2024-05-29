if status is-interactive
# Commands to run in interactive sessions can go here
end

# Color Palette provided by MinimalSwayFX
set -l foreground #ebdbb2
set -l selection #32302f
set -l comment #7c6f64
set -l red #cc241d
set -l orange #d65d0e
set -l yellow #d79921
set -l green #98971a
set -l purple #b16286
set -l cyan #689d6a
set -l pink #d3869b

set -g fish_color_normal $foreground
set -g fish_color_command $cyan
set -g fish_color_keyword $pink
set -g fish_color_quote $yellow
set -g fish_color_redirection $foreground
set -g fish_color_end $orange
set -g fish_color_error $red
set -g fish_color_param $purple
set -g fish_color_comment $comment
set -g fish_color_selection --background=$selection
set -g fish_color_search_match --background=$selection
set -g fish_color_operator $green
set -g fish_color_escape $pink
set -g fish_color_autosuggestion $comment

set -g fish_pager_color_progress $comment
set -g fish_pager_color_prefix $cyan
set -g fish_pager_color_completion $foreground
set -g fish_pager_color_description $comment
set -g fish_pager_color_selected_background --background=$selection

function fish_greeting
end

function fish_prompt
printf '%s%s%s $ ' \
(set_color $fish_color_cwd) (prompt_pwd) (set_color $fish_color_normal)
end

alias ls="eza -l"
alias vim="nvim"
alias vi="nvim"
