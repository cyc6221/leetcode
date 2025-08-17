import urllib.request
import csv
import io

RATINGS_URL = "https://raw.githubusercontent.com/zerotrac/leetcode_problem_rating/main/ratings.txt"

def get_ratings_map(url: str = RATINGS_URL) -> dict[int, float]:
    """抓取 ratings.txt，回傳 {problem_id: rating} 對照表（標準庫實作）。"""
    with urllib.request.urlopen(url) as resp:
        text = resp.read().decode("utf-8", errors="replace")

    reader = csv.DictReader(io.StringIO(text), delimiter="\t")
    if not reader.fieldnames:
        raise ValueError("ratings.txt 解析不到表頭欄位")

    lower = {c.lower(): c for c in reader.fieldnames}
    id_col = next((lower.get(k) for k in ("id", "problem id", "problem_id", "problemid")), None)
    rating_col = next((lower.get(k) for k in ("rating", "difficulty", "difficulty_rating")), None)
    if not id_col or not rating_col:
        raise ValueError(f"找不到 ID 或 Rating 欄位，表頭為：{reader.fieldnames}")

    out: dict[int, float] = {}
    for row in reader:
        id_raw = (row.get(id_col) or "").strip()
        rating_raw = (row.get(rating_col) or "").strip()
        try:
            pid = int(id_raw)
            r = float(rating_raw)
        except ValueError:
            continue
        # 若同一 ID 出現多筆，取較大的 rating（可依你需求改成首次或均值）
        out[pid] = max(out.get(pid, float("-inf")), r)
    return out

# 簡單快取，避免每次 generate_table 都去抓網路
_RATINGS_CACHE: dict[int, float] | None = None
def ratings_map() -> dict[int, float]:
    global _RATINGS_CACHE
    if _RATINGS_CACHE is None:
        _RATINGS_CACHE = get_ratings_map()
    return _RATINGS_CACHE

def rating_to_emoji(rating):
    if rating >= 4000:
        return "⚫🔴"
    elif rating >= 3000:
        return "🔴⚫"
    elif rating >= 2600:
        return "🔴🔴"
    elif rating >= 2400:
        return "🔴"
    elif rating >= 2300:
        return "🟠🟠"
    elif rating >= 2100:
        return "🟠"
    elif rating >= 1900:
        return "🟣"
    elif rating >= 1600:
        return "🔵"
    elif rating >= 1400:
        return "🔷" 
    elif rating >= 1200:
        return "🟢"
    else:
        return "⚪"

def _fmt_rating(x: float | None) -> str:
    if x is None:
        return "-"
    emoji = rating_to_emoji(x)
    if abs(x - int(x)) < 1e-9:
        return f"{int(x)}<br>{emoji}"
    else:
        return f"{x:.1f}<br>{emoji}"
