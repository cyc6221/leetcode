import os
import re
from pathlib import Path

from .paths import CONTESTS_DIR, PROBLEMS_DIR
from .ratings import RATING_BUCKETS, UNRATED_BUCKET, _fmt_rating, rating_bucket, ratings_map

REPO_ROOT = Path(__file__).resolve().parents[1]


def extract_info(filename: str) -> tuple[str | None, str | None, str | None]:
    match = re.match(r"(\d+)\.([a-z0-9\-]+)\.cpp$", filename)
    if not match:
        return None, None, None

    qid = match.group(1)
    kebab_title = match.group(2)
    title_display = kebab_title.replace("-", " ").title()
    return qid, title_display, kebab_title


def _markdown_rel(path: Path, base: Path) -> str:
    rel = os.path.relpath(path.resolve(), base.resolve())
    return "./" + Path(rel).as_posix()


def _leetcode_url(kebab_title: str) -> str:
    return f"https://leetcode.com/problems/{kebab_title}/"


def _problem_entries(base_dir: Path | None = None):
    base_dir = base_dir or Path(PROBLEMS_DIR)
    rating_by_id = ratings_map()
    entries = []

    if not base_dir.exists():
        return entries

    for path in base_dir.rglob("*.cpp"):
        if not path.is_file():
            continue
        qid, title, kebab = extract_info(path.name)
        if not qid or not title or not kebab:
            continue

        problem_id = int(qid)
        rating = rating_by_id.get(problem_id)
        bucket = rating_bucket(rating)
        entries.append(
            {
                "id": problem_id,
                "qid": qid,
                "title": title,
                "kebab": kebab,
                "rating": rating,
                "bucket": bucket,
                "path": path,
            }
        )

    entries.sort(key=lambda item: (item["rating"] is None, item["rating"] or 999999, item["id"]))
    return entries


def generate_problem_summary() -> str:
    buckets = [*RATING_BUCKETS, UNRATED_BUCKET]
    counts = {bucket[0]: 0 for bucket in buckets}

    for entry in _problem_entries():
        counts[entry["bucket"][0]] += 1

    lines = [
        "## Problem Count Summary",
        "",
        "| Rating Range | Tier | Count |",
        "|--------------|------|------:|",
    ]
    total = 0
    for slug, _, _, label, tier in buckets:
        count = counts[slug]
        total += count
        lines.append(f"| {label} | {tier} | {count} |")
    lines.append(f"| **Total** |  | **{total}** |")
    return "\n".join(lines)


def generate_problem_table(link_base: Path | None = None) -> str:
    link_base = link_base or REPO_ROOT
    lines = [
        "## Completed Problem List",
        "",
        "| Rating | Tier | ID | Title | Link | Code |",
        "|:------:|------|:--:|-------|:----:|:----:|",
    ]

    for entry in _problem_entries():
        _, _, _, _, tier = entry["bucket"]
        code_path = _markdown_rel(entry["path"], link_base)
        code_link = f"[View]({code_path})"
        lc_link = f"[Link]({_leetcode_url(entry['kebab'])})"
        lines.append(
            f"| {_fmt_rating(entry['rating'])} | {tier} | {entry['qid']} | "
            f"{entry['title']} | {lc_link} | {code_link} |"
        )

    return "\n".join(lines)


def generate_table_contest(contest: str) -> str:
    contest_path = Path(CONTESTS_DIR) / contest
    lines = [
        "## Problem List",
        "",
        "| ID | Title | Rating | Link | Code |",
        "|:--:|-------|:------:|:----:|:----:|",
    ]

    entries = []
    rating_by_id = ratings_map()

    for path in contest_path.glob("*.cpp"):
        qid, title, kebab = extract_info(path.name)
        if not qid or not title or not kebab:
            continue
        problem_id = int(qid)
        entries.append((problem_id, qid, title, kebab, rating_by_id.get(problem_id), path))

    entries.sort()

    for _, qid, title, kebab, rating, path in entries:
        code_link = f"[View]({_markdown_rel(path, contest_path)})"
        lc_link = f"[Link]({_leetcode_url(kebab)})"
        lines.append(f"| {qid} | {title} | {_fmt_rating(rating)} | {lc_link} | {code_link} |")

    return "\n".join(lines)


def generate_table_all_contest() -> str:
    contest_root = Path(CONTESTS_DIR)
    lines = [
        "## Problem List",
        "",
        "| Contest | ID | Title | Rating | Link | Code |",
        "|:-------:|:--:|-------|:------:|:----:|:----:|",
    ]

    entries = []
    rating_by_id = ratings_map()

    for contest_dir in contest_root.iterdir():
        if not contest_dir.is_dir():
            continue
        for path in contest_dir.glob("*.cpp"):
            qid, title, kebab = extract_info(path.name)
            if not qid or not title or not kebab:
                continue
            problem_id = int(qid)
            entries.append((problem_id, contest_dir.name, qid, title, kebab, rating_by_id.get(problem_id), path))

    entries.sort()

    for _, contest, qid, title, kebab, rating, path in entries:
        code_link = f"[View]({_markdown_rel(path, contest_root)})"
        lc_link = f"[Link]({_leetcode_url(kebab)})"
        lines.append(f"| {contest} | {qid} | {title} | {_fmt_rating(rating)} | {lc_link} | {code_link} |")

    return "\n".join(lines)
