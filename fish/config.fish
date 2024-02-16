if status is-interactive
    # Commands to run in interactive sessions can go here
end

# themes
set -Ux fish_color_normal                     e6ccb2
set -Ux fish_color_command                    97a97c
set -Ux fish_color_param --bold               219ebc
set -Ux fish_color_quote                      ffcb70
set -Ux fish_color_redirection --bold         0077b6
set -Ux fish_color_end                        0077b6
set -Ux fish_color_error --bold               d08c60
set -Ux fish_color_comment                    6c757d
set -Ux fish_color_selection                  6c757d
set -Ux fish_color_search_match --background= 050505
set -Ux fish_color_operator --bold            ffcb70
set -Ux fish_color_escape                     219ebc
set -Ux fish_color_cwd --bold                 97a97c
set -Ux fish_color_autosuggestion             6c757d
set -Ux fish_color_user --bold                219ebc
set -Ux fish_color_host --bold                97a97c
set -Ux fish_color_host_remote --bold         d08c60
set -Ux fish_color_cancel                     d08c60

function fish_greeting
end

function fish_prompt
    printf ' %s%s%s $ ' \
        (set_color $fish_color_cwd) (prompt_pwd) (set_color $fish_color_normal)
end

alias ls="eza -l"
