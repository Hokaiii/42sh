# 42sh

42sh is a simplified implementation of a UNIX shell, developed in C as part of the Epitech project.

## Features

- Execution of external commands via `execve`
- Management of arguments and execution paths
- Implementation of the following built-ins:
  - `cd`: change directory
  - `exit`: exit the shell
  - `setenv`: add/modify an environment variable
  - `env`: display environment variables
  - `unsetenv`: remove an environment variable
  - `>`: Redirects the output of a command to a file (overwrites the file if it exists).
  - `>>`: Redirects the output of a command to a file in append mode (without overwriting the file).
  - `<`: Redirects the input of a command from a file.
  - Management of environment variables with a linked list

## Launch:
  ```
make && ./42sh
  ```

## Usage

Start the shell with
`./42sh`

You can then enter commands as you would in a regular terminal.

### Example usage

```bash
$ ./mysh
$ ls -l
$ cd Documents
$ setenv MY_VAR EPITECH
$ env
$ unsetenv MY_VAR
$ ls > test.txt
$ whoami >> test.txt
$ cat < Makefile
$ exit
```

Project carried out as part of the `Epitech` school
