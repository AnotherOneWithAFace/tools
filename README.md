# Some small tools I've made

If you're reading this, it's possible that one or more of these tools will be useful for you, and maybe of general interest. If you like them I'd appreciate a [follow](https://instagram.com/metroland.avi).

### brack.c

This just takes `argv` and wraps parentheses around them. If `argc` is 0 it takes its input from standard input instead. This is useful when you have a series of numbers on the command line and want to manipulate them in some flavour of lisp.

### p.c, makewords.c, lowercase.c, maj.c

These are all inspired by [this video](https://www.youtube.com/watch?v=tc4ROCJYbm0), particularly the part where Brian Kerighan walks through a simple example of a UNIX pipeline. I've always loved this demo but I was sad when some of the tools weren't included in the standard GNU system. So I wrote them myself!
