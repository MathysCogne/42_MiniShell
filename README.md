<div align="center">
<img src="subject/cover.png" alt="Covers" width="650" />

</br>
</br>

<strong>Minishell 👨‍💻🐧</strong>

<p>Minishell is a project from 42 School that involves creating a shell in C.</p>

</br>

<p><a href="https://github.com/MathysCogne/42_MiniShell/blob/main/subject/en.subject.pdf"><strong>Subject</strong></a></p>

</div>

## Features

- **Prompt**: Displays a prompt when waiting for a new command.
- **History**: Keeps a history of commands.
- **Pipes**: Supports pipes (`|`) to connect multiple commands.
- **Redirections**: Handles redirections (`>`, `>>`, `<`, `<<`) seamlessly.
- **Environment Variables**: Expands environment variables (`$HOME`, `$PATH`, etc.).
- **Error Codes**: Tracks and returns error codes (`$?`) for executed commands.
- **Builtins**: Implements internal commands:
  - `echo` (with `-n` flag)
  - `cd` (change directory)
  - `pwd` (print working directory)
  - `export` (set environment variables)
  - `unset` (unset environment variables)
  - `env` (display environment variables)
  - `exit` (terminate the shell)
- **Signals**: Properly handles signals such as:
  - `Ctrl+C` (interrupts the current command and displays a new prompt)
  - `Ctrl+D` (exits the shell if pressed at an empty prompt)
  - `Ctrl+\` (ignored in interactive mode).

</br>

## Parsing Part

The parsing stage is the backbone of the shell, as it transforms the raw input into a structured format for execution. It consists of two main steps: **tokenization** and **semantic analysis**.

### Tokenization
The tokenization process splits the user's input into tokens, which are the smallest meaningful units of the command. These tokens include:

- **Commands** (e.g., `ls`, `cat`, `grep`)
- **Arguments** (e.g., `-l`, `file.txt`)
- **Redirections** (`>`, `>>`, `<`, `<<`)
- **Pipes** (`|`)

#### How Tokenization Works:
1. **Identify the components**: The input string is traversed character by character to identify commands, arguments, redirections, and special characters like `|`.
2. **Handle quotes**: Properly handles single (`'`) and double (`"`) quotes to preserve spaces or special characters inside quoted strings.
   - Single quotes prevent all expansions.
   - Double quotes allow variable expansions (`$`).
3. **Ignore whitespace**: Skips unnecessary spaces while separating meaningful components.
4. **Classify tokens**: Assigns a type to each token (e.g., `TOKEN_COMMAND`, `TOKEN_ARGUMENT`, `TOKEN_PIPE`, etc.).

</br>

Input:

```bash
echo "hello world" | grep hello > output.txt
```
Tokens generated:

```bash
[TOKEN_COMMAND: echo]
[TOKEN_ARGUMENT: "hello world"]
[TOKEN_PIPE: |]
[TOKEN_COMMAND: grep]
[TOKEN_ARGUMENT: hello]
[TOKEN_REDIRECTION_OUT: >]
[TOKEN_ARGUMENT: output.txt]
```

</br>

### **2. Semantic Analysis**

The semantic analysis phase transforms the list of tokens into a hierarchy of commands and redirections while validating the syntax. This ensures that the input is both logical and executable.

#### Steps of Semantic Analysis:
1. **Validate Syntax**:
   - Detect invalid sequences like `| |`, `; ;`, or missing arguments for redirections (`>`, `<`).
   - Example: `echo |` will raise an error.
2. **Group Tokens**:
   - Constructs a command tree where each node represents a command or redirection.
   - Associates redirections (`>`, `<`, etc.) with their respective commands.
3. **Handle Logical Constructs**:
   - Maps pipes (`|`) to connect commands in a pipeline.

</br>

Input:

```bash
cat file.txt | grep "hello" > result.txt
```
Command structure:

```yaml
Command 1:
  - Executable: cat
  - Arguments: [file.txt]

Pipe to Command 2:
Command 2:
  - Executable: grep
  - Arguments: ["hello"]
  - Redirection: > result.txt
```

</br>


## Execution Part

Once the input is parsed and analyzed, the shell proceeds to the execution phase. Commands are executed in separate processes, with builtins handled directly in the shell process.

### Execution Flow:
1. **Forking**:
   - Creates a new process using `fork()` for each external command.
   - The parent process waits for the child process to complete using `waitpid()`.
2. **Piping**:
   - Sets up pipes (`pipe()`) to connect the output of one command to the input of the next.
   - Uses `dup2()` to duplicate file descriptors for standard input/output redirection.
3. **Redirections**:
   - Opens file descriptors for input/output redirections (`<`, `>`, `>>`, `<<`).
   - Uses `dup2()` to redirect standard input/output to the appropriate file descriptors.
4. **Builtin Commands**:
   - Executes builtins directly without forking to avoid unnecessary processes.
   - Builtins are handled by specific functions within the shell process.


</br>

## Compilation and Usage

</br>

```bash
# Compile:
make

# Start shell:
./minishell

# Start shell with test (Norm and Valgrind):
make test
```

</br>


⊹ ࣪ ﹏𓊝﹏𓂁﹏⊹ ࣪ ˖

</br>

## Disclaimer
> At 42 School, most projects must comply with the [Norm](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf).

