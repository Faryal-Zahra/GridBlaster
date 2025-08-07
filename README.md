# GridBlaster – A Modern Minesweeper in OOP
A console-based OOP Minesweeper game built in C++ with classic logic, modern structure, and modular code.
# 🧨 GridBlaster

**GridBlaster** is a terminal-based C++ game inspired by the classic Minesweeper. With multiple difficulty levels, flagging, scoring, and a timer, it's a full-featured console puzzle challenge!

---

## 🎮 About

GridBlaster is a logic-based puzzle game where players must uncover all non-mine cells on a grid without triggering any hidden mines. Players can:

- Choose difficulty levels (Easy, Intermediate, Advanced)
- Flag suspicious cells
- Keep track of time and score
- Play directly from the terminal using intuitive inputs

Built as part of an ASM (Application Software Management) project using core C++ concepts like OOP, vectors, and smart game logic.

---

## 🚀 Features

- 🔥 Three difficulty levels: Easy (9x9), Intermediate (16x16), Advanced (22x32)
- 🏁 Flag/unflag suspected mines
- 🧠 Recursive logic to reveal empty areas
- 🕓 Built-in timer for gameplay duration
- 💯 Score system that rewards wins
- 🧱 Fully object-oriented architecture (Classes: `Board`, `Cell`, `Player`, `Game`, `Level`)

---

## 🛠️ How to Run

### Compile:
```bash
g++ -std=c++11 -o GridBlaster GridBlaster.cpp



