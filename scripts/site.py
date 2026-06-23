import json
import re
from datetime import datetime, timezone
from pathlib import Path

from .paths import CONTESTS_DIR, PROBLEMS_DIR, ROOT_DIR
from .ratings import RATING_BUCKETS, UNRATED_BUCKET, rating_bucket

REPO_ROOT = Path(ROOT_DIR)
PROBLEMS_ROOT = Path(PROBLEMS_DIR)
CONTESTS_ROOT = Path(CONTESTS_DIR)
DOCS_ROOT = REPO_ROOT / "docs"
ASSETS_ROOT = DOCS_ROOT / "assets"
GITHUB_BLOB_BASE = "https://github.com/cyc6221/leetcode/blob/main"


def _display_title(kebab_title: str) -> str:
    roman = {"i", "ii", "iii", "iv", "v", "vi", "vii", "viii", "ix", "x"}
    words = []
    for word in kebab_title.split("-"):
        if word in roman:
            words.append(word.upper())
        elif len(word) == 1:
            words.append(word.upper())
        else:
            words.append(word.capitalize())
    return " ".join(words)


def _extract_site_info(filename: str) -> tuple[str | None, str | None, str | None]:
    match = re.match(r"(\d+)\.([A-Za-z0-9\-_]+)\.cpp$", filename)
    if not match:
        return None, None, None

    qid = match.group(1)
    body = match.group(2)
    kebab_title, _, suffix = body.partition("_")
    kebab_title = kebab_title.lower()
    title = _display_title(kebab_title)
    if suffix:
        title = f"{title} ({suffix.upper()})"
    return qid, title, kebab_title


def _parse_rating(raw: str) -> float | None:
    raw = raw.strip()
    if raw in {"", "-"}:
        return None
    try:
        return float(raw)
    except ValueError:
        return None


def _read_table_rows(path: Path) -> list[list[str]]:
    if not path.exists():
        return []

    rows = []
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        stripped = line.strip()
        if not stripped.startswith("|") or stripped.startswith("|:") or stripped.startswith("|-"):
            continue
        columns = [column.strip() for column in stripped.strip("|").split("|")]
        rows.append(columns)
    return rows


def _read_cached_ratings() -> dict[int, float]:
    ratings: dict[int, float] = {}

    for columns in _read_table_rows(PROBLEMS_ROOT / "README.md"):
        if len(columns) >= 4 and columns[2].isdigit():
            rating = _parse_rating(columns[0])
            if rating is not None:
                ratings[int(columns[2])] = rating

    for columns in _read_table_rows(CONTESTS_ROOT / "README.md"):
        if len(columns) >= 5 and columns[1].isdigit():
            rating = _parse_rating(columns[3])
            if rating is not None:
                ratings[int(columns[1])] = rating

    return ratings


def _relative_path(path: Path) -> str:
    return path.relative_to(REPO_ROOT).as_posix()


def _leetcode_url(kebab_title: str) -> str:
    return f"https://leetcode.com/problems/{kebab_title}/"


def _github_url(path: Path) -> str:
    return f"{GITHUB_BLOB_BASE}/{_relative_path(path)}"


def _read_code(path: Path) -> str:
    return path.read_text(encoding="utf-8", errors="replace").rstrip() + "\n"


def _problem_payload(path: Path, ratings: dict[int, float]) -> dict | None:
    qid, title, kebab = _extract_site_info(path.name)
    if not qid or not title or not kebab:
        return None

    problem_id = int(qid)
    rating = ratings.get(problem_id)
    slug, _, _, label, tier = rating_bucket(rating)
    return {
        "key": f"problem:{_relative_path(path)}",
        "id": problem_id,
        "qid": qid,
        "title": title,
        "kebab": kebab,
        "rating": rating,
        "ratingLabel": "-" if rating is None else f"{rating:.1f}",
        "tier": tier,
        "tierSlug": slug,
        "tierLabel": label,
        "path": _relative_path(path),
        "leetcodeUrl": _leetcode_url(kebab),
        "githubUrl": _github_url(path),
        "code": _read_code(path),
    }


def _contest_number(contest_name: str) -> int | None:
    match = re.search(r"(\d+)$", contest_name)
    return int(match.group(1)) if match else None


def _contest_type(contest_name: str) -> str:
    lowered = contest_name.lower()
    if lowered.startswith("biweekly"):
        return "biweekly"
    if lowered.startswith("weekly"):
        return "weekly"
    return "other"


def _contest_url(contest_name: str) -> str | None:
    number = _contest_number(contest_name)
    contest_type = _contest_type(contest_name)
    if number is None:
        return None
    if contest_type == "weekly":
        return f"https://leetcode.com/contest/weekly-contest-{number}/"
    if contest_type == "biweekly":
        return f"https://leetcode.com/contest/biweekly-contest-{number}/"
    return None


def _contest_payload(contest_dir: Path, path: Path, ratings: dict[int, float]) -> dict | None:
    base = _problem_payload(path, ratings)
    if base is None:
        return None

    contest = contest_dir.name
    contest_number = _contest_number(contest)
    contest_type = _contest_type(contest)
    base.update(
        {
            "key": f"contest:{_relative_path(path)}",
            "contest": contest,
            "contestType": contest_type,
            "contestNumber": contest_number,
            "contestUrl": _contest_url(contest),
        }
    )
    return base


def _collect_problems(ratings: dict[int, float]) -> list[dict]:
    if not PROBLEMS_ROOT.exists():
        return []

    entries = []
    for path in PROBLEMS_ROOT.rglob("*.cpp"):
        if path.is_file():
            payload = _problem_payload(path, ratings)
            if payload:
                entries.append(payload)

    entries.sort(key=lambda item: (item["rating"] is None, item["rating"] or 999999, item["id"]))
    return entries


def _collect_contests(ratings: dict[int, float]) -> list[dict]:
    if not CONTESTS_ROOT.exists():
        return []

    entries = []
    for contest_dir in sorted(path for path in CONTESTS_ROOT.iterdir() if path.is_dir()):
        for path in sorted(contest_dir.glob("*.cpp")):
            payload = _contest_payload(contest_dir, path, ratings)
            if payload:
                entries.append(payload)

    entries.sort(key=lambda item: (item["contestType"], item["contestNumber"] or -1, item["id"]))
    return entries


def _tier_summary(problems: list[dict]) -> list[dict]:
    buckets = [*RATING_BUCKETS, UNRATED_BUCKET]
    counts = {bucket[0]: 0 for bucket in buckets}
    for problem in problems:
        counts[problem["tierSlug"]] += 1

    return [
        {
            "slug": slug,
            "label": label,
            "tier": tier,
            "count": counts[slug],
        }
        for slug, _, _, label, tier in buckets
    ]


def build_site_data() -> dict:
    ratings = _read_cached_ratings()
    problems = _collect_problems(ratings)
    contests = _collect_contests(ratings)
    contest_names = sorted({entry["contest"] for entry in contests})

    return {
        "generatedAt": datetime.now(timezone.utc).isoformat(timespec="seconds"),
        "summary": {
            "problemCount": len(problems),
            "contestSolutionCount": len(contests),
            "contestCount": len(contest_names),
            "ratedProblemCount": sum(1 for item in problems if item["rating"] is not None),
        },
        "tiers": _tier_summary(problems),
        "problems": problems,
        "contests": contests,
    }


def update_site_data() -> None:
    ASSETS_ROOT.mkdir(parents=True, exist_ok=True)
    data = build_site_data()
    output = "window.LEETCODE_IO_DATA = "
    output += json.dumps(data, ensure_ascii=True, separators=(",", ":"))
    output += ";\n"
    data_path = ASSETS_ROOT / "data.js"
    data_path.write_text(output, encoding="utf-8")
    print(f"Updated {data_path}")


def update_site() -> None:
    DOCS_ROOT.mkdir(exist_ok=True)
    ASSETS_ROOT.mkdir(parents=True, exist_ok=True)
    (DOCS_ROOT / ".nojekyll").write_text("", encoding="utf-8")
    update_site_data()
