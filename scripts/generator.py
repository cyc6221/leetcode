import re


def extract_info(filename: str) -> tuple[str | None, str | None, str | None]:
    match = re.match(r"(\d+)\.([a-z0-9\-]+)\.cpp$", filename)
    if not match:
        return None, None, None

    qid = match.group(1)
    kebab_title = match.group(2)
    title_display = kebab_title.replace("-", " ").title()
    return qid, title_display, kebab_title
