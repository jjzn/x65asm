# 6502-to-x86 instruction mappings

The following table lists the correspondence between 6502 instructions and their x86 equivalents that x65asm will produce. Not every available source instruction is listed, this is because the missing instructions are still not implemented.

| 6502 instruction | x86 instruction |
| --- | --- |
| `lda [value]` | `mov ax, [value]` |
