(function () {
  "use strict";

  const data = window.LEETCODE_IO_DATA || {
    summary: {},
    tiers: [],
    problems: [],
    contests: [],
  };

  const state = {
    view: "problems",
    search: "",
    tier: "all",
    contestType: "all",
    openKey: null,
    page: 1,
    pageSize: 100,
    sort: {
      problems: { key: "id", dir: "desc" },
      contests: { key: "contestNumber", dir: "desc" },
    },
  };

  const els = {
    tabs: Array.from(document.querySelectorAll("[data-view]")),
    search: document.getElementById("search"),
    tier: document.getElementById("tier-filter"),
    contestType: document.getElementById("contest-filter"),
    tierControl: document.querySelector('[data-control="tier"]'),
    contestControl: document.querySelector('[data-control="contest-type"]'),
    head: document.getElementById("table-head"),
    body: document.getElementById("table-body"),
    count: document.getElementById("result-count"),
    pageStatus: document.getElementById("page-status"),
    prevPage: document.getElementById("prev-page"),
    nextPage: document.getElementById("next-page"),
    updatedAt: document.getElementById("updated-at"),
    statProblems: document.getElementById("stat-problems"),
    statRated: document.getElementById("stat-rated"),
    statContests: document.getElementById("stat-contests"),
    statContestCode: document.getElementById("stat-contest-code"),
  };

  const columnSets = {
    problems: [
      ["rating", "Rating"],
      ["tier", "Tier"],
      ["id", "ID"],
      ["title", "Title"],
      ["actions", "Links"],
    ],
    contests: [
      ["contestNumber", "Contest"],
      ["rating", "Rating"],
      ["id", "ID"],
      ["title", "Title"],
      ["actions", "Links"],
    ],
  };

  const cppKeywords = new Set([
    "alignas",
    "alignof",
    "and",
    "and_eq",
    "asm",
    "auto",
    "bitand",
    "bitor",
    "bool",
    "break",
    "case",
    "catch",
    "char",
    "char16_t",
    "char32_t",
    "class",
    "compl",
    "concept",
    "const",
    "constexpr",
    "const_cast",
    "continue",
    "decltype",
    "default",
    "delete",
    "do",
    "double",
    "dynamic_cast",
    "else",
    "enum",
    "explicit",
    "export",
    "extern",
    "false",
    "float",
    "for",
    "friend",
    "goto",
    "if",
    "inline",
    "int",
    "long",
    "mutable",
    "namespace",
    "new",
    "noexcept",
    "not",
    "not_eq",
    "nullptr",
    "operator",
    "or",
    "or_eq",
    "private",
    "protected",
    "public",
    "register",
    "reinterpret_cast",
    "requires",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "static_assert",
    "static_cast",
    "struct",
    "switch",
    "template",
    "this",
    "thread_local",
    "throw",
    "true",
    "try",
    "typedef",
    "typeid",
    "typename",
    "union",
    "unsigned",
    "using",
    "virtual",
    "void",
    "volatile",
    "wchar_t",
    "while",
    "xor",
    "xor_eq",
  ]);

  const cppTokenPattern =
    /\/\*[\s\S]*?\*\/|\/\/[^\n]*|"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'|^\s*#[^\n]*|\b(?:0x[\da-fA-F]+|\d+(?:\.\d+)?(?:[eE][+-]?\d+)?)(?:[uUlLfF]+)?\b|\b[a-zA-Z_]\w*\b/gm;

  function escapeHtml(value) {
    return String(value)
      .replace(/&/g, "&amp;")
      .replace(/</g, "&lt;")
      .replace(/>/g, "&gt;")
      .replace(/"/g, "&quot;")
      .replace(/'/g, "&#039;");
  }

  function normalize(value) {
    return String(value || "").toLowerCase();
  }

  function formatNumber(value) {
    return new Intl.NumberFormat("en-US").format(value || 0);
  }

  function formatDate(value) {
    if (!value) {
      return "";
    }
    const date = new Date(value);
    if (Number.isNaN(date.getTime())) {
      return "";
    }
    return `Updated ${date.toLocaleString()}`;
  }

  function sortGlyph(key) {
    const sort = state.sort[state.view];
    if (sort.key !== key) {
      return "";
    }
    return sort.dir === "asc" ? " ^" : " v";
  }

  function rowSearchText(item) {
    return normalize(
      [
        item.qid,
        item.title,
        item.ratingLabel,
        item.tier,
        item.tierLabel,
        item.path,
        item.contest,
        item.contestType,
      ].join(" ")
    );
  }

  function highlightCode(code) {
    let output = "";
    let lastIndex = 0;
    const source = String(code || "");

    source.replace(cppTokenPattern, (token, offset) => {
      output += escapeHtml(source.slice(lastIndex, offset));
      output += highlightToken(token);
      lastIndex = offset + token.length;
      return token;
    });

    output += escapeHtml(source.slice(lastIndex));
    return output;
  }

  function highlightToken(token) {
    const trimmed = token.trimStart();
    let tokenClass = "";

    if (token.startsWith("//") || token.startsWith("/*")) {
      tokenClass = "code-comment";
    } else if (token.startsWith('"') || token.startsWith("'")) {
      tokenClass = "code-string";
    } else if (trimmed.startsWith("#")) {
      tokenClass = "code-preprocessor";
    } else if (/^(?:0x[\da-fA-F]+|\d)/.test(token)) {
      tokenClass = "code-number";
    } else if (cppKeywords.has(token)) {
      tokenClass = "code-keyword";
    }

    const escaped = escapeHtml(token);
    return tokenClass ? `<span class="${tokenClass}">${escaped}</span>` : escaped;
  }

  function filterRows(rows) {
    const query = normalize(state.search.trim());
    return rows.filter((item) => {
      if (query && !rowSearchText(item).includes(query)) {
        return false;
      }
      if (state.view === "problems" && state.tier !== "all" && item.tierSlug !== state.tier) {
        return false;
      }
      if (
        state.view === "contests" &&
        state.contestType !== "all" &&
        item.contestType !== state.contestType
      ) {
        return false;
      }
      return true;
    });
  }

  function sortValue(item, key) {
    if (key === "rating") {
      return item.rating == null ? Number.POSITIVE_INFINITY : item.rating;
    }
    if (key === "contestNumber") {
      return item.contestNumber == null ? -1 : item.contestNumber;
    }
    return item[key] == null ? "" : item[key];
  }

  function compareRows(a, b) {
    const sort = state.sort[state.view];
    const av = sortValue(a, sort.key);
    const bv = sortValue(b, sort.key);
    let result = 0;

    if (typeof av === "number" && typeof bv === "number") {
      result = av - bv;
    } else {
      result = String(av).localeCompare(String(bv), undefined, {
        numeric: true,
        sensitivity: "base",
      });
    }

    if (result === 0) {
      result = a.id - b.id;
    }

    return sort.dir === "asc" ? result : -result;
  }

  function tierClass(item) {
    return `pill tier-${item.tierSlug || "unrated"}`;
  }

  function contestLabel(item) {
    const prefix = item.contestType === "biweekly" ? "Biweekly" : "Weekly";
    return `${prefix} ${item.contestNumber || ""}`.trim();
  }

  function contestClass(item) {
    const type = item.contestType === "biweekly" ? "biweekly" : "weekly";
    const tone = item.contestNumber == null ? 0 : item.contestNumber % 4;
    return `pill contest contest-${type} contest-tone-${tone}`;
  }

  function renderHead() {
    const cells = columnSets[state.view]
      .map(([key, label]) => {
        if (key === "actions") {
          return `<th>${label}</th>`;
        }
        return `<th><button type="button" data-sort="${key}">${label}${sortGlyph(key)}</button></th>`;
      })
      .join("");
    els.head.innerHTML = `<tr>${cells}</tr>`;
  }

  function actionCell(item) {
    const isOpen = state.openKey === item.key;
    const contestLink =
      state.view === "contests" && item.contestUrl
        ? `<a class="button" href="${escapeHtml(item.contestUrl)}" target="_blank" rel="noreferrer">Contest</a>`
        : "";
    return `
      <div class="action-row">
        <a class="button" href="${escapeHtml(item.leetcodeUrl)}" target="_blank" rel="noreferrer">LC</a>
        ${contestLink}
        <a class="button" href="${escapeHtml(item.githubUrl)}" target="_blank" rel="noreferrer">GitHub</a>
        <button class="button primary" type="button" data-toggle-code="${escapeHtml(item.key)}">
          ${isOpen ? "Hide" : "Code"}
        </button>
      </div>
    `;
  }

  function problemRow(item) {
    const open = state.openKey === item.key ? " is-open" : "";
    return `
      <tr class="${open}">
        <td class="num">${escapeHtml(item.ratingLabel)}</td>
        <td><span class="${tierClass(item)}">${escapeHtml(item.tier)}</span></td>
        <td class="num">${escapeHtml(item.qid)}</td>
        <td class="title-cell">${escapeHtml(item.title)}</td>
        <td>${actionCell(item)}</td>
      </tr>
      ${codeRow(item, 5)}
    `;
  }

  function contestRow(item) {
    const open = state.openKey === item.key ? " is-open" : "";
    return `
      <tr class="${open}">
        <td><span class="${contestClass(item)}">${escapeHtml(contestLabel(item))}</span></td>
        <td class="num">${escapeHtml(item.ratingLabel)}</td>
        <td class="num">${escapeHtml(item.qid)}</td>
        <td class="title-cell">${escapeHtml(item.title)}</td>
        <td>${actionCell(item)}</td>
      </tr>
      ${codeRow(item, 5)}
    `;
  }

  function codeRow(item, colspan) {
    if (state.openKey !== item.key) {
      return "";
    }
    return `
      <tr class="code-row">
        <td class="code-cell" colspan="${colspan}">
          <div class="code-panel">
            <div class="code-toolbar">
              <span>${escapeHtml(item.path)}</span>
              <button class="button" type="button" data-copy-code="${escapeHtml(item.key)}">Copy</button>
            </div>
            <pre><code>${highlightCode(item.code || "")}</code></pre>
          </div>
        </td>
      </tr>
    `;
  }

  function renderRows() {
    const source = state.view === "problems" ? data.problems : data.contests;
    const rows = filterRows(source).sort(compareRows);
    const totalPages = Math.max(1, Math.ceil(rows.length / state.pageSize));
    state.page = Math.min(Math.max(1, state.page), totalPages);
    const start = (state.page - 1) * state.pageSize;
    const pageRows = rows.slice(start, start + state.pageSize);

    els.count.textContent = `${formatNumber(rows.length)} rows`;
    els.pageStatus.textContent = `Page ${state.page} / ${totalPages}`;
    els.prevPage.disabled = state.page <= 1;
    els.nextPage.disabled = state.page >= totalPages;

    if (!rows.length) {
      els.body.innerHTML = `<tr><td class="empty" colspan="5">No matching rows.</td></tr>`;
      return;
    }

    els.body.innerHTML = pageRows.map(state.view === "problems" ? problemRow : contestRow).join("");
  }

  function renderControls() {
    const isProblems = state.view === "problems";
    els.tierControl.hidden = !isProblems;
    els.contestControl.hidden = isProblems;
  }

  function renderTabs() {
    els.tabs.forEach((tab) => {
      tab.classList.toggle("is-active", tab.dataset.view === state.view);
    });
  }

  function render() {
    renderTabs();
    renderControls();
    renderHead();
    renderRows();
  }

  function setView(view) {
    state.view = view === "contests" ? "contests" : "problems";
    state.openKey = null;
    state.page = 1;
    render();
  }

  function applyHash() {
    const hash = window.location.hash.replace(/^#\/?/, "");
    setView(hash === "contests" ? "contests" : "problems");
  }

  function populateTierFilter() {
    data.tiers.forEach((tier) => {
      const option = document.createElement("option");
      option.value = tier.slug;
      option.textContent = `${tier.label} (${tier.count})`;
      els.tier.appendChild(option);
    });
  }

  function bindEvents() {
    els.tabs.forEach((tab) => {
      tab.addEventListener("click", () => {
        const nextView = tab.dataset.view;
        if (nextView && nextView !== state.view) {
          window.location.hash = `#/${nextView}`;
        }
      });
    });

    els.search.addEventListener("input", () => {
      state.search = els.search.value;
      state.openKey = null;
      state.page = 1;
      renderRows();
    });

    els.tier.addEventListener("change", () => {
      state.tier = els.tier.value;
      state.openKey = null;
      state.page = 1;
      renderRows();
    });

    els.contestType.addEventListener("change", () => {
      state.contestType = els.contestType.value;
      state.openKey = null;
      state.page = 1;
      renderRows();
    });

    els.prevPage.addEventListener("click", () => {
      state.page -= 1;
      state.openKey = null;
      renderRows();
    });

    els.nextPage.addEventListener("click", () => {
      state.page += 1;
      state.openKey = null;
      renderRows();
    });

    els.head.addEventListener("click", (event) => {
      const button = event.target.closest("[data-sort]");
      if (!button) {
        return;
      }
      const key = button.dataset.sort;
      const sort = state.sort[state.view];
      if (sort.key === key) {
        sort.dir = sort.dir === "asc" ? "desc" : "asc";
      } else {
        sort.key = key;
        sort.dir = key === "contestNumber" || key === "id" ? "desc" : "asc";
      }
      state.openKey = null;
      state.page = 1;
      render();
    });

    els.body.addEventListener("click", (event) => {
      const toggle = event.target.closest("[data-toggle-code]");
      if (toggle) {
        const key = toggle.dataset.toggleCode;
        state.openKey = state.openKey === key ? null : key;
        renderRows();
        return;
      }

      const copy = event.target.closest("[data-copy-code]");
      if (copy) {
        const key = copy.dataset.copyCode;
        const rows = state.view === "problems" ? data.problems : data.contests;
        const item = rows.find((row) => row.key === key);
        if (!item || !navigator.clipboard) {
          return;
        }
        navigator.clipboard.writeText(item.code || "").then(() => {
          copy.textContent = "Copied";
          window.setTimeout(() => {
            copy.textContent = "Copy";
          }, 1200);
        });
      }
    });

    window.addEventListener("hashchange", applyHash);
  }

  function boot() {
    populateTierFilter();
    els.statProblems.textContent = formatNumber(data.summary.problemCount);
    els.statRated.textContent = formatNumber(data.summary.ratedProblemCount);
    els.statContests.textContent = formatNumber(data.summary.contestCount);
    els.statContestCode.textContent = formatNumber(data.summary.contestSolutionCount);
    els.updatedAt.textContent = formatDate(data.generatedAt);
    bindEvents();
    applyHash();
  }

  boot();
})();
