# x65asm Language

The assembly language x65asm understands is a fairly simple one. A program consists of a sequence of lines, each of which may have a label, and may contain an instruction.

An instruction consists of an operation, which is either a 6502 assembly mnemonic or a pseudo-op (which starts with a period `.`); followed by an optional argument.

In Backus-Naur form (BNF):
```
program := { line }
line := [label] [instruction]
instruction := (op|pseudo-op) [argument]
```

## Instructions

For a complete list of all the (known) 6502 instructions and their mnemonics, see the [6502.org Opcodes](http://www.6502.org/tutorials/6502opcodes.html) site.

## Pseudo-ops

| Pseudo-Op | Meaning |
| --- | --- |
| `.org [addr]` | Sets the start address of the assembly output |
