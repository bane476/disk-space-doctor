Disk Space Doctor

A lightweight Unix-based disk analysis tool written in C. It scans directories recursively, finds the largest files/directories, detects junk files, and displays results in a clean, human-readable format.


📌 Features
Recursive directory scanning
Displays top largest files
Human-readable size formatting (KB / MB / GB)
Sorted output for easy interpretation
Junk file detection (.tmp, .cache, Trash folders)
Clean and minimal terminal UI
Very fast — uses efficient stat()-based scanning


🛠️ Build Instructions
Prerequisites:
GCC or Clang
Linux/Unix environment
Make


Build : make
Run : ./doctor <path>


🧹 Junk File Categories
The program detects common junk patterns, including:
*.tmp
*.cache
Trash folder contents:
~/.local/share/Trash/files/
~/.local/share/Trash/info/


📌 Future Improvements
Optional flag to delete junk files
JSON output mode
Progress indicator for large directory scans
Multi-threaded scanning for maximum performance
