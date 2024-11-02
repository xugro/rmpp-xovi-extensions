# fileman

The module responsible for remapping files without editing or moving any of them.
It exports the following functions:

- `int fopenToOpenFlags(const char *mode)` - accepts `fopen`-style mode flags, returns flags for `open()`.
- `int anyFlagsToSyscall(const char *mode, int flags, int iMode)` - accepts any flags (`fopen`-style take precedense) and returns flags for `open`.
- `int anyFlagsToSimple(const char *mode, int flags, int iMode)` - accepts any flags (`fopen`-style take precedense) and returns fileman-specific bitmask of FILEMAN_SIMPLE_WRITE and FILEMAN_SIMPLE_READ. FILEMAN_SIMPLE_ILLEGAL if flags are invalid.
- `void registerOverride(struct FilemanOverride *entry)` - registers a filesystem file override (see [fileman.h](src/fileman.h) for details.)

Note: struct FilemanOverride *entry needs to be stored on the heap!
