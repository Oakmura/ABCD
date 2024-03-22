 # ABCD Engine
This is an effort to learn inner workings and architecture of Game Engine as I clone code [The Cherno Game Engine Series](https://www.youtube.com/watch?v=JxIZbV_XjAs&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=1)

<a name = "snapshots"></a>
**Snapshot as of now**

**Guizmo**
![Guizmo](https://github.com/Oakmura/ABCD/blob/main/Screenshots/Guizmo.gif)

**Adding Sprite Component**
![Adding Sprite Component](https://github.com/Oakmura/ABCD/blob/main/Screenshots/New_Entity.gif)

**Deserializing**
![Deserializing](https://github.com/Oakmura/ABCD/blob/main/Screenshots/Deserializing.gif)

**Transform Component**
![Transform Component](https://github.com/Oakmura/ABCD/blob/main/Screenshots/TransformComponent.gif)

<a name = "Geting-Started"></a>
## Getting Started

<a name = "Downloading-the-repository"></a>
<ins>**1. Downloading the repository:**</ins>

Start by cloning the repository with `git clone --recursive https://github.com/Oakmura/ABCD`.

If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.

<a name = "Generating-project-files"></a>
<ins>**2. Generating Project Files:**</ins>

Run the [Win-GenProjects.bat](https://github.com/Oakmura/ABCD/blob/main/scripts/Win-GenProjects.bat) file found in `scripts` folder. This will run [premake5.lua](https://github.com/Oakmura/ABCD/blob/main/premake5.lua) with predefined configuration settings to generate Visual Studio 2022 solution and project files.

If you want to generate project files other than VS2022, you can change the "vs2022" found in [Win-GenProjects.bat](https://github.com/Oakmura/ABCD/blob/main/scripts/Win-GenProjects.bat) to other projects supported in [premake](https://premake.github.io/docs/Using-Premake/).

**Please note that if you have non-Ascii characters(i.e. Korean) in cloned path, it may not work due to lack of Unicode support in premake or lua in general.**

<a name = "Building-and-running"></a>
<ins>**3. Building And Running Files:**</ins>

Change Configuration settings to **Distribution** mode. Then, build and run!

## License

This project is licensed under the Apache License - see the  [LICENSE](https://github.com/Oakmura/ABCD/blob/main/LICENSE)  file for details

## Acknowledgements

-  Thank you to [TheCherno](https://www.youtube.com/watch?v=JxIZbV_XjAs&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=1) for providing such informative contents!
