# Web Bootstrap

This folder is the browser shell for the Emscripten build.

## Build

From repository root:

```bash
make -f Makefile.web
```

Generated files:

- `web/cub3d.js`
- `web/cub3d.wasm`
- `web/cub3d.data`

## Run locally

```bash
make -f Makefile.web serve
```

Open:

- `http://localhost:8000/index.html`

## Map selection

This web build is compiled in **bonus mode**.
The startup map is fixed to `/maps/default.cub`.
