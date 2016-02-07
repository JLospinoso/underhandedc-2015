Here's my submission for the [2015 Underhanded C Competition](http://www.underhanded-c.org).

The vulnerable function is given in match.c; it ostensibly performs a [cosine similarity][https://en.wikipedia.org/wiki/Cosine_similarity]
to determine how similar the reference and sample material are. 

Can you find the bug?

The underhanded part is in the error checking: as a boundary condition, if the reference AND the sample produce an overflow (i.e. they have
really, really big elements), the matching function produces a match. It's the best guess we can make about whether the materials match or not.

The explanation of what goes wrong is in spoiler.c (and the `main` method shows the bug in action).

This submission got a "runner-up" honorable mention.

# Compiling
The project uses [cmake](https://cmake.org/):

```sh
git clone git@github.com:JLospinoso/underhandedc-2015
cd underhandedc-2015
mkdir build
cd build
cmake ..
```

This will generate (hopefully) some sensible files for your build environment. For linux like environments, proceed with:

```sh
make
./underhandedc_2015
```

For Windows, open `underhandedc_2015.sln` in Visual Studio and compile.

The output should look like this:

```
Test1 v Reference:     NO_MATCH
Test2 v Reference:     MATCH
Dorked v Reference:    MATCH
```