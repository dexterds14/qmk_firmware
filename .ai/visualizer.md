# Keymap visualizer

Location: `keyboards/handwired/dactyl_manuform/5x6/visualizer/`.

A dependency-free static webpage that renders the dactyl 5x6 keymap — layers,
tap-dances, leader sequences, RGB indicators — straight from the firmware
sources. No framework, no build step beyond one Python script.

## Files

| File | Role |
|------|------|
| `build_data.py` | Parses `keymap.c`, `keyboard.json`, `config.h`, `quantum/color.h` → `keymap-data.js`. Stdlib only. |
| `keymap-data.js` | **Generated.** Data inlined as `window.KEYMAP_DATA = {...}` and loaded via a `<script>` tag, so the page opens straight from `file://` (no server, no `fetch`). Do not hand-edit. |
| `index.html` | Page skeleton: header, sticky layer nav, keyboard stack, side rail (leader / tap-dance / legend). |
| `app.js` | Renders one SVG card per layer from geometry, sticky jump nav with scroll tracking, one fixed-position popover shared by all layers, cross-layer key tracing, leader flow, legends. |
| `styles.css` | Dark theme. |

## Regenerate after ANY source change (hard rule)

After editing `keymap.c`, `keyboard.json`, or `config.h`:

```sh
python3 keyboards/handwired/dactyl_manuform/5x6/visualizer/build_data.py
```

Commit the regenerated `keymap-data.js` alongside the source change. The
generator **validates and exits non-zero on drift**:

- key count per layer ≠ layout size (64)
- a `TD(...)` name used in a layer but missing from `enum tap_dance_keys`
- a `TD(...)` key with no entry in the curated `TD_SEMANTICS` table
- a phantom layer (`_CAPSIND`/`_ALTLKIND`/`_LOWLKIND`) that is not fully transparent
- an `RGB_*` index out of range of `RGBLIGHT_LAYERS_LIST`, or an unresolvable `HSV_*`
- a leader sequence with no actions

If it fails, fix the firmware source **or** the `TD_SEMANTICS` overlay in
`build_data.py` (below). Never edit `keymap-data.js` by hand.

## The tap-dance semantics overlay

`build_data.py` can parse the keymap *table*, but the per-key tap/double/triple/
hold **behaviour** lives in C functions (`osm_finished`, `layr_dn_finished`,
`layr_up_finished`) that aren't worth a full C parser. Those are captured by hand
in the `TD_SEMANTICS` dict near the top of `build_data.py`.

**When you change a tap-dance's behaviour in `keymap.c`, update the matching
`TD_SEMANTICS` entry too.** The generator validates that every `TD()` used on a
layer has a semantics entry, so a renamed/added TD key fails the build until you
add it — but a *behaviour* change (e.g. double-tap now does something else) is
your responsibility to mirror.

## Viewing

Just open the file in a browser — no server needed:

```
keyboards/handwired/dactyl_manuform/5x6/visualizer/index.html
```

The data is inlined into `keymap-data.js` (a `window.KEYMAP_DATA` assignment
loaded with a `<script>` tag), which sidesteps the `file://` CORS block that
`fetch()`/XHR would hit. If you edit the page and see stale data, hard-reload
(Ctrl/Cmd-Shift-R) to bust the browser cache.

## Layout

All six functional layers render at once as a vertical stack of cards — no tab
switching. Each card has a header (layer name, layer index, mapped-key count, RGB
swatch) and its own full-size SVG. Phantom indicator layers are omitted (explained
in the legend).

- **Sticky jump nav** — layer buttons tinted with each layer's runtime RGB color;
  clicking scrolls to that card, and an IntersectionObserver keeps the button for
  whichever layer crosses the middle of the viewport highlighted.
- **Shortcuts placement** — leader sequences, tap dances and the legend sit
  *below* the stack by default. At `min-width: 1400px` they move to a sticky
  420px side rail that scrolls independently of the stack.
- **Scale** — keyboard SVGs are capped at 1150px wide so they stay near 1:1
  instead of ballooning on ultrawide. Layers never render side by side.
- **Cross-layer tracing** — hovering or focusing any key outlines the same matrix
  position in all six layers, so a key's behaviour on LOWER vs RAISE vs LEADR can
  be compared without scrolling back and forth.
- **Ghosted transparent keys** — on a non-base layer, transparent keys are dashed
  and show the `_QWERTY` label underneath; click one for the fall-through note.
- **Key popovers** — a single `position: fixed` popover shared by all layers, kept
  glued to the key across scroll/resize and clamped to the viewport. Click any key
  for raw keycode + behaviour; tap-dance keys show the full
  tap/double/triple/hold table. `Esc` closes it.
- **Leader panel** — every sequence as `LEAD → keys → action`, with the 5
  commented-out (disabled) ones greyed and tagged.
- **Tap-dance table** — all 10 TD keys + the fast-typing passthrough note.
- **Legend** — RGB indicator swatches with triggers, custom keycodes
  (`DOT_SLS`/`DIR_UP`/`DBL_DASH`), timing constants, phantom-layer explanation.

## Runtime RGB note

The page uses the **actual** `enum rgb_layer` → `my_rgb_layers[]` index mapping
(so RAISE2=teal, MOUSE=pink, LEADER=magenta), matching the firmware, not the
legacy `my_layerN_layer` names. The comments in `keymap.c` were corrected to
agree with this.
