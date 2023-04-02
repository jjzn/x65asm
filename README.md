# x65asm

x65asm is a fairly simple two-pass cross-assembler. It takes MOS 6502
assembler code and produces standalone x86 binaries.

## Features

- Should run on any x86-based platform
- Has few dependencies (only needs plain old `make` and a C compiler)
- Assembled binaries run in "real mode" for better 6502 compatibility
- Assembled binaries can be flashed onto external storage and booted from,
or can be run inside an emulator

## Installation

**NOTE:** x65asm requires a compiler conforming to the C99 standard, however,
support for VLAs is not required.

```
# clone the repo

git clone https://github.com/jjzn/x65asm.git
cd x65asm

# compile and install binaries

make && make install
```

`make install` installs binaries to `~/.local/bin/` by default.

## Usage

First, assemble the 6502 code:

```
./x65asm example.s
```

This will create a bootable disk image called `example.img`, which you
can flash onto a USB stick or a similar medium and boot. It may be
easier, however, to just run it inside an emulator like QEMU:

```
qemu-system-x86 example.img
```

For a full reference on the x65asm assembly language, see [docs/language.md](docs/language.md).

## Roadmap

Some features or ideas I would like to implement in the future:

- [ ] More and better documentation
- [ ] AFL/AFL++ input fuzzing and unit testing
- [ ] Automated pre-commit linting
- [ ] LLVM-based codegen (with a compile-time flag to switch between LLVM
and native backends?)

## License

This project is licensed under the [GPL v3.0](https://choosealicense.com/licenses/gpl-3.0/).
