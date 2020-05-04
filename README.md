# GeoRhiau

GeoRhiau is a geometry library. My goal for GeoRhiau is to do "everything geometry", although I will admit that is quite a wide scope. At the moment, this library is concerned with generating 2D triangulations of point clouds. 

Contained within GeoRhiau is some very basic plotting functionality. This will eventually be removed, seriously improved
and moved over the a dedicated repo that will be fetched via CMake. 

## Building

To build

`make`

To test

`make test`

To clean

`make clean`

To produce different builds (e.g. Release), run

`make BUILD_TYPE=<build-type>`

If no `BUILD_TYPE` is entered, it defaults to Debug.

To generate docs

`cd build && make docs && google-chrome docs/html/index.html && cd ..`

## Things to be done

- [x] Implement minimize maximum angle constraint triangulation (Delaunay)
- [ ] Implement minimize maximum edge length constraint triangulation (not the same thing as above).
- [ ] Optimise the above algorithms
