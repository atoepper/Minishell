# 🐚 minishell 
A simplified Unix shell implemented in C.

## 📌 Project Overview
minishell is a custom implementation of a Unix command-line shell.
It replicates essential behaviors of bash, including command execution, pipes, redirections, and environment variable handling.
The goal of this project is to deepen understanding of:
- Process creation
- File descriptors
- Signals
- Parsing and tokenization
- Shell behavior and edge cases

## ✨ Features
- Execute system commands (`ls`, `cat`, `grep`, etc.)
- Built-in commands:
  * `echo`
  * `cd`
  * `pwd`
  * `export`
  * `unset`
  * `env`
  * `exit`
- Pipes (`|`)
- Redirections:
  * Input `<`
  * Output `>`
  * Append `>>`
  * Heredoc `<<`
- Environment variable expansion (`$VAR`, `$?`)
- Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)
- Exit status management
- Quote handling (`'` and `"`)

## 🧠 Shell Behavior
minishell aims to behave similarly to bash, including:
- Correct exit codes
- Handling of invalid syntax
- Proper signal responses
- Memory management without leaks

⚠️ This is not a full bash implementation — behavior is limited to the project requirements.

## 🛠️ Installation
### Requirements
- Linux
- gcc
- make
- readline library
### Build
```
git clone https://github.com/atoepper/minishell.git
cd minishell
make
```
## ▶️ Usage
### Run the shell:
`./minishell`
### Example commands:
```
minishell$ echo "Hello, world"
minishell$ ls -la | grep minishell
minishell$ export NAME=42
minishell$ echo $NAME
minishell$ cat << EOF
```
### Exit the shell:
```
minishell$ exit
```
## 📚 Constraints
This project follows 42 School constraints.
### Allowed functions:
- `readline`, `rl_clear_history`
- `fork`, `execve`, `waitpid`
- `pipe`, `dup2`
- `signal`, `kill`
- `malloc`, `free`

## 🏗️ Architecture Overview

minishell is designed as a modular pipeline:
input → parsing → execution.

The full architectural design and rationale are documented in [`docs/architecture.md`](docs/architecture.md)

## 👥 Authors
Alexander Toepper — atoepper

Johannes Weingarten — jweingar

## 📜 License
This project is part of the 42 School curriculum and is intended for educational purposes only.
