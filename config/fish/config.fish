if status is-interactive
    # Commands to run in interactive sessions can go here
end

# Color Palette provided by MinimalSwayFX
set -l foreground msfxSet(color_fg2)
set -l selection msfxSet(color_bg3)
set -l comment msfxSet(color_gray2)
set -l red msfxSet(color_red1)
set -l orange msfxSet(color_orange1)
set -l yellow msfxSet(color_yellow1)
set -l green msfxSet(color_green1)
set -l purple msfxSet(color_purple1)
set -l cyan msfxSet(color_aqua1)
set -l pink msfxSet(color_purple2)

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
