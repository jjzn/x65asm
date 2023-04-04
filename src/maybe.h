#ifndef __maybe_h
#define __maybe_h

#include <stdbool.h>

#define make_maybe(T) struct maybe_##T { bool ok; T val; }
#define maybe(T) struct maybe_##T
#define unwrap(x) x.ok ? x.val : (panic("unwrapped none() value\n"), x.val)
#define some(val) { true, val }
#define none() { false }

#endif /* __maybe_h */
