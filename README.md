# Mini Game Script Interpreter

A **domain-specific scripting language interpreter** for building simple **2D grid-based games**, developed as part of the **Compiler Design Lab (CSE332)**.  
This project demonstrates core compiler concepts using **Flex**, **Bison**, and **C**.

---

## 🚀 Features
- Custom game scripting language (DSL)
- Lexical analysis with **Flex**
- LALR(1) parsing with **Bison**
- Semantic actions & runtime execution in **C**
- **Dynamic grid sizes**: 3x3, 4x4, 5x5, 10x10, 15x15, 20x20, 25x25, 50x50, 100x100
- **Player health system** with damage and healing
- **Inventory system** with item collection and usage
- **Multiple object types**: obstacles, items, enemies, power-ups, walls, doors
- **Teleportation system** with named teleport points
- **Sound effects** (terminal beeps) that can be toggled
- **Random number generation** for procedural content
- **Game timer** and wait commands
- **Combat system** with enemy attacks and player combat
- Player movement with collision detection
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

## 📜 Script Commands

### Grid Management
- `GRIDSIZE <size>` - Set grid size (3, 4, 5, 10, 15, 20, 25, 50, or 100)

### Player & Health
- `HEALTH <amount>` - Change player health (positive heals, negative damages)
- `STATUS` - Display player status (position, health, score, inventory, etc.)

### Movement & Combat
- `MOVE player <DIRECTION>` - Move player (UP, DOWN, LEFT, RIGHT)
- `ATTACK` - Attack enemies in adjacent cells

### Object Placement
- `PLACE OBSTACLE <x> <y>` - Place obstacle (#) at position
- `PLACE ITEM <x> <y>` - Place collectible item (*) at position
- `PLACE ENEMY <x> <y>` - Place enemy (E) at position
- `PLACE POWERUP <x> <y>` - Place power-up (+) at position  
- `PLACE WALL <x> <y>` - Place wall (|) at position
- `PLACE DOOR <x> <y>` - Place locked door (D) at position

### Inventory & Items
- `INVENTORY <item>` - Add item to inventory (sword, key, potion, etc.)
- `USE <item>` - Use item from inventory (effects vary by item type)

### Teleportation
- `TELEPORT <name> <x> <y>` - Create named teleport point at position
- `TELEPORT <name>` - Teleport to existing teleport point

### Game Mechanics
- `RANDOM <var> <min> <max>` - Generate random number and store in variable
- `SOUND <0|1>` - Enable (1) or disable (0) sound effects
- `WAIT <seconds>` - Pause execution for specified seconds

### Variables & Arithmetic
- `SET <var> <expr>` - Set variable value
- `ADD <var> <expr>` - Add to variable
- `SUBTRACT <var> <expr>` - Subtract from variable
- Supports expressions: `(x + y * 2)`

### Control Flow
- `IF <var> <operator> <value> ... ENDIF` - Conditional execution
- `REPEAT <count> ... ENDREPEAT` - Loop execution

### Output
- `SAY "<message>"` - Print message

### Exit
- `EXIT` - Exit program

---

## 💡 Example Usage

```
GRIDSIZE 8
SAY "Enhanced adventure begins!"
HEALTH 100
INVENTORY sword
PLACE ENEMY 3 3
PLACE POWERUP 5 5
TELEPORT base 1 1
MOVE player RIGHT
ATTACK
USE sword
TELEPORT base
STATUS
EXIT
```

### Object Legend
- `P` - Player
- `#` - Obstacle  
- `*` - Item (+10 score)
- `E` - Enemy (-20 health when touched, +50 score when defeated)
- `+` - Power-up (+25 score, +15 health)
- `|` - Wall (blocks movement)
- `D` - Door (needs key to pass)
- `T` - Teleport point

See [example.txt](example.txt) and [enhanced_demo.txt](enhanced_demo.txt) for comprehensive examples.

---

Developed By   
Redwan Rahman
