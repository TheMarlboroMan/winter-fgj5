# winter-fgj5

# building and dependencies.

This project depends on some very specific commits of some old libraries. Long story short, I just bundled these and made some fixes so they build in 2021, they are in the "dependencies" directory, so:

1) build dependencies/libdansdl2
2) update the dependencies/tools makefile so the libdansdl2 paths match what you built in step 1
3) build dependencies/tools
4) update the main makefile so the dependencies point at these things you just built.
5) build the main application.	

# Bugs

For some unexplained reason, sometimes the game starts up with a black screen and does nothing. I can see this in my netbook but I've seen it in real computers too.

# Changelog

- June, 3rd 2021, AppImage build.
- June, 2nd 2021, bundling deps.
- As of nov 5th 2015, the code has been patched to require the compatibility layer in the repository "capa_compatibilidad_libdansdl2" and to link with SDL2_tff (even though it is not used). Should the code be updated the compatibility layer will be removed.
