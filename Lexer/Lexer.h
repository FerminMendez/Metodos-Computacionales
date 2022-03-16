

#ifndef INCLUDE_LEXER
#define INCLUDE_LEXER

#include <string>

using namespace std;

class Token {
 public:
  enum class Kind {
    Entero,
    Decimal,
    ID,
    Operador, 
    Simbolo_e,
    Comentario,
    No_valido,
    Fin,
  };

  Token(Kind kind) noexcept : m_kind{kind} {}

  Token(Kind kind, const char* beg, size_t len) noexcept
      : m_kind{kind}, m_lexeme(beg, len) {}

  Token(Kind kind, const char* beg, const char* end) noexcept
      : m_kind{kind}, m_lexeme(beg, distance(beg, end)) {}

  Kind kind() const noexcept { return m_kind; }

  void kind(Kind kind) noexcept { m_kind = kind; }

  bool is(Kind kind) const noexcept { return m_kind == kind; }

  bool is_not(Kind kind) const noexcept { return m_kind != kind; }

  bool is_one_of(Kind k1, Kind k2) const noexcept { return is(k1) || is(k2); }

  template <typename... Ts>
  bool is_one_of(Kind k1, Kind k2, Ts... ks) const noexcept {
    return is(k1) || is_one_of(k2, ks...);
  }

  string_view lexeme() const noexcept { return m_lexeme; }

  void lexeme(string_view lexeme) noexcept {
    m_lexeme = move(lexeme);
  }

 private:
  Kind m_kind{};
  string_view m_lexeme{};
};

class Lexer {
 public:
  Lexer(const char* beg) noexcept : m_beg{beg} {}

  Token next() noexcept;

 private:
  Token identificador() noexcept;
  Token number() noexcept;
  Token decimal() noexcept;
  Token comentario() noexcept;
  Token operador() noexcept;
  Token simbolo_e() noexcept;
  Token atom(Token::Kind) noexcept;

  char peek() const noexcept { return *m_beg; }
  char get() noexcept { return *m_beg++; }

  const char* m_beg = nullptr;
};

bool is_space(char c) noexcept {
  switch (c) {
    case ' ':
    case '\t':
    case '\r':
    case '\n':
      return true;
    default:
      return false;
  }
}

bool is_digit(char c) noexcept {
  switch (c) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return true;
    default:
      return false;
  }
}

bool is_identifier_char(char c) noexcept {
  switch (c) {
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '_':
      return true;
    default:
      return false;
  }
}

Token Lexer::atom(Token::Kind kind) noexcept { return Token(kind, m_beg++, 1); }

Token Lexer::next() noexcept {
  while (is_space(peek())) get();

  switch (peek()) {
    case '\0':
      return Token(Token::Kind::Fin, m_beg, 1);
    default:
      return atom(Token::Kind::No_valido);
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
      return identificador();
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return number();
    case '(':
      return atom(Token::Kind::Simbolo_e);
    case ')':
      return atom(Token::Kind::Simbolo_e);
    case '=':
      return atom(Token::Kind::Operador);
    case '+':
      return atom(Token::Kind::Operador);
    case '-':
      return atom(Token::Kind::Operador);
    case '*':
      return atom(Token::Kind::Operador);
    case '/':
      return comentario();
    case '.':
      return atom(Token::Kind::Decimal);
  }
}

Token Lexer::identificador() noexcept {
  const char* start = m_beg;
  get();
  while (is_identifier_char(peek())) get();
  return Token(Token::Kind::ID, start, m_beg);
}

Token Lexer::number() noexcept {
  const char* start = m_beg;
  get();
  while (is_digit(peek())) get();
  return Token(Token::Kind::Entero, start, m_beg);
}

Token Lexer::comentario() noexcept {
  const char* start = m_beg;
  get();
  if (peek() == '/') {
    get();
    start = m_beg;
    while (peek() != '\0') {
      if (get() == '\n') {
        return Token(Token::Kind::Comentario, start,
                     std::distance(start, m_beg) - 1);
      }
    }
    return Token(Token::Kind::No_valido, m_beg, 1);
  } else {
    return Token(Token::Kind::No_valido, start, 1);
  }
}

#include <iomanip>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Token::Kind& kind) {
  static const char* const names[]{
      "Entero", "Identificador",  "Operador", "Símbolo especial", "Decimal",    
     "Comentario", "Fin","Inválido",
  };
  return os << names[static_cast<int>(kind)];
}

int main() {
  auto code =
      "x = 2\n"
      "// This is a comment.\n"
      "var x\n"
      "var y\n"
      "var f = function(x, y) { sin(x) * sin(y) + x * y; }\n"
      "der(f, x)\n"
      "var g = function(x, y) { 2 * (x + der(f, y)); } // der(f, y) is a "
      "matrix\n"
      "var r{3}; // Vector of three elements\n"
      "var J{12, 12}; // Matrix of 12x12 elements\n"
      "var dot = function(u{:}, v{:}) -> scalar {\n"
      "          return u[i] * v[i]; // Einstein notation\n"
      "}\n"
      "var norm = function(u{:}) -> scalar { return sqrt(dot(u, u)); }\n"
      "<end>";

  Lexer lex(code);
  for (auto token = lex.next();
       not token.is_one_of(Token::Kind::Fin, Token::Kind::No_valido);
       token = lex.next()) {
    std::cout << std::setw(12) << token.kind() << " |" << token.lexeme()
              << "|\n";
  }
}

#endif