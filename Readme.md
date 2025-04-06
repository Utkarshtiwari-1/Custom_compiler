# 🛠️ Building a Simple Custom Compiler for `Z = A^2 + B` 

This guide walks you through creating a tiny compiler that converts a high-level custom instruction (e.g., `Z = A^2 + B`) into x86 assembly, assembles it, links it, and shows the result in a MessageBox on Windows. You'll also understand the underlying architecture and theory.

---

## ✅ Prerequisites: What You Need to Install

To build and run your own compiler and assembly programs on Windows, you'll need the following tools:

### 1. 🔧 MinGW (Minimalist GNU for Windows)
- Provides the GNU compiler (`g++`, `gcc`) and tools like `objdump`.
- [Download MinGW](https://sourceforge.net/projects/mingw/)
- During installation, check `g++` (C++ Compiler).
- Add `C:\MinGW\bin` to your system `PATH` in Environment Variables.

### 2. 🛠️ NASM (Netwide Assembler)
- Converts `.asm` to `.obj` files.
- [Download NASM](https://www.nasm.us/pub/nasm/releasebuilds/)
- Add NASM to system `PATH`.

### 3. 🔗 GoLink (Windows PE Linker)
- Links `.obj` to `.exe`.
- [Download GoLink](https://www.godevtool.com/)
- Extract `GoTools.zip`, copy `GoLink.exe` to project directory.

### 4. 📝 Text Editor or IDE
- Use Visual Studio Code, Sublime Text, or Notepad++.

---

## 🧾 Terminal Commands & Their Purpose

| Command | Description |
|--------|-------------|
| `g++ -std=c++17 main.cpp tokenizer.cpp parser.cpp -o sage_compiler.exe` | Compiles the compiler source code. |
| `./sage_compiler.exe` | Runs the compiler which generates `program.asm` from `example.sage`. |
| `nasm -f win32 program.asm -o program.obj` | Assembles the assembly code into an object file. |
| `GoLink.exe /console /entry _start program.obj user32.dll` | Links the object file into a Windows executable. |
| `./program.exe` | Runs the final output and displays result in a MessageBox. |
| `objdump -d program.obj` | Disassembles object file to show generated machine instructions. |

These commands form the full compilation and execution pipeline: from high-level code to low-level machine code to execution.

---

## 📁 Folder Structure
```
sage_compiler/
├── main.cpp           # Compiler entry point
├── tokenizer.cpp      # Splits input into tokens
├── tokenizer.h
├── parser.cpp         # Converts tokens into AST
├── parser.h
├── ast.h              # AST data structures
├── example.sage       # Contains: Z = SQUAREADD(A, B)
├── macros.inc         # External call declarations
├── build.bat          # Optional script
└── GoLink.exe         # Linker
```

---

## 🔄 Code Execution Flow: Theory + Practice

This custom compiler transforms a domain-specific language (DSL) into x86 assembly. It mimics the compilation pipeline:

1. Lexical Analysis → 2. Parsing → 3. Code Generation → 4. Assembling → 5. Linking → 6. Execution

### Step 1: Custom Language
Your DSL input (in `example.sage`) looks like:
```
Z = SQUAREADD(A, B)
```
This means: `Z = A * A + B`

### Step 2: Tokenizer
`tokenizer.cpp` scans the string into a list of tokens like:
- Identifiers: `Z`, `SQUAREADD`, `A`, `B`
- Operators: `=`, `(`, `,`, `)`

It converts raw text into structured elements.

### Step 3: Parser
`parser.cpp` processes tokens into an Abstract Syntax Tree (AST):
```
Assignment to Z:
└── Expression: SQUAREADD
    ├── Arg1: A
    └── Arg2: B
```
This represents the logic of the expression in memory.

### Step 4: Code Generation
`main.cpp` walks the AST and outputs `program.asm`:
```asm
mov eax, [A]       ; Load A
imul eax, eax      ; A squared
add eax, [B]       ; A^2 + B
mov [Z], eax       ; Store in Z
```
It then appends Windows API calls to display result in a MessageBox.

### Step 5: Assemble and Link
Convert `.asm` to `.obj`, then to `.exe`:
```bash
nasm -f win32 program.asm -o program.obj
GoLink.exe /console /entry _start program.obj user32.dll
```

### Step 6: Run It
```bash
./program.exe  # MessageBox shows result: 19
```

---

## 🧠 How the Assembly Works

The core math is:
```asm
mov eax, [A]     ; Load A into EAX
imul eax, eax    ; Multiply A * A (EAX = A^2)
add eax, [B]     ; Add B → EAX = A^2 + B
mov [Z], eax     ; Store result in Z
```

To show this result in a MessageBox:
```asm
mov eax, [Z]     ; Load result
add eax, '0'     ; Convert digit to ASCII (basic form)
mov [digit], al  ; Store as string
push 0           ; MB_OK
push title
push digit       ; Message content
push 0
call [MessageBoxA]
```

---

## 🧪 Inspecting Output
To verify what instructions were generated:
```bash
objdump -d program.obj
```
This shows low-level opcodes like:
- `mov`, `imul`, `add` (for computation)
- `push`, `call` (for MessageBox)

---

## 📌 Summary
You’ve built a basic compiler:
- Accepts custom DSL: `Z = SQUAREADD(A, B)`
- Tokenizes → Parses → Generates x86 Assembly
- Assembles to `.obj`, Links to `.exe`
- Shows result using Windows MessageBox

This project teaches the end-to-end path from language design to execution, including internals of how compilers and assembly interact.

---

## 🚀 Possible Improvements

- Add multiple instructions and arithmetic types (e.g., `MULADD`, `DIVSUB`)
- Handle variables dynamically from user input
- Add error checking in tokenizer/parser
- Generate 64-bit assembly
- Port to Linux (use syscall instead of MessageBox)
- Visualize AST
- Compile to bytecode/intermediate language instead of just assembly

This mini-compiler gives you foundational knowledge of how programming languages are implemented under the hood.

