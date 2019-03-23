## Features

* [x] List TCP and UDP connetions (IPv4).
* [x] List TCP and UDP connetions (IPv6).
* [x] Show corresponding command lines and arguments for each identified connection.
* [x] Implement -u and --udp option using `getopt_long(3)`.
* [x] Implement -t and --tcp option using `getopt_long(3)`.
* [x] Translate network address into user-friendly formats, e.g., from 0100007F to 127.0.0.1, and from FE01A8C0 to 192.168.1.254.
* [x] Implement basic filter string feature.
* [x] Use Makefile to manage the building process of your program.
* [x] If your filter string supports regular expression, see `regex(3)`.

## Requirement

Require C++ compiler with C++17 and `<filesystem>` support.

- Tested on Clang++ 8.0 with libc++ 8 on Ubuntu 16.04

On Ubuntu, you can install clang++8 and libc++ 8 with command below:

```
$ apt install clang-8 libc++-8-dev libc++abi-8-dev
```

> You may need official ppa supported by LLVM, see https://apt.llvm.org/

## Compile

Use `make all` to build the executable file `hw1`.

## Usage

```
$ ./hw1 [-t|--tcp] [-u|--udp] [filter-string]
```

You may use `root` to be able to read information of processes run by other users.

With un-priviliged user, pid/program field may show as `-`.
