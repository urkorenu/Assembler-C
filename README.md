# 🚀 Labratory-C-Final-Project 🚀
## Project Grade - Hoping for - 💯
<p align="center"> <img src="https://komarev.com/ghpvc/?username=BreadcrumbsAssembler-C&label=Repo%20views&color=0e75b6&style=flat" alt="Assembler-C" /> </p>

This is the Final project (mmn 14) in Laboratory C 20465- 2024A course at the Open University. This project was developed as part of the "20465 - Systems Programming Laboratory" 2024A course at the Open University. It's a comprehensive assembler program for a specific assembly language, written in C. The purpose is to simulate the operation of common system programs, and thus experience writing a large-scale software project.

## 📖 Table of Contents
- [Project Structure](#-project-structure)
- [Getting Started](#-getting-started)
- [Usage](#-usage)
- [Testing](#-testing)
- [Documentation](#-documentation)
- [Contribution](#-contribution)

___

## 🧩 Project Structure

The project consists of multiple C and header files, each serving a specific purpose in the program. It adheres to principles of clarity, readability, structured writing, and data abstraction.

The assembler works in three main stages:

1. **Pre-Processing**
2. **First Pass**
3. **Second Pass**

These stages form the core algorithm of the assembler.

### Pre-Processing

The pre-assembler reads the source file line by line and identifies macro definitions. If a macro is identified, the lines of the macro are added to a macro table and replaced in the source file.

### First Pass

The first pass identifies symbols (labels) and assigns them numerical values representing their corresponding memory addresses.

### Second Pass

In the second pass, the assembler generates the final machine code, replacing operation names with their binary equivalents and symbol names with their assigned memory locations.

Details about the algorithms for these stages can be found in the [documentation](#-documentation).

___ 

## ⚙️ Getting Started

### ✔️ Prerequisites

Before you begin, ensure that you have the following prerequisites installed:
> - `ℹ️ GCC compiler`

### 📦 Installation

1. Clone the Labratory-C-Final-Project repository:
```sh
git clone https://github.com/urkoren/Assembler-C.git
```

2. Change to the project directory:
```sh
cd Assembler-C
```

3. Run Makefile to compile the program:
```sh
`make`
```


## 🔧 Usage

Run the compiled program using the following command: `./assembler file_name_1 ... file_name_N`

This will output machine code generated from the provided assembly file.

___ 

## 🧪 Testing

Several assembly language input files are provided to demonstrate the use of various operations and data types, as well as the assembler's handling of errors.

___ 

## 📚 Documentation

Each function in the source code is accompanied by concise, clear documentation in the form of header comments, explaining its purpose and usage. Important variables are also explained. Detailed comments are present throughout the code for better understanding.

___ 

## 🤝 Contribution

This project does not accept contributions as of now.

___
## 👏🏻 Ur Koren and Yam Sheizaf ©
