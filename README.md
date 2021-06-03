# landscape-render

This program renders the landscape in the format below:
---------
```
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```
The position of the number is the local x, y coordinates, the value of the number is the local height.\
(Central number have local position 0,0)

Implimented:
----------
- Rotations
- Bresenham line
- Wu's line
- Maps parsing

Build on `MacOS`
--------
```
make
./ls-render maps/'map_name'
```
## Controls
- `ESC` - Close the program.
- `W`/`A`/`S`/`D` - Move the map.
- `Q`/`E` - Spin the map.
- `R`/`T` - Start/Stop auto spin.
- `J` + `auto spin (R)` - Nice moving.
- `Hold LMB` - Map will follow mouse cursor.
- `Mouse wheel` - Zoom.
- `CTRL` + `mouse wheel` - Height.
- `L` - Switch mode.
- `O` - Small optimization for Breshenham mode.

Screenshots:
--------
![Image alt](https://github.com/dolovnyak/landscape-render/blob/master/screenshots/Screen%20Shot%202019-12-07%20at%2020.34.22.png)
![Image alt](https://github.com/dolovnyak/landscape-render/blob/master/screenshots/Screen%20Shot%202019-12-07%20at%2020.39.37.png)
![Image alt](https://github.com/dolovnyak/landscape-render/blob/master/screenshots/random_map.gif)
![Image alt](https://github.com/dolovnyak/landscape-render/blob/master/screenshots/pyro.gif)
![Image alt](https://github.com/dolovnyak/landscape-render/blob/master/screenshots/pylo.gif)
