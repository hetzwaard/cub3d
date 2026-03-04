# BunnyHoppy Web Build

This folder contains the browser shell for the Emscripten build.

## Build

From repository root:

```bash
source ~/emsdk/emsdk_env.sh
make -f Makefile.web
```

Generated artifacts:

- `web/cub3d.js`
- `web/cub3d.wasm`
- `web/cub3d.data`

## Run Local

```bash
make -f Makefile.web serve
```

Open:

- `http://localhost:8000/index.html`

## Notes

- Bonus mode is compiled in.
- Startup map is fixed to `/maps/default.cub`.
- `index.html` includes a README-style section describing ray casting and deployment.

## Deploy To `mahmutkilic.nl/bunnyhoppy`

If your website lives in another repo:

1. Build here.
2. Copy these files to that repo under `bunnyhoppy/`:
   - `index.html`
   - `cub3d.js`
   - `cub3d.wasm`
   - `cub3d.data`
   - `coi-serviceworker.js`
3. Commit and push website repo.
