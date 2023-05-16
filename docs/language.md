# x65asm Language

The assembly language x65asm understands is a fairly simple one. A program consists of a sequence of lines, each of which may have a label, and may contain an instruction.

An instruction consists of an operation, which is either a 6502 assembly mnemonic or a pseudo-op (which starts with a period `.`); followed by an optional argument.

Arguments can be one of the following:
 - Accumulator: `A`
 - Immediate: `#value` between 0x0 and 0xFF
 - Zero page: `value` between 0x0 and 0xFF
 - Absolute: `value` between 0x0 and 0xFFFF
 - Indexed: `value,X` or `value,Y`
 - Indirect: `(value)`
 - Indexed indirect: `(value,X)`
 - Indirect indexed: `(value),Y`

## BNF grammar

A valid program can be expressed in Backus-Naur form (BNF):
```
program := { line }
line := [label] [instruction]
instruction := (op|pseudo-op) [argument]
```

Any line may contain a comment, which starts with a `;` (semicolon) and extends until the end of the line. Comments are discarded and not processed by the assembler.

See [`example`](./example) for some examples of 6502 assembly.

## Instructions

For a complete list of all the (known) 6502 instructions and their mnemonics, see the [6502.org Opcodes](http://www.6502.org/tutorials/6502opcodes.html) site.

See the [Emulator 101 site](http://www.emulator101.com/6502-addressing-modes.html) for an explanation of the 6502 addressing modes.

## Pseudo-ops

| Pseudo-Op | Meaning |
| --- | --- |
| `.org [addr]` | Sets the start address of the assembly output |
