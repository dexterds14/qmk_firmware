const UNIT = 64, KEY = 60, GAP = 30;
const SVG_NS = "http://www.w3.org/2000/svg";
// Per-key label fitting: keep LABEL_PAD either side inside the key box, and never
// shrink below LABEL_MIN user units. LABEL_MIN is a floor, not a target — at
// LABEL_PAD 5 the widest label in this keymap still lands at ~7.1u.
const LABEL_PAD = 5, LABEL_MIN = 7;

function hexToRgb(hex) {
  const n = parseInt(hex.slice(1), 16);
  return [(n >> 16) & 255, (n >> 8) & 255, n & 255];
}
function mix(hex, withHex, amt) {
  const a = hexToRgb(hex), b = hexToRgb(withHex);
  const c = a.map((v, i) => Math.round(v * amt + b[i] * (1 - amt)));
  return `rgb(${c[0]},${c[1]},${c[2]})`;
}
function lum(hex) {
  const [r, g, b] = hexToRgb(hex);
  return (0.299 * r + 0.587 * g + 0.114 * b) / 255;
}

let DATA, baseLayer, boardW, boardH;
const keysByIdx = new Map();

function px(g) {
  return { x: g.x * UNIT + (g.x >= 9 ? GAP : 0), y: g.y * UNIT };
}

function el(tag, attrs, ...kids) {
  const e = document.createElementNS(SVG_NS, tag);
  for (const [k, v] of Object.entries(attrs || {})) e.setAttribute(k, v);
  for (const k of kids) if (k != null) e.appendChild(typeof k === "string" ? document.createTextNode(k) : k);
  return e;
}

function layerByName(n) { return DATA.layers.find(l => l.name === n); }
function shownLayers() { return DATA.layers.filter(l => !l.phantom); }
function layerTitle(l) { return l.name.replace(/^_/, ""); }
function cardId(l) { return "layer-" + layerTitle(l); }

function renderNav() {
  const nav = document.getElementById("layer-nav");
  nav.innerHTML = "";
  for (const l of shownLayers()) {
    const b = document.createElement("button");
    b.textContent = layerTitle(l);
    b.dataset.target = cardId(l);
    if (l.rgb) {
      b.style.setProperty("--tab-color", l.rgb);
      b.style.setProperty("--tab-text", lum(l.rgb) > 0.55 ? "#111" : "#eee");
    }
    b.onclick = () => {
      const card = document.getElementById(b.dataset.target);
      if (card) card.scrollIntoView({ behavior: "smooth", block: "start" });
    };
    nav.appendChild(b);
  }
}

// Highlight the nav button for whichever layer card crosses the middle of the viewport.
function trackActiveLayer() {
  const io = new IntersectionObserver((entries) => {
    for (const e of entries) {
      if (!e.isIntersecting) continue;
      document.querySelectorAll("#layer-nav button").forEach(b =>
        b.classList.toggle("active", b.dataset.target === e.target.id));
    }
  }, { rootMargin: "-42% 0px -52% 0px", threshold: 0 });
  document.querySelectorAll(".layer-card").forEach(c => io.observe(c));
}

function renderStack() {
  const stack = document.getElementById("layers-stack");
  stack.innerHTML = "";
  keysByIdx.clear();
  for (const l of shownLayers()) stack.appendChild(renderLayerCard(l));
}

// Fit every key label into its box. Measured with getComputedTextLength() so the
// result is in SVG user units and stays correct however wide the page renders the
// keyboard. Sized per distinct label (cached) rather than per key instance.
// Requires the cards to be in the document, so it runs once after renderStack().
function fitLabels() {
  const labels = [...document.querySelectorAll(".key .label")].filter(t => t.textContent);
  if (!labels.length) return;
  const base = parseFloat(getComputedStyle(labels[0]).fontSize);
  const avail = KEY - LABEL_PAD * 2;
  const sizes = new Map();
  for (const t of labels) {
    const txt = t.textContent;
    let size = sizes.get(txt);
    if (size === undefined) {
      t.style.fontSize = base + "px";
      const w = t.getComputedTextLength();
      size = w > avail ? Math.max(LABEL_MIN, base * avail / w) : base;
      sizes.set(txt, size);
    }
    t.style.fontSize = size.toFixed(2) + "px";
  }
}

function renderLayerCard(layer) {
  const card = document.createElement("section");
  card.className = "layer-card";
  card.id = cardId(layer);
  card.style.setProperty("--layer-color", layer.rgb || "#3a4150");

  const mapped = layer.keys.filter(k => k.kind !== "transparent").length;
  const head = document.createElement("div");
  head.className = "layer-head";
  head.innerHTML = `<span class="swatch" style="background:${layer.rgb || "#3a4150"}"></span>` +
    `<h2>${layerTitle(layer)}</h2>` +
    `<span class="layer-meta">layer ${layer.index} · ${mapped} of ${layer.keys.length} keys mapped</span>`;
  card.appendChild(head);

  const wrap = document.createElement("div");
  wrap.className = "kbd-wrap";
  const svg = el("svg", { class: "kbd", xmlns: SVG_NS });
  svg.setAttribute("viewBox", `0 0 ${boardW} ${boardH}`);
  DATA.geometry.forEach((g, i) => {
    const grp = keyGroup(layer, g, i);
    const idx = String(i);
    const list = keysByIdx.get(idx) || [];
    list.push(grp);
    keysByIdx.set(idx, list);
    svg.appendChild(grp);
  });
  wrap.appendChild(svg);
  card.appendChild(wrap);
  return card;
}

function keyGroup(layer, g, i) {
  const entry = layer.keys[i];
  const base = baseLayer.keys[i];
  const { x, y } = px(g);
  const transparent = entry.kind === "transparent";
  const shown = transparent ? base : entry;
  const color = layer.rgb || "#3a4150";

  const grp = el("g", {
    class: `key kind-${shown.kind}${transparent ? " ghost" : ""}${g.half === "right" ? " right" : ""}`,
    transform: `translate(${x},${y})`,
    "data-idx": i,
    tabindex: 0,
  });
  const rect = el("rect", {
    width: KEY, height: KEY, rx: 8,
    fill: transparent ? "#20242c" : mix(color, "#262b34", 0.16),
    stroke: transparent ? "#3a4150" : mix(color, "#000", 0.35),
    "stroke-dasharray": transparent ? "4 3" : "none",
  });
  grp.appendChild(rect);

  const label = el("text", {
    class: "label", x: KEY / 2, y: KEY / 2 + 1,
    fill: transparent ? "#6b7484" : "#e8ecf2",
  }, shown.label);
  grp.appendChild(label);

  if (!transparent && shown.kind === "tapdance") {
    const badge = el("text", { class: "td-badge", x: KEY - 6, y: 12, "text-anchor": "end" }, "TD");
    grp.appendChild(badge);
  }
  if (!transparent && (shown.kind === "oneshot_layer" || shown.kind === "layer_switch")) {
    const sub = el("text", { class: "sub", x: KEY / 2, y: KEY - 8 },
      shown.kind === "oneshot_layer" ? "OSL" : "switch");
    grp.appendChild(sub);
  }

  grp.addEventListener("click", (e) => {
    e.stopPropagation();
    showPopover(grp, layer, i, shown, transparent);
  });
  grp.addEventListener("keydown", (e) => {
    if (e.key === "Enter" || e.key === " ") {
      e.preventDefault();
      showPopover(grp, layer, i, shown, transparent);
    }
  });
  return grp;
}

function highlightIdx(idx) {
  document.querySelectorAll(".key.xlink").forEach(k => k.classList.remove("xlink"));
  if (idx == null) return;
  for (const grp of keysByIdx.get(idx) || []) grp.classList.add("xlink");
}

let popoverAnchor = null;

function hidePopover() {
  const p = document.getElementById("popover");
  p.hidden = true;
  popoverAnchor = null;
  document.querySelectorAll(".key.selected").forEach(k => k.classList.remove("selected"));
}

function showPopover(grp, layer, idx, shown, transparent) {
  hidePopover();
  grp.classList.add("selected");
  const p = document.getElementById("popover");
  const g = DATA.geometry[idx];
  const base = baseLayer.keys[idx];

  let html = `<div class="pop-head"><b>${shown.label || "(transparent)"}</b>
    <span class="pop-matrix">matrix [${g.matrix[0]},${g.matrix[1]}] · ${g.half}</span></div>`;

  if (transparent) {
    html += `<p class="pop-note">Transparent on <b>${layer.name}</b> — falls through to
      <b>${baseLayer.name}</b>: <code>${base.raw}</code></p>`;
    if (base.kind === "tapdance") html += tdDetailHtml(base.td);
  } else {
    html += `<div class="pop-raw">raw: <code>${shown.raw}</code></div>`;
    switch (shown.kind) {
      case "tapdance": html += tdDetailHtml(shown.td); break;
      case "oneshot_layer":
        html += `<p>One-shot <b>${shown.layer}</b>: next keypress uses that layer, then it releases.
                 Double-tap <b>locks</b> it (<code>ONESHOT_TAP_TOGGLE ${DATA.timings.ONESHOT_TAP_TOGGLE}</code>).</p>`;
        break;
      case "oneshot_mod":
        html += `<p>One-shot <b>${shown.mod.replace("MOD_", "")}</b> for the next keypress.</p>`;
        break;
      case "layer_switch":
        html += `<p>Switches the active layer to <b>${shown.layer}</b> until another <code>TO()</code>.</p>`;
        break;
      case "custom":
        html += `<p>Custom keycode: <b>${shown.detail}</b></p>`;
        break;
      case "chord":
        html += `<p>Chord: <b>${shown.label}</b></p>`;
        break;
      case "special":
        html += `<p>QMK special: <b>${shown.label}</b></p>`;
        break;
      default:
        html += `<p>Types <b>${shown.label}</b></p>`;
    }
  }

  p.innerHTML = html;
  p.hidden = false;
  popoverAnchor = grp;
  positionPopover();
}

// Fixed positioning keeps one popover valid across all six stacked keyboards.
function positionPopover() {
  const p = document.getElementById("popover");
  if (!popoverAnchor || p.hidden) return;
  const r = popoverAnchor.getBoundingClientRect();
  const pw = p.offsetWidth, ph = p.offsetHeight;
  let left = r.left + r.width / 2 - pw / 2;
  left = Math.max(8, Math.min(left, window.innerWidth - pw - 8));
  let top = r.top - ph - 10;
  if (top < 8) top = r.bottom + 10;
  if (top + ph > window.innerHeight - 8) top = Math.max(8, window.innerHeight - ph - 8);
  p.style.left = left + "px";
  p.style.top = top + "px";
}

let positionQueued = false;
function queuePosition() {
  if (positionQueued) return;
  positionQueued = true;
  requestAnimationFrame(() => { positionQueued = false; positionPopover(); });
}

function tdDetailHtml(tdName) {
  if (!tdName) return "";
  const s = DATA.tapDances[tdName];
  if (!s) return "";
  let h = `<table class="pop-td"><tr><th>tap</th><td>${s.tap}</td></tr>
    <tr><th>double</th><td>${s.double}</td></tr>
    <tr><th>triple</th><td>${s.triple}</td></tr>
    <tr><th>hold</th><td>${s.hold}</td></tr></table>`;
  if (s.note) h += `<p class="pop-note">${s.note}</p>`;
  return h;
}

function renderLeader() {
  const ul = document.getElementById("leader-list");
  ul.innerHTML = "";
  document.getElementById("leader-timeout").textContent =
    `QK_LEAD on _LEADR thumb keys · ${DATA.leader.timeoutMs} ms per key (LEADER_TIMEOUT, per-key timing)`;
  for (const s of DATA.leader.sequences) {
    const li = document.createElement("li");
    li.className = s.active ? "active" : "disabled";
    const chips = [`<span class="chip lead">LEAD</span>`,
      ...s.keys.map(k => `<span class="chip">${k}</span>`)].join("<span class='arrow'>→</span>");
    li.innerHTML = `${chips}<span class="arrow">→</span><span class="action">${s.action}</span>
      ${s.active ? "" : "<span class='tag'>disabled</span>"}
      ${s.note ? `<div class="seq-note">${s.note}</div>` : ""}`;
    ul.appendChild(li);
  }
}

function renderTdTable() {
  const tb = document.querySelector("#td-table tbody");
  tb.innerHTML = "";
  for (const [name, s] of Object.entries(DATA.tapDances)) {
    const tr = document.createElement("tr");
    tr.innerHTML = `<td><b>${s.base}</b><div class="td-name">${name}</div></td>
      <td>${s.tap.replace(/^types /, "")}</td><td>${s.double}</td><td>${s.triple}</td><td>${s.hold}</td>`;
    tb.appendChild(tr);
  }
  const t = DATA.timings;
  document.getElementById("td-fast").textContent =
    `Fast typing (≤ ${t.FLOW_TAP_TERM} ms between keys) types the base letter immediately. ` +
    `TAPPING_TERM ${t.TAPPING_TERM} ms. Interrupted holds emit the tap.`;
}

function renderLegend() {
  const rgb = document.getElementById("rgb-legend");
  rgb.innerHTML = "<h3>RGB layer indicators</h3>";
  for (const e of DATA.rgbLegend) {
    const row = document.createElement("div");
    row.className = "legend-row";
    row.innerHTML = `<span class="swatch" style="background:${e.hex}"></span>
      <b>${e.name}</b> — ${e.trigger}`;
    rgb.appendChild(row);
  }
  if (DATA.baseColor) {
    const row = document.createElement("div");
    row.className = "legend-row";
    row.innerHTML = `<span class="swatch" style="background:${DATA.baseColor}"></span>
      <b>base</b> — idle (rgblight_sethsv 94,255,50)`;
    rgb.appendChild(row);
  }

  const cust = document.getElementById("custom-legend");
  cust.innerHTML = "<h3>Custom keycodes</h3>";
  for (const [k, v] of Object.entries(DATA.customKeycodes)) {
    const row = document.createElement("div");
    row.className = "legend-row";
    row.innerHTML = `<code>${k}</code> — ${v}`;
    cust.appendChild(row);
  }

  const tim = document.getElementById("timings-legend");
  tim.innerHTML = "<h3>Timings & notes</h3>";
  const t = DATA.timings;
  tim.innerHTML += `<ul>
    <li>TAPPING_TERM ${t.TAPPING_TERM} ms · FLOW_TAP_TERM ${t.FLOW_TAP_TERM} ms</li>
    <li>LEADER_TIMEOUT ${t.LEADER_TIMEOUT} ms per key (LEADER_PER_KEY_TIMING)</li>
    <li>ONESHOT_TAP_TOGGLE ${t.ONESHOT_TAP_TOGGLE} — double-tap locks OSL layers</li>
    <li>Phantom layers <code>_CAPSIND</code>/<code>_ALTLKIND</code>/<code>_LOWLKIND</code> are
        transparent indicator bits synced master→slave (caps / alt-lock / lower-lock).</li>
  </ul>`;
}

function init(d) {
  DATA = d;
  baseLayer = layerByName("_QWERTY");
  boardW = Math.max(...DATA.geometry.map(g => px(g).x)) + UNIT;
  boardH = Math.max(...DATA.geometry.map(g => px(g).y)) + UNIT;
  document.getElementById("meta").textContent =
    `${d.meta.keyboard} · ${d.meta.keymap} · source ${d.meta.sourceCommit}`;
  document.getElementById("footer").textContent =
    `Generated by ${d.meta.generatedBy} — regenerate after any keymap/keyboard.json/config.h change: ` +
    `python3 keyboards/handwired/dactyl_manuform/5x6/visualizer/build_data.py`;
  renderNav();
  renderStack();
  fitLabels();
  trackActiveLayer();
  renderLeader();
  renderTdTable();
  renderLegend();

  const stack = document.getElementById("layers-stack");
  stack.addEventListener("mouseover", (e) => {
    const key = e.target.closest ? e.target.closest(".key") : null;
    if (key) highlightIdx(key.dataset.idx);
  });
  stack.addEventListener("mouseleave", () => highlightIdx(null));
  stack.addEventListener("focusin", (e) => {
    const key = e.target.closest ? e.target.closest(".key") : null;
    if (key) highlightIdx(key.dataset.idx);
  });

  const p = document.getElementById("popover");
  p.addEventListener("click", (e) => e.stopPropagation());
  document.addEventListener("click", hidePopover);
  document.addEventListener("keydown", (e) => { if (e.key === "Escape") hidePopover(); });
  window.addEventListener("scroll", queuePosition, true);
  window.addEventListener("resize", queuePosition);
}

// Data is inlined via <script src="keymap-data.js"> so the page opens directly
// from file:// with no server. If that script is missing, tell the user to generate it.
if (window.KEYMAP_DATA) {
  init(window.KEYMAP_DATA);
} else {
  document.getElementById("layers-stack").innerHTML =
    `<p class="error">keymap-data.js not found. Run ` +
    `<code>python3 build_data.py</code> in this folder first, then reload.</p>`;
}
