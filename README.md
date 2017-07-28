# Runtime backtrace examples

Three different ways of getting a runtime backtrace. First uses libSegFault.so,
which was the simplest to implemnt. Second uses the builtin GCC libbacktrace,
and the third uses the libbacktrace found [here][1].

The winner seems to be libbacktrace, though libSegFault is perfect for C
applications.

[1]: https://github.com/ianlancetaylor/libbacktrace
