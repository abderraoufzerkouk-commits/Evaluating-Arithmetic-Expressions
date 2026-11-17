# Evaluating-Arithmetic-Expressions

Arithmetic expression evaluator implemented in C using stacks and the Shunting Yard algorithm

# Evaluating Arithmetic Expressions in C

A command-line arithmetic expression evaluator written in C. It parses and evaluates mathematical expressions using stacks and the Shunting Yard algorithm.

## Features

- Supports arithmetic operators: `+`, `-`, `*`, `/`, `^`
- Supports parentheses `()`
- Converts infix expressions into postfix notation
- Evaluates postfix expressions using stacks
- Checks expression validity
- Uses linked lists to implement stacks

## Technologies

- C Programming Language
- GCC Compiler
- Data Structures: Linked Lists and Stacks
- Algorithms: Shunting Yard Algorithm

## Project Structure

```text
Evaluating-Arithmetic-Expressions/
│
├── src/
│   ├── main.c
│   ├── Parser.h
│   ├── Tokenizer.h
│   └── Tools.h
│
├── .gitignore
└── README.md
```

## Compilation

Compile the project using GCC:

```bash
gcc src/main.c -o arithma -lm
```

## Usage

Run the program with an arithmetic expression as an argument:

```bash
./arithma "4+2*3"
```

Output:

```text
10
```

## Limitations

- Operands are integers.
- Division uses integer arithmetic.
- Negative exponents are not supported.

## Author

**Zerkouk Abderraouf**
