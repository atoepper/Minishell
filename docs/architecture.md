# 🏗️ Technical Architecture
The minishell is structured as a modular pipeline, where each stage has a single responsibility.
Input flows from prompt → parsing → execution, closely mirroring how a real shell operates.
```
User Input
   ↓
Lexer / Parser
   ↓
Command Structures
   ↓
Executor
   ↓
System Calls
```
This separation improves readability, debuggability, and teamwork.
## 🔍 Parsing Pipeline
The parsing stage is responsible for transforming raw user input into structured commands.
### Responsibilities
- Tokenization of input
- Quote handling (`'` and `"`) 
- Environment variable expansion (`$VAR`, `$?`)
- Syntax validation
- Heredoc processing
### Flow
```
readline()
   ↓
Lexer → tokens
   ↓
Expander
   ↓
Parser → command list
```
### Example: Tokenization (simplified)
```
while (*input)
{
    if (is_operator(input))
        add_token(OPERATOR, extract_op(&input));
    else
        add_token(WORD, extract_word(&input));
}
```
### Quote Handling
- Single quotes: literal interpretation
- Double quotes: variable expansion allowed
- Unclosed quotes are detected and rejected
```
if (quote == '\'' && c == '\'')
    quote = 0;
```
## ⚙️ Execution Engine
The execution stage converts parsed commands into running processes.
### Responsibilities
- Built-in detection
- Process creation (fork)
- Command execution (execve)
- Pipe management
- Redirections
- Exit status propagation
### Execution Strategy
Built-ins without pipes execute in the parent process
External commands and piped built-ins execute in child processes
```
pid = fork();
if (pid == 0)
    execve(cmd->path, cmd->argv, envp);
waitpid(pid, &status, 0);
```
## 🔗 Pipes & Redirections
Pipes and redirections are handled through careful file descriptor management.
### Pipe example
```
pipe(fd);
dup2(fd[1], STDOUT_FILENO);
close(fd[0]);
```
Each command:
- Receives input from the previous pipe
- Sends output to the next pipe if applicable
- Redirections override default stdin / stdout before execution.
## 🧠 Built-in Commands
Built-ins are implemented separately from external commands.
### Examples:
- cd
- export
- unset
- exit
```
if (is_builtin(cmd))
    return execute_builtin(cmd);
```
Special care is taken to:
- Modify the shell environment correctly
- Preserve behavior when built-ins are part of a pipeline
## 🚦 Signal Handling
Signal behavior matches bash expectations as closely as possible.
### Signals handled
- `SIGINT (Ctrl-C)`
- `SIGQUIT (Ctrl-\)`
- `EOF (Ctrl-D)`
```
signal(SIGINT, handle_sigint);
signal(SIGQUIT, SIG_IGN);
```
Behavior differs depending on context:
- Prompt
- Child process
- Heredoc
🧹 Memory & Resource Management
- No memory leaks
- File descriptors closed after use
- Child processes properly waited for
- Shell remains stable after errors
### Tested using:
- valgrind
## 👥 Work Distribution
The project was developed collaboratively with a clear division of responsibilities:
### atoepper
- Parsing and tokenization
- Quote and variable expansion
- Syntax validation
- Signal handling
### jweingar
- Execution engine
- Process management
- Pipes and redirections
- Built-in commands

This division allowed parallel development while maintaining a coherent overall design.
