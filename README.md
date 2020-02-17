Mad Libs History
================

This repository contains the history of my Mad Libs software
development.  Mad Libs was the first significant computer program I've
written while learning my first programming language, C++, in late
2004.  It's also an example of a program that I've redeveloped a
couple of times, and had one "failed" implementation path that I've
worked around by approaching the task from a parallel development
effort.

Unfortunately, the original source code of the first program was
deleted during the redevelopment effort.  However, my original
planning document for the source code had been preserved at the latest
version... I did not use version control nor did preserve older copies
of the file during development.  Using a little bit of personal
historical knowledge, cross reference points, and other historical
reference sources, I was able to reconstruct a mostly accurate
representation of the original source code versions for future
reference, along with a mostly accurate timeline of its development to
preserve.  See the time `TIMES.md` for more information about the
timestamp and revision recovery process.

* `MAD LIBS`: 2004 - 2005: Oldest and original source code version
  line.  Mad Libs stories are hard-coded in the C++ source code.

* `mad-libs`: 2008 - 2009: Development effort on "Ultimate Mad Libs"
  which never got completed.

* `MadLibs.cpp`: 2009 - 2011: The C++ program I whipped up to read in
  Mad Libs stories from files rather than hard coding.  Please note
  that to use the latest version of this line of development, you must
  manually create a `strche.dat` file using a hex editor.

After 2011, I rewrote `MadLibs.cpp` into C, which is the current
version today in the `quorten/madlibs` GitHub repository.  This itself
has gone through a few revisions, the most significant of which was
the writing of `exparray.h` to expand the API to make it more similar
to GLib GArray.
