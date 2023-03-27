# Welcome to my personal build of dwm

This project hosts my personal patched version of [dwm][1]  Below is included the original
readme from the [suckless dwm project][2].

Dwm is a dynamic tiling window manager. A window manager is in charge of arranging
graphical windows of user applications across the screen and is a crucial part of any
graphical desktop computer. A dynamic tiling window manager will arrange windows
automatically, based on predictable rules and provides keyboard shortcuts for manipulating
windows. My particular build of dwm is leaning in even more on keyboard controls. Patches
like xtile and moveplace provide immense power of controlling the shape, size, and
location of clients. Cursorwarp minimizes the distance you have you move the mouse. All
this pairs nicely with [xbanish][3], which means you don't even have to see the cursor
when you're not using it. 

[1]: https://dwm.suckless.org/ "dwm homepage" 
[2]: https://git.suckless.org/dwm/ "dwm source code" 
[3]: https://github.com/jcs/xbanish "xbanish"

### Patches applied are (in no particular order): 
> - ~[cfacts][3] Allow resizing clients in stack.~
> - ~[adjacent tags][4] Switch to next or previous tag.~
> - [xtile][5] Control how clients are tiled.
>    - Replaced ~[bottom stack][6]~ and ~[centered master][7]~ layouts. 
> - [attach aside and below][8] Don't push existing clients around when spawning a new one.
> - [hide vacant tags][9] Don't render tag icons in title bar for tags without clients.
> - ~[in place rotate][10] Rotate clients around their stack, or around master and stack.~
> - [pertag - perseltag][11] Allow different master/stack sizes and layouts for tags
> - [dynamic scratchpads][12] Assign windows to scratchpad and hide/show cycle through them
> - [titlecolor][13] Allow colouring the title bar.
> - [center][14] Adds a rule for automatically centring floating clients on launch.
> - [cursorwarp][15] Makes the cursor follow around when focus changes. For example when
>   focussing another monitor or spawning new clients. 
> - [moveplace][16] Shrink current window, make it float, and move it to one
>   combination of top/centre/bottom left/centre/right positions in one move.

[3]: https://dwm.suckless.org/patches/cfacts/ "Clients size factor" 
[4]: https://dwm.suckless.org/patches/focusadjacenttag/ "Focus adjacent tags" 
[5]: https://dwm.suckless.org/patches/xtile/ "New strategy for layouts" 
[6]: https://dwm.suckless.org/patches/bottomstack/ "Bottom stack, no longer included" 
[7]: https://dwm.suckless.org/patches/centeredmaster/ "Centered master, no longer included" 
[8]: https://dwm.suckless.org/patches/attachasideandbelow/ "Attach aside and below" 
[9]: https://dwm.suckless.org/patches/hide_vacant_tags/ "Hide vacant tags" 
[10]: https://dwm.suckless.org/patches/inplacerotate/ "In place rotate" 
[11]: https://dwm.suckless.org/patches/pertag/ "Per (selected) tag" 
[12]: https://dwm.suckless.org/patches/dynamicscratchpads/ "Dynamic scratchpads" 
[13]: https://dwm.suckless.org/patches/titlecolor/ "Title color" 
[14]: https://dwm.suckless.org/patches/center/ "Center rule for floating clients" 
[15]: https://dwm.suckless.org/patches/cursorwarp/ "Move cursor along whenever focus changes" 
[16]: https://dwm.suckless.org/patches/moveplace/ "Move window to one of nine cooridinates" 

### Configuration changes
> - Colours. Flat black for all backgrounds, same colours for the title as for the rest of
>   the bar. Single pixel clear white border.
> - Keybindings. I use the meta (windows) key as a modifier for all window manager related
>   operations to avoid collisions with app specific hotkeys.
> - Added binds for launching specific terminal commands and programs, such as my browser
>   (Librewolf) or `top`, `dmenu`, `passmenu`, `calc`, `cmus`, or `nnn`

### Original README below:

dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.


Requirements
------------
In order to build dwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
