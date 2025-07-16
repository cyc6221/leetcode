import os

def list_cpp_files(base_path):
    content = "# Codebook Index\n\n"
    for folder in sorted(os.listdir(base_path)):
        full_path = os.path.join(base_path, folder)
        if os.path.isdir(full_path) and not folder.startswith('.'):
            section = f"## {folder}/\n"
            entries = []
            for file in sorted(os.listdir(full_path)):
                if file.endswith(".cpp"):
                    rel_path = f"./{folder}/{file}"
                    entries.append(f"- [{file}]({rel_path})")
            if entries:
                section += "\n".join(entries) + "\n\n"
                content += section
    return content

def update_readme():
    base_dir = os.path.dirname(os.path.abspath(__file__))
    index_md = list_cpp_files(base_dir)
    readme_path = os.path.join(base_dir, "README.md")
    with open(readme_path, "w", encoding="utf-8") as f:
        f.write(index_md)
    print("✅ Codebook README.md updated successfully.")

if __name__ == "__main__":
    update_readme()
