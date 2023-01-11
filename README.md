**WARNING** This project is currently *very* experimental and at it's
earliest stage.

# The Cool Text Editor (CTE)

```
/cte
|- build: All things compilation related.
|- documents: Additional informative resources on all things CTE.
|- source: The source code for this/your project.
|  `- cte: The source code for CTE. The rest of the `/source` folder is
|             for user-made things, such as plugins.
`- tests: Legos.
```

CTE is a terminal-based and a *truely* lightweight experimental text
editor.
I started this project to experiment with some topics, such as efficient
string manipulation and standards; also because I disliked other text
exitors.

Yes, I m quite new to computer science--I started around last year as of < 11 Jan. 2022 with less than a year of hours dedicated to computer
science. But I have already accidentally reinvented the segmented
doubly linked list used for the buffer as of < 11 Jan. 2022--something
that I am very proud of.

For this project, I am focusing on it being *truely* lightweight with
a big focus on an easy and simple configuration process using an
intuitive API. Because of this, it is encouraged for CTE to be a base
for your own text editor.

## Base features

At it's base, it only

* initiates the terminal,
* loads a single file, and
* allows you to edit text.

You can add more features using CTE's API; or edit CTE's source
directly.

## Features

- [ ] usable,

- [ ] key remapping,

- [ ] theming,

- [ ] plugin system, and

- [ ] habit system.

### Source code ricing (**NOTE** currently indated)

You can simply edit a couple variables in the `/source/cte/config.hpp`
file to configure small things, such as colors and keymaps.

Plugins are created manually by creating a new folder in the
`/source/cte` folder and including the `/source/cte/plugin.hpp` header.

*To know more about plugins, open `/source/cte/plugin.hpp`.*

#### Why?

I don't like using libraries, nor do I feel like creating my own
configuration language.
Also because it allows you to **fully** personalize everything.
This may be unsafe, but it won't be my fault if you break it!

---

## Internals

The source code is located in the `/source/cte` folder, and it
should be *fairly* easy to read.
However, it does favor *performance* over readability, so synopses will
be provided in the header files.

One thing to note is that *only* C libraries are used.

---

## Building

Just run the really bad `/makefile`.
