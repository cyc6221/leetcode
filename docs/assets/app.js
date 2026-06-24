(function () {
  "use strict";

  const data = window.LEETCODE_IO_DATA || {
    summary: {},
    tiers: [],
    problems: [],
    contests: [],
    codebook: [],
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
      codebook: { key: "group", dir: "asc" },
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
    statCodebook: document.getElementById("stat-codebook"),
    summaryBody: document.getElementById("summary-body"),
    summaryTotal: document.getElementById("summary-total"),
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
    codebook: [
      ["group", "Group"],
      ["title", "Snippet"],
      ["actions", "Links"],
    ],
  };

  const escapeHtml = window.CodeTools.escapeHtml;
  const highlightCode = window.CodeTools.highlightCode;

  function sourceRows() {
    if (state.view === "contests") {
      return data.contests || [];
    }
    if (state.view === "codebook") {
      return data.codebook || [];
    }
    return data.problems || [];
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
        item.group,
      ].join(" ")
    );
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

    if (result === 0 && typeof a.id === "number" && typeof b.id === "number") {
      result = a.id - b.id;
    } else if (result === 0) {
      result = String(a.title || a.path || "").localeCompare(String(b.title || b.path || ""), undefined, {
        numeric: true,
        sensitivity: "base",
      });
    }

    return sort.dir === "asc" ? result : -result;
  }

  function tierClass(item) {
    return `pill tier-${item.tierSlug || "unrated"}`;
  }

  function tierSummaryClass(tier) {
    return `pill tier-${tier.slug || "unrated"}`;
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

  function codeViewUrl(item) {
    const params = new URLSearchParams({ key: item.key });
    return `./code.html?${params.toString()}`;
  }

  function scrollRowToTop(key) {
    window.requestAnimationFrame(() => {
      const row = Array.from(els.body.querySelectorAll(".data-row")).find(
        (candidate) => candidate.dataset.rowKey === key
      );
      if (row) {
        row.scrollIntoView({ block: "start", behavior: "smooth" });
      }
    });
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

  function renderSummary() {
    const total = data.tiers.reduce((sum, tier) => sum + (tier.count || 0), 0);
    els.summaryTotal.textContent = `${formatNumber(total)} total`;
    els.summaryBody.innerHTML = data.tiers
      .map(
        (tier) => `
          <tr>
            <td>${escapeHtml(tier.label)}</td>
            <td><span class="${tierSummaryClass(tier)}">${escapeHtml(tier.tier)}</span></td>
            <td class="num">${formatNumber(tier.count)}</td>
          </tr>
        `
      )
      .join("");
  }

  function actionCell(item) {
    const isOpen = state.openKey === item.key;
    const leetcodeLink = item.leetcodeUrl
      ? `<a class="button" href="${escapeHtml(item.leetcodeUrl)}" target="_blank" rel="noreferrer">LC</a>`
      : "";
    const contestLink =
      state.view === "contests" && item.contestUrl
        ? `<a class="button" href="${escapeHtml(item.contestUrl)}" target="_blank" rel="noreferrer">Contest</a>`
        : "";
    return `
      <div class="action-row">
        ${leetcodeLink}
        ${contestLink}
        <a class="button" href="${escapeHtml(item.githubUrl)}" target="_blank" rel="noreferrer">GitHub</a>
        <a class="button" href="${escapeHtml(codeViewUrl(item))}" target="_blank" rel="noreferrer">Full</a>
        <button class="button primary" type="button" data-toggle-code="${escapeHtml(item.key)}">
          ${isOpen ? "Hide" : "Preview"}
        </button>
      </div>
    `;
  }

  function problemRow(item) {
    const open = state.openKey === item.key ? " is-open" : "";
    return `
      <tr class="data-row${open}" data-row-key="${escapeHtml(item.key)}">
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
      <tr class="data-row${open}" data-row-key="${escapeHtml(item.key)}">
        <td><span class="${contestClass(item)}">${escapeHtml(contestLabel(item))}</span></td>
        <td class="num">${escapeHtml(item.ratingLabel)}</td>
        <td class="num">${escapeHtml(item.qid)}</td>
        <td class="title-cell">${escapeHtml(item.title)}</td>
        <td>${actionCell(item)}</td>
      </tr>
      ${codeRow(item, 5)}
    `;
  }

  function codebookRow(item) {
    const open = state.openKey === item.key ? " is-open" : "";
    return `
      <tr class="data-row${open}" data-row-key="${escapeHtml(item.key)}">
        <td><span class="pill codebook-pill">${escapeHtml(item.group)}</span></td>
        <td class="title-cell">${escapeHtml(item.title)}</td>
        <td>${actionCell(item)}</td>
      </tr>
      ${codeRow(item, 3)}
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
    const rows = filterRows(sourceRows()).sort(compareRows);
    const totalPages = Math.max(1, Math.ceil(rows.length / state.pageSize));
    state.page = Math.min(Math.max(1, state.page), totalPages);
    const start = (state.page - 1) * state.pageSize;
    const pageRows = rows.slice(start, start + state.pageSize);
    const colspan = columnSets[state.view].length;

    els.count.textContent = `${formatNumber(rows.length)} rows`;
    els.pageStatus.textContent = `Page ${state.page} / ${totalPages}`;
    els.prevPage.disabled = state.page <= 1;
    els.nextPage.disabled = state.page >= totalPages;

    if (!rows.length) {
      els.body.innerHTML = `<tr><td class="empty" colspan="${colspan}">No matching rows.</td></tr>`;
      return;
    }

    const renderer =
      state.view === "contests" ? contestRow : state.view === "codebook" ? codebookRow : problemRow;
    els.body.innerHTML = pageRows.map(renderer).join("");
  }

  function renderControls() {
    const isProblems = state.view === "problems";
    const isContests = state.view === "contests";
    els.tierControl.hidden = !isProblems;
    els.contestControl.hidden = !isContests;
    els.search.placeholder = isContests
      ? "ID, title, contest, rating"
      : state.view === "codebook"
        ? "Snippet, group, path"
        : "ID, title, tier, rating";
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
    state.view = ["problems", "contests", "codebook"].includes(view) ? view : "problems";
    state.openKey = null;
    state.page = 1;
    render();
  }

  function applyHash() {
    const hash = window.location.hash.replace(/^#\/?/, "");
    setView(hash);
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
        const shouldOpen = state.openKey !== key;
        state.openKey = shouldOpen ? key : null;
        renderRows();
        if (shouldOpen) {
          scrollRowToTop(key);
        }
        return;
      }

      const copy = event.target.closest("[data-copy-code]");
      if (copy) {
        const key = copy.dataset.copyCode;
        const item = sourceRows().find((row) => row.key === key);
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
    renderSummary();
    populateTierFilter();
    els.statProblems.textContent = formatNumber(data.summary.problemCount);
    els.statRated.textContent = formatNumber(data.summary.ratedProblemCount);
    els.statContests.textContent = formatNumber(data.summary.contestCount);
    els.statContestCode.textContent = formatNumber(data.summary.contestSolutionCount);
    els.statCodebook.textContent = formatNumber(data.summary.codebookCount);
    els.updatedAt.textContent = formatDate(data.generatedAt);
    bindEvents();
    applyHash();
  }

  boot();
})();
