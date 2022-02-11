# Strip C-like Comments

A **C program** to strip comments from a `c` file and output the result to a new file.

## Features

- Fast and Without any third-party library
- Without using Regex
- Remove inline C-style comments
- Remove multiline C-style comments
- Trim whitespaces
- Remove two or more empty lines 

## Build

```
gcc StripComments.c -o strip_comments
```

## Using

If you are going to strip comments and get the results in stdout:

```
./strip_comments StripComments.c
```

And maybe sometime you need to write the result in another or same file:

```
./strip_comments StripComments.c StripComments.nocomments.c
```

### TODO

- Add Makefile or CMake (to set `strip_comments` in /user/bin/)

© Copyright Max Base, 2022
