# Mini Game Script Interpreter

A **domain-specific scripting language interpreter** for building simple **2D grid-based games**, developed as part of the **Compiler Design Lab (CSE332)**.  
This project demonstrates core compiler concepts using **Flex**, **Bison**, and **C**.

---

## 🚀 Features
- Custom game scripting language (DSL)
- Lexical analysis with **Flex**
- LALR(1) parsing with **Bison**
- Semantic actions & runtime execution in **C**
- 10×10 grid-based game world
- Player movement with collision detection
- Objects: obstacles (`#`) and items (`*`)
- Variables, arithmetic expressions
- Control flow: `IF–ENDIF`, `REPEAT–ENDREPEAT`
- Interactive mode & script execution
- Colored terminal output (ANSI)

---

## 🛠 Tech Stack
- **C**
- **Flex (Lexical Analyzer)**
- **Bison (Parser Generator)**
- **GCC**

---


## ▶️ Build & Run
```bash
flex script.l
bison -d script.y
gcc lex.yy.c script.tab.c main.c -o game
./game
```

---

Developed By   
Redwan Rahman
