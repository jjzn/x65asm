# 6502-to-x86 instruction mappings

The following table lists the correspondence between 6502 instructions and their x86 equivalents that x65asm will produce. Not every available source instruction is listed, this is because the missing instructions are still not implemented.

| 6502 instruction | x86 instruction |
| --- | --- |
| `lda [value]` | `mov ax, [value]` |
| `ldx [value]` | `mov bx, [value]` |
| `ldy [value]` | `mov cx, [value]` |
| `sta [addr]` | `mov [addr], ax` |
| `stx [addr]` | `mov [addr], bx` |
| `sty [addr]` | `mov [addr], cx` |
| `inc` | `inc ax` |
| `inx` | `inc bx` |
| `iny` | `inc cx` |
| `dec` | `dec ax` |
| `dex` | `dec bx` |
| `dey` | `dec cx` |
| `cmp [value]` | `cmp ax, [value]` |
| `cpx [value]` | `cmp bx, [value]` |
| `cpy [value]` | `cmp cx, [value]` |
| `jmp [addr]` | `jmp [addr]` |
