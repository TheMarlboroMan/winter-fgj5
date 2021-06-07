# winter-fgj5

# building and dependencies.

This project depends on some very specific commits of some old libraries. Long story short, I just bundled these and made some fixes so they build in 2021, they are in the "dependencies" directory, so:

1) build dependencies/libdansdl2
2) update the dependencies/tools makefile so the libdansdl2 paths match what you built in step 1
3) build dependencies/tools
4) update the main makefile so the dependencies point at these things you just built.
5) build the main application.

# TODO:

- Do the map title thing.
	- Fades in, stays, fades out. Use the linear function thing and be done.
	- The hub
		- A world unhinged
		- A world with no color
		- A world in silence
- Increment minor version number.
- Add symbols over the hub doors.

# Notes to self.

map01
	exits to map 1, 3, 4
map1
	-> goes to map 2
	map 2
		-> goes to map 0
map3
	-> goes back to map 0
map4
	-> goes to map 5
	map5
		-> goes to map 4 or 6
	map6
		-> goes to map 7 or 8
	map7
		-> goes to map5
	map8
		-> goes to map0

# Changelog

- June, 3rd 2021, AppImage build.
- June, 2nd 2021, bundling deps.
- As of nov 5th 2015, the code has been patched to require the compatibility layer in the repository "capa_compatibilidad_libdansdl2" and to link with SDL2_tff (even though it is not used). Should the code be updated the compatibility layer will be removed.
