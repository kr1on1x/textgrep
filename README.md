# textgrep

> **Same problem. Different language.**

A small recursive text-search CLI implemented in **Python, Rust, and C++**.

The goal of this project is simple: solve the same practical problem three times and compare how different languages approach file traversal, text processing, command-line interfaces, error handling, and project structure.

---

## ✨ Features

* 🔎 Recursive directory search
* 🔤 Case-insensitive search
* 📍 Line-number output
* 📁 File extension filtering
* 👻 Hidden-file support
* 📊 Match statistics
* ⚠️ Basic error handling
* 🧪 Shared test dataset
* 🛠️ C++ implementation with CMake

---

## 🚀 Usage

### Python

```bash
python3 python/textgrep.py "TODO" tests/data
```

Case-insensitive search:

```bash
python3 python/textgrep.py "todo" tests/data --ignore-case
```

Filter by extension:

```bash
python3 python/textgrep.py "TODO" tests/data --ext cpp
```

### Rust

```bash
cargo run --manifest-path rust/Cargo.toml -- "TODO" tests/data
```

Case-insensitive search:

```bash
cargo run --manifest-path rust/Cargo.toml -- "todo" tests/data --ignore-case
```

### C++

Build:

```bash
cmake -S cpp -B cpp/build
cmake --build cpp/build
```

Run:

```bash
./cpp/build/textgrep "TODO" tests/data
```

With line numbers and case-insensitive search:

```bash
./cpp/build/textgrep "todo" tests/data --ignore-case --line-number
```

---

## 📦 Project Structure

```text
textgrep/
├── python/
│   └── textgrep.py
│
├── rust/
│   ├── Cargo.toml
│   └── src/
│       └── main.rs
│
├── cpp/
│   ├── CMakeLists.txt
│   ├── include/
│   │   ├── config.hpp
│   │   ├── search.hpp
│   │   └── utils.hpp
│   └── src/
│       ├── config.cpp
│       ├── main.cpp
│       ├── search.cpp
│       └── utils.cpp
│
├── tests/
│   ├── data/
│   └── test.sh
│
├── README.md
├── LICENSE
└── .gitignore
```

---

## 🧩 Implementations

| Language  | Focus                                                           |
| --------- | --------------------------------------------------------------- |
| 🐍 Python | Rapid implementation and readable scripting                     |
| 🦀 Rust   | Safety, ownership, and explicit error handling                  |
| ⚙️ C++    | Low-level control, filesystem APIs, and structured architecture |

All three implementations solve the same core problem while using the tools and conventions of their respective languages.

---

## 🧪 Testing

The project includes a shared dataset under `tests/data`.

Run the test script:

```bash
bash tests/test.sh
```

The same test data can be used to compare the behavior of all three implementations.

---

## 🎯 Why this project?

`textgrep` started as a small programming challenge:

> **Can the same problem be solved cleanly in different languages?**

Instead of building three unrelated projects, the same requirements are implemented in Python, Rust, and C++.

This makes it possible to compare:

* syntax and language design
* filesystem APIs
* string processing
* CLI argument parsing
* error handling
* project organization
* development workflow

The C++ version is intentionally structured as a multi-file project to practice a more production-oriented layout with headers, source files, and CMake.

---

## 🛠️ Technologies

![Python](https://img.shields.io/badge/Python-3.x-3776AB?logo=python\&logoColor=white)
![Rust](https://img.shields.io/badge/Rust-1.x-000000?logo=rust\&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus\&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-3.20%2B-064F8C?logo=cmake\&logoColor=white)

---

## 📄 License

This project is licensed under the MIT License.

---

<p align="center">
  <b>textgrep</b><br>
  Same problem. Different language.
</p>
