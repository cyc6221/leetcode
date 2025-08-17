import re

def replace_block(content: str, start_tag: str, end_tag: str, new_block: str) -> str:
    return re.sub(
        f"{re.escape(start_tag)}.*?{re.escape(end_tag)}",
        f"{start_tag}\n{new_block}\n{end_tag}",
        content,
        flags=re.DOTALL
    )

def replace_block(content: str, start_tag: str, end_tag: str, new_block: str) -> str:
    pattern = f"{re.escape(start_tag)}.*?{re.escape(end_tag)}"
    return re.sub(
        pattern,
        lambda m: f"{start_tag}\n{new_block}\n{end_tag}",
        content,
        flags=re.DOTALL
    )
