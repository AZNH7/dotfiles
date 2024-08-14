if status is-interactive
    # Commands to run in interactive sessions can go here
end

### EXPORT ###
set fish_greeting                                 # Supresses fish's intro message
set TERM "xterm-256color"

### AUTOCOMPLETE AND HIGHLIGHT COLORS ###
set fish_color_normal brcyan
set fish_color_autosuggestion '#7d7d7d'
set fish_color_command brcyan
set fish_color_error '#ff6c6b'
set fish_color_param brcyan
set fish_color_quote brgreen
set fish_color_redirection brred
set fish_color_search_match 'bryellow' # search term highlighting
set fish_color_selection '#b3d4fc' # selection highlighting
set fish_color_status red
set fish_color_user brgreen
set fish_color_valid_path brblue
set fish_pager_color_completion normal
set fish_pager_color_description brblue
set fish_pager_color_prefix normal
set fish_pager_color_progress normal
set fish_pager_color_secondary normal

# function fish_greeting
#    neofetch
# end

# set fish_greeting

starship init fish | source

######################## Aliases ########################

#Easier disk reading
alias df='df -h'                          # human-readable sizes
alias free='free -m'                      # show sizes in MB

#ls/exa
alias ls='exa -al --color=always --group-directories-first' # my preferred listing
alias la='exa -a --color=always --group-directories-first'  # all files and dirs
alias ll='exa -l --color=always --group-directories-first'  # long format
alias lt='exa -aT --color=always --group-directories-first' # tree listing
# alias l.='exa -a | egrep "^\."'

#Git
alias gadd='git add'
alias gaddall='git add .'
alias gbranch='git branch'
alias gcheckout='git checkout'
alias gclone='git clone'
alias gcommit='git commit -m'
alias gfetch='git fetch'
alias gpull='git pull origin'
alias gpush='git push origin'
alias gstatus='git status'
alias gtag='git tag'
alias gnewtag='git tag -a'

#Colorized grep
alias grep='grep --color=auto'
alias egrep='egrep --color=auto'
alias fgrep='fgrep --color=auto'

# ps
alias psa="ps auxf"
alias psgrep="ps aux | grep -v grep | grep -i -e VSZ -e"
alias psmem='ps auxf | sort -nr -k 4'
alias pscpu='ps auxf | sort -nr -k 3'

# get error messages from journalctl
alias jctl="journalctl -p 3 -xb"

#Permissions
# alias cp='cp -i'
# alias mv='mv -i'
# alias rm='rm -i'

#Starship prompt
eval "$(starship init fish)"

#better cat
alias cat='bat'

colorscript random


# functions
if set -q SSH_TTY
  set -g fish_color_host brred
end

# source /etc/profile with bash
#if status is-login
#    exec bash -c "aziz -e /etc/profile && source /etc/profile;\
#    exec fish"
#end

# Functions needed for !! and !$
function __history_previous_command
  switch (commandline -t)
  case "!"
    commandline -t $history[1]; commandline -f repaint
  case "*"
    commandline -i !
  end
end

function __history_previous_command_arguments
  switch (commandline -t)
  case "!"
    commandline -t ""
    commandline -f history-token-search-backward
  case "*"
    commandline -i '$'
  end
end
