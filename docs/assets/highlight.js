(function () {
  "use strict";

  const cppKeywords = new Set([
    "alignas",
    "alignof",
    "and",
    "and_eq",
    "asm",
    "auto",
    "bitand",
    "bitor",
    "bool",
    "break",
    "case",
    "catch",
    "char",
    "char16_t",
    "char32_t",
    "class",
    "compl",
    "concept",
    "const",
    "constexpr",
    "const_cast",
    "continue",
    "decltype",
    "default",
    "delete",
    "do",
    "double",
    "dynamic_cast",
    "else",
    "enum",
    "explicit",
    "export",
    "extern",
    "false",
    "float",
    "for",
    "friend",
    "goto",
    "if",
    "inline",
    "int",
    "long",
    "mutable",
    "namespace",
    "new",
    "noexcept",
    "not",
    "not_eq",
    "nullptr",
    "operator",
    "or",
    "or_eq",
    "private",
    "protected",
    "public",
    "register",
    "reinterpret_cast",
    "requires",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "static_assert",
    "static_cast",
    "struct",
    "switch",
    "template",
    "this",
    "thread_local",
    "throw",
    "true",
    "try",
    "typedef",
    "typeid",
    "typename",
    "union",
    "unsigned",
    "using",
    "virtual",
    "void",
    "volatile",
    "wchar_t",
    "while",
    "xor",
    "xor_eq",
  ]);

  const cppTokenPattern =
    /\/\*[\s\S]*?\*\/|\/\/[^\n]*|"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'|^\s*#[^\n]*|\b(?:0x[\da-fA-F]+|\d+(?:\.\d+)?(?:[eE][+-]?\d+)?)(?:[uUlLfF]+)?\b|\b[a-zA-Z_]\w*\b/gm;

  function escapeHtml(value) {
    return String(value)
      .replace(/&/g, "&amp;")
      .replace(/</g, "&lt;")
      .replace(/>/g, "&gt;")
      .replace(/"/g, "&quot;")
      .replace(/'/g, "&#039;");
  }

  function highlightCode(code) {
    let output = "";
    let lastIndex = 0;
    const source = String(code || "");

    source.replace(cppTokenPattern, (token, offset) => {
      output += escapeHtml(source.slice(lastIndex, offset));
      output += highlightToken(token);
      lastIndex = offset + token.length;
      return token;
    });

    output += escapeHtml(source.slice(lastIndex));
    return output;
  }

  function highlightToken(token) {
    const trimmed = token.trimStart();
    let tokenClass = "";

    if (token.startsWith("//") || token.startsWith("/*")) {
      tokenClass = "code-comment";
    } else if (token.startsWith('"') || token.startsWith("'")) {
      tokenClass = "code-string";
    } else if (trimmed.startsWith("#")) {
      tokenClass = "code-preprocessor";
    } else if (/^(?:0x[\da-fA-F]+|\d)/.test(token)) {
      tokenClass = "code-number";
    } else if (cppKeywords.has(token)) {
      tokenClass = "code-keyword";
    }

    const escaped = escapeHtml(token);
    return tokenClass ? `<span class="${tokenClass}">${escaped}</span>` : escaped;
  }

  window.CodeTools = {
    escapeHtml,
    highlightCode,
  };
})();
