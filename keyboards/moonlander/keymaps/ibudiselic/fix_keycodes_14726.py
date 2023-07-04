"""Fixes keycodes after https://github.com/qmk/qmk_firmware/pull/14726

Pass the file name to modify (e.g. the keycodes.c file) as the only argument.

This is not semantics aware, but instead just token-boundary wraps the keycode
tokens and does a global replace. So review the result carefully.

The constants are copied from the PR text.

Note that some of the long-form codes also have aliases defined in
https://docs.qmk.fm/#/keycodes which are not mentioned in the PR or used in
this script, i.e. this script doesn't produce the short alias codes wherever
possible..
"""

import re
import sys

# Old Keycode New Keycode
RENAMES = """
KC_BSPACE	KC_BACKSPACE
KC_LBRACKET	KC_LEFT_BRACKET
KC_RBRACKET	KC_RIGHT_BRACKET
KC_BSLASH	KC_BACKSLASH
KC_SCOLON	KC_SEMICOLON
KC_CAPSLOCK	KC_CAPS_LOCK
KC_PSCREEN	KC_PRINT_SCREEN
KC_SCROLLLOCK	KC_SCROLL_LOCK
KC_PGUP	KC_PAGE_UP
KC_PGDOWN	KC_PAGE_DOWN
KC_NUMLOCK	KC_NUM_LOCK
KC_NONUS_BSLASH	KC_NONUS_BACKSLASH
KC_POWER	KC_KB_POWER
KC__MUTE	KC_KB_MUTE
KC__VOLUP	KC_KB_VOLUME_UP
KC__VOLDOWN	KC_KB_VOLUME_DOWN
KC_LOCKING_CAPS	KC_LOCKING_CAPS_LOCK
KC_LOCKING_NUM	KC_LOCKING_NUM_LOCK
KC_LOCKING_SCROLL	KC_LOCKING_SCROLL_LOCK
KC_INT1	KC_INTERNATIONAL_1
KC_INT2	KC_INTERNATIONAL_2
KC_INT3	KC_INTERNATIONAL_3
KC_INT4	KC_INTERNATIONAL_4
KC_INT5	KC_INTERNATIONAL_5
KC_INT6	KC_INTERNATIONAL_6
KC_INT7	KC_INTERNATIONAL_7
KC_INT8	KC_INTERNATIONAL_8
KC_INT9	KC_INTERNATIONAL_9
KC_LANG1	KC_LANGUAGE_1
KC_LANG2	KC_LANGUAGE_2
KC_LANG3	KC_LANGUAGE_3
KC_LANG4	KC_LANGUAGE_4
KC_LANG5	KC_LANGUAGE_5
KC_LANG6	KC_LANGUAGE_6
KC_LANG7	KC_LANGUAGE_7
KC_LANG8	KC_LANGUAGE_8
KC_LANG9	KC_LANGUAGE_9
KC_ALT_ERASE	KC_ALTERNATE_ERASE
KC_SYSREQ	KC_SYSTEM_REQUEST
KC_LCTRL	KC_LEFT_CTRL
KC_LSHIFT	KC_LEFT_SHIFT
KC_LALT	KC_LEFT_ALT
KC_LGUI	KC_LEFT_GUI
KC_RCTRL	KC_RIGHT_CTRL
KC_RSHIFT	KC_RIGHT_SHIFT
KC_RALT	KC_RIGHT_ALT
KC_RGUI	KC_RIGHT_GUI
"""

# Alias	Keycode
ADDED_ALIASES = """
KC_SCRL	KC_SCROLL_LOCK
KC_PGUP	KC_PAGE_UP
KC_NUM	KC_NUM_LOCK
KC_INT1	KC_INTERNATIONAL_1
KC_INT2	KC_INTERNATIONAL_2
KC_INT3	KC_INTERNATIONAL_3
KC_INT4	KC_INTERNATIONAL_4
KC_INT5	KC_INTERNATIONAL_5
KC_INT6	KC_INTERNATIONAL_6
KC_INT7	KC_INTERNATIONAL_7
KC_INT8	KC_INTERNATIONAL_8
KC_INT9	KC_INTERNATIONAL_9
KC_LNG1	KC_LANGUAGE_1
KC_LNG2	KC_LANGUAGE_2
KC_LNG3	KC_LANGUAGE_3
KC_LNG4	KC_LANGUAGE_4
KC_LNG5	KC_LANGUAGE_5
KC_LNG6	KC_LANGUAGE_6
KC_LNG7	KC_LANGUAGE_7
KC_LNG8	KC_LANGUAGE_8
KC_LNG9	KC_LANGUAGE_9
KC_SYRQ	KC_SYSTEM_REQUEST
KC_CNCL	KC_CANCEL
KC_PRIR	KC_PRIOR
KC_RETN	KC_RETURN
KC_SEPR	KC_SEPARATOR
KC_CLAG	KC_CLEAR_AGAIN
KC_CRSL	KC_CRSEL
KC_EXSL	KC_EXSEL
KC_LALT	KC_LEFT_ALT
KC_LGUI	KC_LEFT_GUI
KC_RALT	KC_RIGHT_ALT
KC_RGUI	KC_RIGHT_GUI
"""

# Alias	Replacement
REMOVED_ALIASES = """
KC_CLCK	KC_CAPS
KC_SLCK	KC_SCRL
KC_NLCK	KC_NUM
KC_ZKHK	JP_ZKHK
KC_RO	JP_BSLS
KC_KANA	JP_KANA
KC_JYEN	JP_YEN
KC_HENK	JP_HENK
KC_MHEN	JP_MHEN
KC_HAEN	KR_HAEN
KC_HANJ	KR_HANJ
"""


def mkdict(mapping: str) -> dict[str, str]:
    """Parses a string in the format above in the file into a simple dict mapping.
    """
    res = {}
    for line in mapping.split("\n"):
        line = line.strip()
        if line == "":
            continue
        parts = line.split("\t")
        assert len(parts) == 2
        a, b = parts
        assert a not in res
        res[a] = b
    return res


def mkrules() -> list[tuple[str, str]]:
    """Returns a list of rewrite rules for the keymap.
    """
    renames = mkdict(RENAMES)
    # Make it easier to "apply" the alieses to the renames. We want the long
    # code to be the key, and the alias to be the value.
    add_alias = {v:k for k, v in mkdict(ADDED_ALIASES).items()}
    remove_alias = mkdict(REMOVED_ALIASES)

    # We want the short names in the keymap, so apply the aliases where available.
    for old, new_long in renames.items():
        alias = add_alias.get(new_long, None)
        if alias is not None:
            renames[old] = alias

    # Add the remaining new alises.
    for long_name, alias in add_alias.items():
        if long_name not in renames:
            renames[long_name] = alias

    # Add rename rules for the removed aliases.
    for old_alias, new_alias in remove_alias.items():
        assert old_alias not in renames
        renames[old_alias] = new_alias

    # Finally, remove no-ops that can arise from the above tranformation, like
    # KC_LALT -> KC_LALT.
    renames = {k:v for k, v in renames.items() if k != v}

    return sorted([(old_val, new_val) for old_val, new_val in renames.items()])


def apply_rules(code: str, rules: list[tuple[str, str]]) -> str:
    """Returns the code modified with the given rewrite rules, applying them one by one in order.
    """
    total = 0
    for old_val, new_val in rules:
        code, n = re.subn(rf"\b{old_val}\b", new_val, code)
        if n > 0:
            print(f"{old_val} -> {new_val}  ({n} times)")
            total += n
    print(f"A total of {total} replacements made.")
    return code


def main():
    if len(sys.argv) != 2:
        print("Pass the file name to update as the only argument.", file=sys.stderr)
        sys.exit(1)

    rules = mkrules()
    print(f"Parsed {len(rules)} rename rules.")
    print("Applying them...")

    with open(sys.argv[1], "r") as f:
        code = f.read()
    code = apply_rules(code, rules)
    with open(sys.argv[1], "w") as f:
        f.write(code)
    print("Done.")


if __name__ == "__main__":
    main()
