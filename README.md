## Minishell

Minishell is a custom Unix shell written in C, designed to emulate the basic functionality of the `Bash` shell.

Features:
  - Displays a prompt when waiting for a new command
  - Maintains a command history
  - Searches and launches executables based on `PATH` or using relative/absolute paths
  - Supports input/output redirections:
    - `<` for input redirection
    - `>` for output redirection
    - `<<` for heredoc
    - `>>` for output append
  - Implements commands with pipes
  - Handles environment variables
  - Supports built-in commands:
      - echo
      - cd
      - pwd
      - export
      - unset
      - env
      - exit
  - Handles single (') and double (") quotes
  - Responds to ctrl-C, ctrl-D, and ctrl-\
