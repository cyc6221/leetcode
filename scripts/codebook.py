from pathlib import Path

from .paths import ROOT_DIR

CODEBOOK_ROOT = Path(ROOT_DIR) / "codebook"
SITE_URL = "https://cyc6221.github.io/leetcode/#/codebook"


def codebook_readme_content() -> str:
    return "\n".join(
        [
            "# Codebook",
            "",
            "Reusable algorithm notes and snippets live in this folder.",
            "",
            f"Browse and preview snippets on the site: {SITE_URL}",
            "",
            "The generated snippet list that used to live here has moved to the site.",
            "",
        ]
    )


def update_codebook_readme() -> None:
    readme_path = CODEBOOK_ROOT / "README.md"
    readme_path.write_text(codebook_readme_content(), encoding="utf-8")
    print(f"Updated {readme_path}")
