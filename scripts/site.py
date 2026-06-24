import json
import re
from datetime import datetime, timezone
from pathlib import Path

from .paths import CONTESTS_DIR, PROBLEMS_DIR, ROOT_DIR
from .ratings import RATING_BUCKETS, UNRATED_BUCKET, rating_bucket, ratings_map

REPO_ROOT = Path(ROOT_DIR)
PROBLEMS_ROOT = Path(PROBLEMS_DIR)
CONTESTS_ROOT = Path(CONTESTS_DIR)
CODEBOOK_ROOT = REPO_ROOT / "codebook"
DOCS_ROOT = REPO_ROOT / "docs"
ASSETS_ROOT = DOCS_ROOT / "assets"
DATA_PATH = ASSETS_ROOT / "data.js"
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


def _read_existing_site_ratings() -> dict[int, float]:
    ratings: dict[int, float] = {}
    if not DATA_PATH.exists():
        return ratings

    prefix = "window.LEETCODE_IO_DATA = "
    raw = DATA_PATH.read_text(encoding="utf-8", errors="replace").strip()
    if not raw.startswith(prefix) or not raw.endswith(";"):
        return ratings

    try:
        data = json.loads(raw[len(prefix) : -1])
    except json.JSONDecodeError:
        return ratings

    for item in [*data.get("problems", []), *data.get("contests", [])]:
        problem_id = item.get("id")
        rating = item.get("rating")
        if isinstance(problem_id, int) and isinstance(rating, (int, float)):
            ratings[problem_id] = float(rating)

    return ratings


def _rating_source() -> dict[int, float]:
    try:
        return ratings_map()
    except Exception as exc:
        fallback = _read_existing_site_ratings()
        if fallback:
            print(f"Warning: using existing site ratings because rating fetch failed: {exc}")
            return fallback
        raise


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


def _collect_codebook() -> list[dict]:
    if not CODEBOOK_ROOT.exists():
        return []

    entries = []
    for path in sorted(CODEBOOK_ROOT.rglob("*.cpp")):
        if not path.is_file():
            continue
        relative_parts = path.relative_to(CODEBOOK_ROOT).parts
        group = relative_parts[0] if len(relative_parts) > 1 else "root"
        entries.append(
            {
                "key": f"codebook:{_relative_path(path)}",
                "title": path.name,
                "group": group,
                "path": _relative_path(path),
                "githubUrl": _github_url(path),
                "code": _read_code(path),
            }
        )
    entries.sort(key=lambda item: (item["group"].lower(), item["title"].lower()))
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
    ratings = _rating_source()
    problems = _collect_problems(ratings)
    contests = _collect_contests(ratings)
    codebook = _collect_codebook()
    contest_names = sorted({entry["contest"] for entry in contests})

    return {
        "generatedAt": datetime.now(timezone.utc).isoformat(timespec="seconds"),
        "summary": {
            "problemCount": len(problems),
            "contestSolutionCount": len(contests),
            "contestCount": len(contest_names),
            "codebookCount": len(codebook),
            "ratedProblemCount": sum(1 for item in problems if item["rating"] is not None),
        },
        "tiers": _tier_summary(problems),
        "problems": problems,
        "contests": contests,
        "codebook": codebook,
    }


def update_site_data() -> None:
    ASSETS_ROOT.mkdir(parents=True, exist_ok=True)
    data = build_site_data()
    output = "window.LEETCODE_IO_DATA = "
    output += json.dumps(data, ensure_ascii=True, separators=(",", ":"))
    output += ";\n"
    DATA_PATH.write_text(output, encoding="utf-8")
    print(f"Updated {DATA_PATH}")


def update_site() -> None:
    DOCS_ROOT.mkdir(exist_ok=True)
    ASSETS_ROOT.mkdir(parents=True, exist_ok=True)
    (DOCS_ROOT / ".nojekyll").write_text("", encoding="utf-8")
    update_site_data()
