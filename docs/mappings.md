# 6502-to-x86 instruction mappings

The following table lists the correspondence between 6502 instructions and their x86 equivalents that x65asm will produce. Not every available source instruction is listed, this is because the missing instructions are still not implemented.

| 6502 instruction | x86 instruction | Implemented |
| --- | --- | --- |
| `lda [value]` | `mov ax, [value]` | **Yes** |
| `ldx [value]` | `mov bx, [value]` | **Yes** |
| `ldy [value]` | `mov cx, [value]` | **Yes** |
| `sta [addr]` | `mov [addr], ax` | **Yes** |
| `stx [addr]` | `mov [addr], bx` | **Yes** |
| `sty [addr]` | `mov [addr], cx` | **Yes** |
| `inc` | `inc [addr]` | **Yes** |
| `inx` | `inc bx` | **Yes** |
| `iny` | `inc cx` | **Yes** |
| `dec` | `dec [addr]` | **Yes** |
| `dex` | `dec bx` | **Yes** |
| `dey` | `dec cx` | **Yes** |
| `cmp [value]` | `cmp ax, [value]` | No |
| `cpx [value]` | `cmp bx, [value]` | No |
| `cpy [value]` | `cmp cx, [value]` | No |
| `jmp [addr]` | `jmp [addr]` | No |
