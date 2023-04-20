#ifndef __maybe_h
#define __maybe_h

#include <stdbool.h>

#define make_maybe(T) struct maybe_##T { bool ok; T val; }
#define maybe(T) struct maybe_##T
#define unwrap(x, msg) x.ok ? x.val : (panic("unwrapped none() value: %s\n", msg), x.val)
#define some(T, val) (maybe(T)) { true, val }
#define none(T) (maybe(T)) { false }

#endif /* __maybe_h */
