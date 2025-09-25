# Dep-Trust: An Anomaly-Based Heuristic Engine for Supply Chain Security

[![license: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Language](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_programming_language)
[![Status](https://img.shields.io/badge/status-in%20development-orange.svg)](https://github.com/djbertolo/dep-trust)

Dep-Trust is a static analysis tool, written in C, designed to address the critical issue of software supply chain security in C/C++ projects. Inspired by widespread vulnerabilities like Log4j, this project aims to help developers and researchers detect malicious code injected into open-source dependencies before it can be integrated into a final product.

The core innovation of Dep-Trust in its **anomaly-based heuristic engine**. Instead of relying on known malware signatures, it flags suspicious libraries by identifying behaviors that deviate from their expected purpose. This allows for the potential discovery of novel, zero-day threats.

---

## The Problem

The modern software development ecosystem relies heavily on open-source, third-party libraries. While this accelerates development, it also introduces significant risk. A single malicious dependency, nested deep within a project's dependency tree, can lead to a catastrophic security breach. Traditional security tools often use signature-based detection, which is ineffective against novel or heavily obfuscated threats. Dep-Trust aims to provide a deeper, more context-aware layer of security.

---

## Features (Planned & In-Progress)

* **Recursive Dependency Mapping:** Parses `Makefile` based C/C++ projects to construct a complete, directed graph of all dependencies.
* **Library Categorization:** Automatically classifies libraries by their intended purpose (e.g., "Networking", "Cryptography", "Math").
* **Behavioral Baselining:** Establishes a profile of expected behavior for each library category.
* **Anomaly-Based Heuristics:**
    * **Capatibility Mismatch:** Flags libraries that exhibit behavior outside their baseline (e.g., a math library making network calls).
    * **Code Entropy Analysis:** Calculates the entropy of binary sections to detect potentially packed or obfuscated code.
    * **Suspicious String Detection:** Scans for hardcoded IP addresses, domains, and other suspicious artifacts.

---

## Getting Started

This project is currently in the early stages of development.

### Prerequisites

* A C Compiler (e.g., GCC, Clang)
* `make`
* `graphviz` (for visualizing dependency graphs)

### Building from Source

```bash
# Clone the repository
git clone https://github.com/djbertolo/dep-trust.git

# Navigate to the project directory
cd dep-trust

# Compile the project
make
```

### Usage

```bash
# Analyze a project and generate a report
./dep-trust /path/to/target/project

# Generate a visual dependency graph
./dep-trust --visualize /path/to/target/project > graph.dot
dot -Tpng graph.dot -o dependency_graph.png
```

---

## Project Goals & Roadmap

This project is being developed as part of an independent undergraduate research initiative at California State University, San Bernardino, with the intention of submission to the CSUSB Student Research Competition.

- [X] **Phase1: Foundational Framework (Q4 2025)**
    - [ ] `Makefile` Parser
    - [ ] Recursive Dependency Graphing
    - [ ] Basic Heuristics (String & Symbol Analysis)
- [ ] **Phase2: Advanced Heuristic Engine (Q1 2026)**
    - [ ] Library Categorization Engine
    - [ ] Code Entropy Analysis
    - [ ] Comprehensive Reporting

For a detailed, week-by-week log of progress, challenges, and discoveries, please see the [**Research & Development Journal**](JOURNAL.md).

---

## Contributing

As this is currently an academic research project, contributions are not being accepted at this time. However, feedback and suggestions are welcome. Please open an issue to start a discussion.
















































