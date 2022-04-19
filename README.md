# Welcome to my personal build of dwm

This project exists solely to host my personal patched version of [dwm][1] and make it easily
accessible for all my devices and gain familiarity with working with github. Below is
included the original readme from the [suckless dwm project][2].

[1]: https://dwm.suckless.org/ "dwm homepage" 
[2]: https://git.suckless.org/dwm/ "dwm source code" 

### patches applied are (in no particular order): 
> - [cfacts][3] Allow resizing clients in stack.
> - [adjacent tags][4] Switch to next or previous tag.
> - [attach aside and below][5] Don't push existing clients around when spawning a new one.
> - [hide vacant tags][6] Don't render tag icons in title bar for tags without clients.
> - [in place rotate][7] Rotate clients around their stack, or around master and stack.
> - [pertag - perseltag][8] Allow different master/stack sizes and layouts for tags
> - [dynamic scratchpads][9] Assign windows to scratchpad and hide/show cycle through them
> - [titlecolor][10] Allow coloring the title bar.

[3]: https://dwm.suckless.org/patches/cfacts/ "Clients size factor" 
[4]: https://dwm.suckless.org/patches/focusadjacenttag/ "Focus adjacent tags" 
[5]: https://dwm.suckless.org/patches/attachasideandbelow/ "Attach aside and below" 
[6]: https://dwm.suckless.org/patches/hide_vacant_tags/ "Hide vacant tags" 
[7]: https://dwm.suckless.org/patches/inplacerotate/ "In place rotate" 
[8]: https://dwm.suckless.org/patches/pertag/ "Per (selected) tag" 
[9]: https://dwm.suckless.org/patches/dynamicscratchpads/ "Dynamic scratchpads" 
[10]: https://dwm.suckless.org/patches/titlecolor/ "Title color" 

### configuration changes
> - Colors. Flat black for all backgrounds, same colors for the title as for the rest of
>   the bar. 1 Pixel clear white border.
> - Keybindings. I use the meta (windows) key as a modifier for all window manager related
>   operations to avoid collisions with app specific hotkeys.
> - Added binds for launching specific terminal commands and programs, such as my browser
>   (librewolf) or `top` or `connmanctl` 

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
