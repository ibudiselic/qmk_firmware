import re


PRE_WS = ' ' * 4
LAYOUT_SPLIT_WS = ' ' * 6
LAYOUT_NUMKEYS = 72
LAYOUT_HALF_COLS = 7
# Left offset (number of "holes"), nkeys
# Note that the thumb cluster "triangle" keys are part of the previous row.
LAYOUT = [
    (0, 7),
    (0, 7),
    (0, 7),
    (0, 6),
    (0, 6),
    (3, 3),
]
assert 2*sum(l[1] for l in LAYOUT) == LAYOUT_NUMKEYS
RE_LAYOUTS_START = re.compile(r'^const uint16_t PROGMEM keymaps.* = {$')


def _keymaps_start_line(lines: list[str]) -> int:
    for i, l in enumerate(lines):
        if RE_LAYOUTS_START.match(l):
            return i
    raise Exception('didn\'t find the layouts line')


# Returns line and column numbers where the matching `r` char is located, starting to count from
# the given `bc` (brace count). It is requred that `l` and `r` have length 1, and they are
# expected to be matching brace pairs (but any two characters will work).
# If `bc` is already zero, returns the location of the place where it next switches from 1 to 0.
# If the matching location can't be found, raises an exception.
def _matching_right_pair(lines: list[str], start_i: int, start_j: int, l: str, r: str, bc: int) -> tuple[int, int]:
    for i in range(start_i, len(lines)):
        for j in range(0 if i > start_i else start_j, len(lines[i])):
            c = lines[i][j]
            if c == l:
                bc += 1
            elif c == r:
                bc -= 1
                if bc == 0:
                    return i, j
    raise Exception(f'didn\'t find matching right pair for l={l} r={r} from {start}')


def _tokenize(s: str, ws: str, spec: str) -> list[str]:
    res = []
    cur = ''
    for c in s:
        if c in ws:
            if cur:
                res.append(cur)
                cur = ''
        elif c in spec:
            if cur:
                res.append(cur)
                cur = ''
            res.append(c)
        else:
            cur += c
    if cur:
        res.append(cur)
    return res


def _parse_keycodes(tokens: list[str]) -> list[str]:
    at = 0
    codes = []
    if tokens[-1] != ',':
        tokens.append(',')
    while at < len(tokens):
        if tokens[at+1] == ',':
            codes.append(tokens[at])
            at += 2
        else:
            assert tokens[at+1] == '('
            p = tokens.index(')', at + 1)
            assert tokens[p+1] == ','
            codes.append('{}({})'.format(tokens[at], ', '.join(t for t in tokens[at+2:p] if t != ',')))
            at = p + 2
    return codes


def _append_layout(keycodes: list[str], ret: list[str]) -> None:
    assert len(keycodes) == LAYOUT_NUMKEYS, f'Expected {LAYOUT_NUMKEYS} keys in a Moonlander layout, found {len(keycodes)}'
    key_len = max(len(t) for t in keycodes)
    # Space + comma.
    hole = ' '*(key_len+2)
    at = 0
    for left_offset, nkeys in LAYOUT:
        line = f'{PRE_WS}  '
        line += hole * left_offset
        for i in range(nkeys):
            # Make the comma next to the keycode, and pad after.
            k = f'{keycodes[at+i]},'
            # +1 accounts for the comma we just added.
            line += f' {k:{key_len+1}s}'
        line += hole * (LAYOUT_HALF_COLS-nkeys-left_offset)
        line += LAYOUT_SPLIT_WS
        line += hole * (LAYOUT_HALF_COLS-nkeys-left_offset)
        at += nkeys
        for i in range(nkeys):
            k = f'{keycodes[at+i]},'
            line += f' {k:{key_len+1}s}'
        at += nkeys
        ret.append(line.rstrip())
    ret[-1] = ret[-1][:-1] # Last line can't have a trailing comma.


def _fixed_keymaps(keymaps: list[str]) -> list[str]:
    tokens = _tokenize(''.join(keymaps), ' \t\r\n', '[](),')
    assert tokens[0] == '['
    ret = []
    at = 1
    while True:
        try:
            p = tokens.index('LAYOUT_moonlander', at+1)
        except ValueError:
            break
        assert tokens[p+1] == '('
        assert tokens[p-1] == '='
        assert tokens[p-2] == ']'
        assert tokens[p-4] == '['
        bc = 1
        for i in range(p+2, len(tokens)):
            if tokens[i] == '(':
                bc += 1
            elif tokens[i] == ')':
                bc -= 1
                if bc == 0:
                    at = i + 2
                    break
        assert tokens[at - 1] == ','
        assert tokens[at - 2] == ')'
        keycodes = _parse_keycodes(tokens[p+2:at-2])

        ret.append(f'{PRE_WS}[{tokens[p-3]}] = {tokens[p]}(')
        _append_layout(keycodes, ret)
        ret.append(f'{PRE_WS}),')
        ret.append('')
    return ret[:-1] # Remove the final empty line.


def fix_format(lines: list[str]) -> None:
    start = _keymaps_start_line(lines)
    endchar_i, endchar_c = _matching_right_pair(lines, start+1, 0, '{', '}', 1)
    assert lines[endchar_i] == '};', f'Found matching keymap }}, but it isn\'t on a separate line but: {lines[endchar_i]}'
    fixed_keymaps = _fixed_keymaps(lines[start+1:endchar_i])
    len_pre = endchar_i - (start+1)
    new_endchar_i = endchar_i + (len(fixed_keymaps) - len_pre)
    lines[start+1:endchar_i] = fixed_keymaps


def main():
    with open('keymap.c', 'r', encoding='utf-8') as f:
        lines = [l.rstrip() for l in f.readlines()]
    fix_format(lines)
    with open('keymap.c', 'w', encoding='utf-8', newline='\n') as f:
        f.write('\n'.join(lines))


if __name__ == '__main__':
    main()
