## Project Description

A C implementation of interactive user defined Linux shell.

## Compile

Compile using 'make' command

## Run

Run using './myshell' command

## Features

- Works almost like normal shell
- Keeps the directory where the shell is run, as home directory and shows the path of the current directory relative to that home directory
- Every command is run in new forked process
- 'cd', 'echo', 'pwd', 'jobs'(returns process related information like pid, process status, etc.) commands implemented as a part of shell.
- System commands are run as forked process which is served by system(OS)
- Implemented Background processes. Commands which have '&' appended, run in background.

