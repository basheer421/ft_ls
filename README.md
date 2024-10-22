# ft_ls
ft_ls is a project where I recreated the functionality of the ls command from Unix-based systems in C. This version of ls supports a limited set of flags while ensuring memory efficiency (no memory leaks).

## Features
The ft_ls command supports the following flags:

-l : Use a long listing format to display additional information (permissions, links, owner, group, size, and date).

-R : Recursively list all directories and their contents.

-a : Include hidden files (those beginning with a dot .) in the output.

-r : Reverse the order of the results.

-t : Sort files by modification time, newest first.

## Requirements
- The project does not allow external libraries, so all functions, including memory management, were written from scratch.
- The goal is to create an efficient and functional version of ls while preventing memory leaks.

## Installation
To build the project, simply clone the repository and run make.

```bash
git clone https://github.com/basheer421/ft_ls
cd ft_ls
make
```

## Usage
```bash
./ft_ls [FLAGS] [DIRECTORY]
```

For example:
```bash
./ft_ls -la
```

This will list all files, including hidden ones, in the current directory using a long format.

## Project Highlights
Memory management was a key focus, and the implementation ensures there are no memory leaks.
The project is built without external libraries, adhering strictly to the rules of the 42 curriculum.
All code is written in C, ensuring it runs efficiently on Unix-based systems.

## Limitations
This version of ft_ls only implements a subset of the flags available in the real ls command (-l, -R, -a, -r, -t).
The command does not handle all edge cases that the actual ls would, such as advanced file types or unusual filesystem structures.


## License
This project is licensed under the MIT License. See the LICENSE file for details.

