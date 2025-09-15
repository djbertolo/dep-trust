# Dep-Trust: Research & Development Journal

This document tracks the weekly progress, challenges, and discoveries made during the development of the Dep-Trust project. It serves as a detailed log to complement the final research paper and presentation.

---

### Week of: Sep 15 - 21, 2025

**Weekly Goals:**
1. Implement the initial `Makefile` parser in C.
2. Create a baseline project structure and a professional `README.md`.
3. Create timeline for progress points for project.

**Progress & Key Activities:**
* Pushed the initial project structure and a complete `README.md` to the GitHub repository.

**Challenges & Blockers**

**Discoveries & Ideas:**
* Possible feature to include a contributors tracking system for each dependency to highlight potential sources of vulnerability (Inspiration from  NPM Supply Chain Attack Sept. 8, 2025)


---

### Week of: Sep 8 - 14, 2025

**Weekly Goals:**
1. Set up the development environment.
2. Select a target open-source project for intial analysis.
3. Research existing static analysis tools to understand their approaches.

**Progress & Key Activities:**
* Configured neovim to be used for C development with necessary Linting & LSP
* Chose `redis` as the first analysis target due to its well-structured `Makefile`.
* Reviewed the basic functionality of tools like `cppcheck` and `scan-build` to understand their scope.

**Challenges & Blockers:**
* None this week; focus was on setup and research.

**Discoveries & Ideas:**
* Most open-source static analysis tools focus on code quality and bug detection (e.g., buffer overflows, null pointer dereferences). Very few seem to focus on the "intent" or "behavior" of a depedency, which validates the novel approach of Dep-Trust.
