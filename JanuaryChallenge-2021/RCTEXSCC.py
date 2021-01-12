#!/usr/bin/env python
from collections import defaultdict

def h(a, b, c, d):
    if ((c == a and b == d) or
        (a == c == d) or
        (b == c == d)):
        return 0
    elif ((a == c and d != c and d != b) or
          (b == d and c != a and c != d) or
          (c == d and a != c and b != d)):
        return 1
    else:
        return 2

for k in range(26):
    transition_map = {
        (True, True, 0): k,
        (True, True, 1): k**2 - k,
        (True, False, 1): 2*k**2 - 2*k,
        (True, False, 2): k**3 - 3*k**2 + 2*k,
        (False, True, 0): 2*k**2 - 2*k,
        (False, True, 1): k**3 - 3*k**2 + 2*k,
        (False, False, 0): k**2 - k,
        (False, False, 1): 2*k**3 - 6*k**2 + 4*k,
        (False, False, 2): k**4 - 4*k**3 + 6*k**2 - 3*k,
    }

    for a in range(k):
        for b in range(k):
            for c in range(k):
                for d in range(k):
                    transition_map[(a == b, c == d, h(a, b, c, d))] -= 1

    for kk, v in transition_map.items():
        assert v == 0, (kk, k, v)
