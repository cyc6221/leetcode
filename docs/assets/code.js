(function () {
  "use strict";

  const data = window.LEETCODE_IO_DATA || {
    problems: [],
    contests: [],
  };
  const highlightCode = window.CodeTools.highlightCode;

  const els = {
    tableLink: document.getElementById("table-link"),
    meta: document.getElementById("code-meta"),
    title: document.getElementById("code-title"),
    path: document.getElementById("code-path"),
    toolbarPath: document.getElementById("toolbar-path"),
    leetcodeLink: document.getElementById("leetcode-link"),
    githubLink: document.getElementById("github-link"),
    copy: document.getElementById("copy-code"),
    output: document.getElementById("code-output"),
  };

  function allItems() {
    return [...data.problems, ...data.contests];
  }

  function contestLabel(item) {
    if (!item.contest) {
      return "";
    }
    const prefix = item.contestType === "biweekly" ? "Biweekly" : "Weekly";
    return `${prefix} ${item.contestNumber || ""}`.trim();
  }

  function itemMeta(item) {
    const parts = [`#${item.qid}`];
    if (item.ratingLabel && item.ratingLabel !== "-") {
      parts.push(`Rating ${item.ratingLabel}`);
    }
    if (item.tier) {
      parts.push(item.tier);
    }
    const contest = contestLabel(item);
    if (contest) {
      parts.push(contest);
    }
    return parts.join(" / ");
  }

  function tableUrl(item) {
    return item.key.startsWith("contest:") ? "./#/contests" : "./#/problems";
  }

  function renderNotFound() {
    document.title = "Code not found | CYCcc in LeetCode";
    els.meta.textContent = "Missing code";
    els.title.textContent = "Code not found";
    els.path.textContent = "The requested solution key is not available in the generated site data.";
    els.toolbarPath.textContent = "No file selected";
    els.output.textContent = "";
    els.leetcodeLink.hidden = true;
    els.githubLink.hidden = true;
    els.copy.disabled = true;
  }

  function renderItem(item) {
    document.title = `${item.qid}. ${item.title} | CYCcc in LeetCode`;
    els.tableLink.href = tableUrl(item);
    els.meta.textContent = itemMeta(item);
    els.title.textContent = item.title;
    els.path.textContent = item.path;
    els.toolbarPath.textContent = item.path;
    els.leetcodeLink.href = item.leetcodeUrl;
    els.githubLink.href = item.githubUrl;
    els.output.innerHTML = highlightCode(item.code || "");

    els.copy.addEventListener("click", () => {
      if (!navigator.clipboard) {
        return;
      }
      navigator.clipboard.writeText(item.code || "").then(() => {
        els.copy.textContent = "Copied";
        window.setTimeout(() => {
          els.copy.textContent = "Copy";
        }, 1200);
      });
    });
  }

  function boot() {
    const params = new URLSearchParams(window.location.search);
    const key = params.get("key");
    const item = allItems().find((candidate) => candidate.key === key);
    if (!item) {
      renderNotFound();
      return;
    }
    renderItem(item);
  }

  boot();
})();
