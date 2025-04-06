#include "tokenizer.h"
#include "parser.h"
#include "ast.h"
#include <fstream>
#include <iostream>

void generateAssembly(const std::vector<Assignment>& program, std::ostream& out) {
    out << "%include \"macros.inc\"\n\n";
    out << "section .data\n";
    out << "    A dd 4\n    B dd 3\n    Z dd 0\n";
    out << "    title db \"Z Value\", 0\n";
    out << "    digit db 10 dup(0)\n\n";

    out << "section .text\n";
    out << "global _start\n\n";
    out << "_start:\n";

    for (const auto& stmt : program) {
        if (auto squareadd = std::dynamic_pointer_cast<SquareAddExpr>(stmt.expr)) {
            out << "    mov eax, [" << squareadd->arg1->name << "]\n";
            out << "    imul eax, eax\n";
            out << "    add eax, [" << squareadd->arg2->name << "]\n";
            out << "    mov [" << stmt.target->name << "], eax\n";
        }
    }

    out << "    mov eax, [Z]\n";
    out << "    mov ebx, 10\n";
    out << "    xor ecx, ecx\n";
    out << "convert_loop:\n";
    out << "    xor edx, edx\n";
    out << "    div ebx\n";
    out << "    add dl, '0'\n";
    out << "    mov [digit + ecx], dl\n";
    out << "    inc ecx\n";
    out << "    test eax, eax\n";
    out << "    jnz convert_loop\n";
    out << "    mov byte [digit + ecx], 0\n";
    out << "    mov esi, digit\n";
    out << "    lea edi, [digit + ecx - 1]\n";
    out << "reverse:\n";
    out << "    cmp esi, edi\n";
    out << "    jge done_reverse\n";
    out << "    mov al, [esi]\n";
    out << "    mov bl, [edi]\n";
    out << "    mov [esi], bl\n";
    out << "    mov [edi], al\n";
    out << "    inc esi\n";
    out << "    dec edi\n";
    out << "    jmp reverse\n";
    out << "done_reverse:\n";

    out << "    push 0\n";
    out << "    push title\n";
    out << "    push digit\n";
    out << "    push 0\n";
    out << "    call [MessageBoxA]\n";
    out << "    ret\n";
}

int main() {
    std::ifstream in("example.sage");
    std::string input((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    auto tokens = tokenize(input);
    auto program = parse(tokens);
    std::ofstream out("program.asm");
    generateAssembly(program, out);
    std::cout << "Compiled to program.asm\n";
    return 0;
}