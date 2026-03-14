# cub3D

cub3d is a first-person game written in C using MLX42.
The project focuses on ray casting, map parsing, movement/collision, and
bonus gameplay systems implemented in a clean modular structure.

## Features

- Ray-casting renderer (walls, floor, ceiling, shading)
- Strict `.cub` parser and map validation
- Textured walls (XPM42 assets)
- Player movement, jump, and collision handling
- Bonus systems: keys, doors, minimap, sprites.

## Controls

- Move: `WASD`
- Look: `Mouse` and `Arrow Keys`
- Jump: `Space`
- Run: `Shift`
- Open door: `E`
- Toggle minimap: `M`
- Exit: `Esc`

## Project Layout

```text
include/                headers (`cub3d.h`)
src/parser/             config/map parser and validation
src/game/               core loop, movement, ray cast, draw pipeline
src/bonus/              doors, keys, minimap, sprites, checkpoint logic
src/error/              error handling helpers
assets/                 XPM42 textures and sprites
maps/                   `.cub` maps (default: `maps/default.cub`)
```

## Ray Casting Logic (C)

The renderer casts one ray per screen column:

1. Build camera ray from player direction + camera plane.
2. Use DDA grid stepping until a wall tile is hit.
3. Compute perpendicular distance to avoid fish-eye distortion.
4. Project wall slice height on screen.
5. Sample texture coordinates and draw vertical stripe.
6. Draw floor/ceiling and apply distance-based shading.

Core files:

- `src/game/fn_game_ray.c`
- `src/game/fn_game_wall_loop.c`
- `src/game/fn_game_wall_draw.c`
- `src/game/fn_game_floor_draw.c`

## Build

Mandatory build:

```bash
make
./cub3D maps/wall.cub
```

Bonus build:

```bash
make bonus
./cub3D_bonus maps/default.cub
```

## Cleanup

```bash
make clean
make fclean
```
