import csv
import io
import urllib.request

RATINGS_URL = "https://raw.githubusercontent.com/zerotrac/leetcode_problem_rating/main/ratings.txt"

RATING_BUCKETS = [
    ("0000-1199-newbie", None, 1200, "< 1200", "Newbie"),
    ("1200-1399-pupil", 1200, 1400, "1200-1399", "Pupil"),
    ("1400-1599-specialist", 1400, 1600, "1400-1599", "Specialist"),
    ("1600-1899-expert", 1600, 1900, "1600-1899", "Expert"),
    ("1900-2099-candidate-master", 1900, 2100, "1900-2099", "Candidate Master"),
    ("2100-2299-master", 2100, 2300, "2100-2299", "Master"),
    ("2300-2399-international-master", 2300, 2400, "2300-2399", "International Master"),
    ("2400-2599-grandmaster", 2400, 2600, "2400-2599", "Grandmaster"),
    ("2600-2999-international-grandmaster", 2600, 3000, "2600-2999", "International Grandmaster"),
    ("3000-3999-legendary-grandmaster", 3000, 4000, "3000-3999", "Legendary Grandmaster"),
    ("4000-plus-eponym", 4000, None, ">= 4000", "Eponym"),
]

UNRATED_BUCKET = ("unrated", None, None, "Unrated", "Unrated")


def get_ratings_map(url: str = RATINGS_URL) -> dict[int, float]:
    with urllib.request.urlopen(url) as resp:
        text = resp.read().decode("utf-8", errors="replace")

    reader = csv.DictReader(io.StringIO(text), delimiter="\t")
    if not reader.fieldnames:
        raise ValueError("ratings.txt does not contain a header row")

    lower = {column.lower(): column for column in reader.fieldnames}
    id_col = next((lower.get(key) for key in ("id", "problem id", "problem_id", "problemid")), None)
    rating_col = next((lower.get(key) for key in ("rating", "difficulty", "difficulty_rating")), None)
    if not id_col or not rating_col:
        raise ValueError(f"ratings.txt is missing ID or rating columns: {reader.fieldnames}")

    out: dict[int, float] = {}
    for row in reader:
        id_raw = (row.get(id_col) or "").strip()
        rating_raw = (row.get(rating_col) or "").strip()
        try:
            problem_id = int(id_raw)
            rating = float(rating_raw)
        except ValueError:
            continue
        out[problem_id] = max(out.get(problem_id, float("-inf")), rating)
    return out


_RATINGS_CACHE: dict[int, float] | None = None


def ratings_map() -> dict[int, float]:
    global _RATINGS_CACHE
    if _RATINGS_CACHE is None:
        _RATINGS_CACHE = get_ratings_map()
    return _RATINGS_CACHE


def rating_bucket(rating: float | None) -> tuple[str, float | None, float | None, str, str]:
    if rating is None:
        return UNRATED_BUCKET

    for bucket in RATING_BUCKETS:
        _, low, high, _, _ = bucket
        if (low is None or rating >= low) and (high is None or rating < high):
            return bucket
    return UNRATED_BUCKET


def rating_bucket_slug(rating: float | None) -> str:
    return rating_bucket(rating)[0]


def _fmt_rating(rating: float | None) -> str:
    if rating is None:
        return "-"
    if abs(rating - int(rating)) < 1e-9:
        return str(int(rating))
    return f"{rating:.1f}"
