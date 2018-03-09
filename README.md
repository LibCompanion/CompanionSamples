# Samples for Companion

![Companion](https://libcompanion.github.io/CompanionDoc/images/logo.png "Companion")

# Build Companion Samples

[Samples](https://github.com/LibCompanion/CompanionSamples) are included as a submodule or can be referenced via the CMake variable `Companion_SAMPLE_MODULE`. To build the samples you have to enable the `Companion_BUILD_SAMPLES` flag.

## Build Samples from Submodule

```
git clone https://github.com/LibCompanion/Companion.git
cd Companion
git submodule update --init --recursive
cmake -DCompanion_BUILD_SAMPLES=ON
make
```

## Build Samples from Project

```
git clone https://github.com/LibCompanion/Companion.git
```

```
git clone https://github.com/LibCompanion/CompanionSamples.git
cmake -DCompanion_BUILD_SAMPLES=ON -DCompanion_SAMPLE_MODULE=/path/to/CompanionSamples/
make
```

## License

```
This program are usage example for Companion.
Copyright (C) 2016-2018 Andreas Sekulski, Dimitri Kotlovsky

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
```
