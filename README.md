# Handmade Instant Image Viewer
Goals:
* Display an image

Non-goals:
* Anything else

There's no screenshot. It's just a plain window with an image inside. Drag to pan view. Scroll to zoom. To open an image provide the path as a first command line argument or drag and drop the file onto the exe.

Other stuff:
* Windows only
* 64-bit only
* C language
* No libraries except *stb_image.h*
* No CRT
* Requires OpenGL 4.6 for no good reason
* Pixel art friendly scaling
* Supports png, jpeg, bmp and gif (no animations)
* Window size adjusts to image size, unless it would be too big

## Building

You need MSVC. Run `Build.bat`. If your `vcvars64.bat` location is different than `C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat` you need to change the path inside the batch file.

## Takeaways

I made it so I can actually use it instead of the Photos app. It's already more usable – it doesn't show a black screen for a second after I open anything, doesn't constrain zooming or panning and doesn't blur pixel art. Still it could use some minor cleanup. Maybe in the future I will add the ability to use left and right arrow keys to go through images in the same directory.

Also:
* C is cool, would recommend
* We can avoid CRT, but then you almost cannot use any other library – wouldn't recommend
* Setting up modern OpenGL in Windows is funny
* Manually loading OpenGL function pointers is a chore even for a small application – just use glad
