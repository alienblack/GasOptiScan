# GasOptiScan

GasOptiScan is a Solidity loop analysis tool. It compiles a contract to EVM bytecode, decompiles the runtime, builds a control‑flow graph, and flags while/loop bodies that can be fused without changing semantics—helping cut redundant gas costs. An Express API wraps the C++ analysis pipeline so you can post contract source and get fusibility suggestions back.

## Background
- Based on “GasOptiScan: Unveiling Gas-Inefficient Smart Contracts via Loop Fusible Pattern Detection for Enhanced Cost Efficiency,” ETNCC 2023, Windhoek, Namibia, pp. 178‑183, DOI: 10.1109/ETNCC59188.2023.10284938.
- This implementation adapts those loop-fusibility heuristics and packages them behind a simple API for quick experimentation and demos.

## How it works
1. The API writes the incoming Solidity snippet to `code.sol`.
2. `solc --bin-runtime` emits runtime bytecode, which is decompiled with a `bin/decompile` script (from the Vandal toolchain) into `disasm.txt`.
3. `make_graph_input` (`headdetection1.h`) parses the disassembly and builds `input_file.txt`, a compact CFG representation.
4. `head_detect` (`headdetect.h`) walks the graph to find loop heads and bodies, saving them to `graph_output_file.txt`.
5. `upper_bound.h`, `lowerbound.h`, and `stackvariable.h` extract loop bounds and stack variables from the disassembly and map them to each loop block.
6. `main.cpp` compares loop bounds and stack usage to mark subsets of loops that share the same trip count and do not share stack variables—these are reported as fusible loops.

## Project layout
- `server.js` — Express server exposing `POST /run_cpp_code`; compiles and runs the analyzer.
- `main.cpp` — C++ driver orchestrating compilation, decompilation, graph construction, and fusibility checks.
- `headdetection1.h`, `headdetect.h` — CFG construction and loop head/body detection via DFS.
- `upperbound.h`, `lowerbound.h` — Parses loop entry/exit metadata to estimate loop trip bounds.
- `stackvariable.h` — Collects stack variables used inside each loop body to enforce non-overlap.
- Sample artifacts: `code.sol`, `disasm.txt`, `input_file.txt`, `graph_output_file.txt`, `upper_bound.txt`, `lower_bound.txt`, `stack_variable.txt` (handy for understanding the expected formats).

## Prerequisites
- Node.js 16+ and npm
- `g++` (C++17) and Python 3
- `solc` available on PATH
- Vandal (or compatible) EVM decompiler providing a `bin/decompile` entry point  
  *(the script is not checked in; install Vandal and ensure `bin/decompile` resolves locally).*

## Setup & API usage
1. Install dependencies: `npm install`
2. Ensure `solc` and `bin/decompile` are available on PATH.
3. Start the API: `npm start` (listens on port 8080).
4. POST Solidity source to the analyzer:
   ```bash
   curl -X POST http://localhost:8080/run_cpp_code \
     -H "Content-Type: application/json" \
     -d '{"code": "<your Solidity contract here>"}'
   ```
   The response echoes the C++ analyzer stdout (e.g., `Block 1, 2 are fusible`), and intermediate artifacts are written alongside the server.

## Running the analyzer manually
If you already have a `code.sol` file, you can run the pipeline without the API:
```bash
solc --bin-runtime code.sol | tail -n 1 > code.hex
python3 bin/decompile code.hex > disasm.txt
g++ main.cpp -o main
./main
```
This regenerates `disasm.txt`, `input_file.txt`, loop head/body metadata, and prints fusible-loop suggestions to stdout.

## Notes
- The fusibility check requires loops to have identical bounds and no overlapping stack variables; relax or extend those heuristics in `main.cpp` as needed.
- Sample output files in the repo reflect a prior run and are useful as format references when modifying the parsers.
