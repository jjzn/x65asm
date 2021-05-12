# x65asm

x86asm is a fairly simple two-pass cross-assembler. It takes MOS 6502
assembler code and produces standalone x86 binaries.

## Features

- Should run on any x86-based platform
- Has few dependencies (only needs plain old `make` and a C compiler)
- Assembled binaries run in "real mode" for better 6502 compatibility
- Assembled binaries can be flashed onto external storage and booted from,
or can be run inside an emulator

## Installation

**NOTE:** x86asm requires a compiler conforming to the C99 standard, however,
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
./x65asm example.s -o example.img
```

After that, you can flash the resulting image onto a USB stick or a
similar medium and boot it. It may be easyer, however, to just run it
inside an emulator like QEMU:

```
qemu-system-x86 example.img
```

## License

This project is licensed under the [GPL v3.0](https://choosealicense.com/licenses/gpl-3.0/).
