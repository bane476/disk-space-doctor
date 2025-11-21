🩺 Disk Space Doctor

A lightweight, efficient, and minimal Unix-based disk analysis tool written in C. It scans directories recursively, finds the largest files and directories, detects common junk files, and displays results in a clean, human-readable format.

✨ Features

Disk Space Doctor is designed for speed and clarity, offering the following capabilities:

Recursive Directory Scanning: Deeply analyzes the contents of the specified path.

Displays Top Largest Files: Quickly identify files and directories consuming the most space.

Human-Readable Size Formatting: Output sizes are formatted in KB / MB / GB.

Sorted Output: Results are sorted (largest first) for immediate interpretation.

Junk File Detection: Identifies and reports common temporary and cache artifacts.

Clean and Minimal Terminal UI: Focuses on presenting the data clearly without clutter.

Very Fast: Leverages efficient stat() system calls for rapid performance.

🛠️ Build Instructions

Prerequisites

GCC or Clang compiler

Linux/Unix environment

make build utility

Build

Navigate to the project directory and run the make command:

make


Run

Execute the compiled binary, optionally providing a directory path to scan (defaults to the current directory if none is provided):

./doctor


🧹 Junk File Categories

The program detects common, removable files and directories based on standard Unix patterns:

Files ending in *.tmp

Directories ending in *.cache

Standard XDG Trash folder contents:

~/.local/share/Trash/files/

~/.local/share/Trash/info/

📌 Future Improvements

We plan to enhance the tool with the following features:

Optional flag to delete junk files.

JSON output mode for machine readability.

Progress indicator for very large directory scans.

Multi-threaded scanning for maximum performance.
