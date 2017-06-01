# Game Architecture - EPITA 2018

> Course materials. Contains voluntary errors and design flaws which are addressed during the courses :)

## Requirements

Although the code should support multiple platforms, only a working code and precompiled libraries for Windows are given.

1. [Visual Studio 2017](https://www.visualstudio.com/downloads/)
2. [Premake 5](https://premake.github.io/download.html)

To generate the solution files, execute:

	premake5.exe vs2017

## External dependencies

1. [cli.cpp](https://github.com/KoltesDigital/cli.cpp), a CLI argument parser (header-only)
2. [ODE](http://www.ode.org/), a physics engine
3. [pugixml](http://pugixml.org/), an XML parser (header-only)
4. [SFML](https://www.sfml-dev.org/), a small multimedia framework

## Session #1

* Architecture principle: rely on lower level, cannot access to higher level.
* Overview of a typical game engine architecture.

## Session #2

* Dependency cycles to be avoided.
* Singletons can facilitate architecture breakings.
* Division of responsibilities.
* Interfaces to break dependency cycles.
* Dependency injection, dependency inversion.
* pImpl.
* void*: C-style pointer to user data.

## Session #3

* RAII.
* Ownership.
* std::unique_ptr.
* std::shared_ptr.
* Move semantics.
* Interface with opaque structures through handlers.

## Session #4

* Specialization through inheritance.
* Specialization through components, entity-component-system.
* Camera system.
* Separation between Model and View.
* Visitor pattern.

## Session #5

* Serialization.
* More visitor pattern.
* Unit tests.
* More separation between Model and View.
