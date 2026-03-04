# BunnyHoppy

BunnyHoppy is a Cub3D-based first-person game written in C with MLX42.
It includes native and WebAssembly builds, bonus gameplay systems (keys, doors,
checkpoints, lava), and custom pixel textures.

## What It Includes

- Ray-casting renderer (walls + floor/ceiling)
- Strict `.cub` parsing and map validation
- Bonus mode systems: keys, doors, minimap, sprites, checkpoints
- Native build (`cub3D_bonus`) and browser build (`web/` via Emscripten)

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
assets/                 XPM42 textures
maps/                   `.cub` maps (default map: `maps/default.cub`)
web/                    browser shell (`index.html`, docs, generated wasm/js/data)
```

## Ray Casting Logic (C)

The renderer casts one ray per screen column.

1. Build a camera ray from player direction + camera plane.
2. Use DDA (grid stepping) to walk the map until hitting a wall tile.
3. Compute perpendicular wall distance (avoids fish-eye distortion).
4. Convert distance into wall strip height on screen.
5. Sample texture `x/y` coordinates and draw the vertical strip.
6. Draw floor/ceiling and apply shading.

Core files to read:

- `src/game/fn_game_ray.c`
- `src/game/fn_game_wall_loop.c`
- `src/game/fn_game_wall_draw.c`
- `src/game/fn_game_floor_draw.c`

## Native Build

```bash
make bonus
./cub3D_bonus maps/default.cub
```

## WebAssembly Build

Install/activate emsdk once per shell session:

```bash
source ~/emsdk/emsdk_env.sh
```

Build and run locally:

```bash
make -f Makefile.web
make -f Makefile.web serve
```

Open:

- `http://localhost:8000/index.html`

## Deploy To `mahmutkilic.nl/bunnyhoppy`

If your website is in a different repo, copy generated web files into that repo
under `bunnyhoppy/` and push.

From this repo:

```bash
make -f Makefile.web
```

In your website repo:

```bash
mkdir -p bunnyhoppy
cp /path/to/cub3d/web/index.html bunnyhoppy/
cp /path/to/cub3d/web/cub3d.js bunnyhoppy/
cp /path/to/cub3d/web/cub3d.wasm bunnyhoppy/
cp /path/to/cub3d/web/cub3d.data bunnyhoppy/
cp /path/to/cub3d/web/coi-serviceworker.js bunnyhoppy/

git add bunnyhoppy
git commit -m "Deploy BunnyHoppy"
git push
```

Then visit:

- `https://mahmutkilic.nl/bunnyhoppy/`
