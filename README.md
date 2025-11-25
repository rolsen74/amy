# My AmigaOS Libraries

Just a small AmigaOS test bench repository.

This repository contains several projects primarily targeting **AmigaOS 4**, all written in C.

— Rene W. Olsen (1-Aug-2025)

## Contents

- `classes/Application` – BSD-licensed library
- `classes/Directory` – BSD-licensed library
- `libs/AmyApplication` – BSD-licensed library
- `libs/AmyBlanker` – BSD-licensed library
- `libs/AmyCLib` – C runtime library (BSD-3-Clause)
- `libs/AmyIUP` – MIT-licensed library
- `libs/AmyInput` – BSD-licensed library
- `libs/AmySDL` – Refactored SDL v1 code (LGPL-2.1)
- `libs/AmySysLog` – BSD-licensed library
- `libs/AmyZLib` – zlib-licensed library
- `libs/Reactive` – BSD-licensed library
- `programs/D` – BSD-licensed library
- `programs/rTestCase` – BSD-licensed library

## Licensing

All original code in this repository is licensed under the **BSD-2-Clause** license.  
See the `LICENSE` file at the root of this repository for full terms.

Some subprojects use other permissive licenses, including:

- **BSD-3-Clause** – used in `libs/AmyCLib`, which is derived in part from clib2 by Olaf Barthel.
- **LGPL v2.1** – used in `libs/AmySDL`, a refactored SDL v1 library.
- **zlib License** – used in `libs/AmyZLib`, a minimal zlib interface layer.

These may appear within shared directories (e.g., `inc_Public/`, `libs/`).
Each source file includes a license header indicating its specific license.
Refer to individual file headers and associated `LICENSE` and `MODIFICATIONS.md` files for full details.
