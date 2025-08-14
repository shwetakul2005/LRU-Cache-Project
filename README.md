#SwiftOpen

A lightning-fast, cross-platform recent file launcher powered by LRU Cache.

SwiftOpen is a command-line utility that keeps track of your most recently opened files, folders, or URLs, and lets you launch them instantly.
It uses an LRU (Least Recently Used) cache under the hood to ensure your top-used items are always at your fingertips — and the oldest ones get kicked out automatically.

##Features

LRU Cache Implementation using:

Doubly Linked List for ordering

unordered_map for O(1) lookups

Persistent Storage in recent.txt between program runs

Cross-platform launching support:

Windows (start)

macOS (open)

Linux (xdg-open)

Interactive Menu:

Launch a recent file/URL

Add a new entry

Delete an entry

Quit

Capacity Limit: Stores the last 10 entries by default

##Project Structure
.
├── main.cpp        # Source code
├── recent.txt      # Stores recent entries
└── README.md       # Documentation

##Installation & Usage
1️) Compile
g++ main.cpp -o swiftopen

2) Run
./swiftopen


Make sure recent.txt is in the same directory as the executable.
If it doesn't exist, SwiftOpen will create it automatically.

##Example Run

Startup List:

1. /home/user/Documents/report.pdf
2. /home/user/Projects/code.cpp
3. https://example.com
Enter 'l' to launch or 'n' for new path or 'd' to delete or 'q' to quit:


Launching an Entry:

Enter 'l' to launch...
enter number from the list: 2
yayy!!!
Opening: /home/user/Projects/code.cpp

##How It Works

On startup, SwiftOpen reads recent.txt and loads entries into an LRU cache.

Entries are stored in a Doubly Linked List for quick ordering.

A Hash Map ensures instant lookup and movement of items.

When a new item is added and the cache is full, the least recently used entry is removed.

Actions (launch, new, delete) update both the cache and recent.txt.

##Cross-platform Launch Commands

SwiftOpen uses platform-specific commands to open files:

Windows: start "" "path"

macOS: open "path"

Linux: xdg-open "path"
