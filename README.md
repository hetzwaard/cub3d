# GO! 🐰💨

### Bunny Hop Maze Runner

GO! is a fast-paced bunny hop game built on the 42 **cub3d** project. You explore compact arenas in first person, chaining jumps to build speed, threading tight corners, and reaching the exit as fast as possible.

The goal: learn raycasting, textures, and real-time input while keeping the code clean and modular.

---
## Features
- Classic raycasting engine (walls, floor/ceiling shading)
- Textured walls using XPM assets
- Smooth movement + rotation
- Bunny hop style momentum (jump timing + strafing)
- Map parsing with strict format validation
- Clean error reporting and safe cleanup

---
## Bonus Implemented
- Doors and keys system
- Minimap with FOV
- Sprite rendering pipeline
- Extra post-processing / shading effects

---
## Controls
- **Move:** WASD
- **Look:** Mouse
- **Jump:** Space
- **Run:** Shift
- **Exit:** Esc

---
## Architecture Overview
```
include/            Public headers (main: cub3d.h)
include/libft/      Custom libc-like helper library (libft)
src/
	parser/           .cub parsing, validation, map build
	game/             core loop, input, movement, raycasting
	bonus/            doors, keys, sprites, minimap, extras
	error/            error helpers and messages
assets/             textures and sprites (XPM)
maps/               sample .cub maps
```

Flow:
1. Parse .cub file (textures, colors, map)
2. Validate map + player start
3. Initialize MLX + textures
4. Game loop (input → move → raycast → draw)
5. Cleanup and exit

---
## Key Modules
- Parsing: identifiers, map checks, color parsing
- Rendering: raycasting, wall draw, floor/ceiling draw, shading
- Movement: collision checks, jump, rotate, time-based updates
- Bonus: doors/keys, sprites, minimap
- Cleanup: safe free routines and error path handling

---
## Building
Prerequisites:
- `make` and a POSIX toolchain

Build:
```bash
make
```

Rebuild from scratch:
```bash
make re
```

Clean objects / full cleanup:
```bash
make clean
make fclean
```

---
## Running
```bash
./cub3d maps/test.cub
```

---
## Notes
This project uses MLX42 for rendering and input handling.

---
## Credits
Built for the 42 curriculum. GO! is a bunny hop twist on cub3d.

---
Enjoy the speed. 🐇
