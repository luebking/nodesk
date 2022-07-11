/**********************************************************************

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

 Copyright (C) 2022 Thomas Lübking, https://github.com/luebking/nodesk

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this script, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.

**********************************************************************/




/* * * * * * * * * * * * * * * * * * * * * README * * * * * * * * * * * * * * * * * * * * *
===========================================================================================
Build with
            gcc -o xkb_indicator xkb_indicator.c -lX11 -lxkbfile
-------------------------------------------------------------------------------------------
Prints the current xkb group ("layout") to stdout and also sets the name of the root window
accordingly, where some indicator tools pick this up automatically.
Then listens to xkb events and prints/sets updates when toggling between groups.

Pass "2lc" if you want to print/set the ISO3166 2-letter-code rather than a full description,
ie "de" instead of "German", "us" instead of "English (US)", etc.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/XKBlib.h>
#include <X11/extensions/XKBrules.h>

Atom wm_name;
Atom string;

void printGroup(Display *dpy, int grp, Bool useLabel) {

    char *group;
    if (useLabel) {
        group = XGetAtomName(dpy, XkbGetKeyboard(dpy, XkbAllComponentsMask, XkbUseCoreKbd)->names->groups[grp]);
    } else {
        XkbRF_VarDefsRec vd;
        XkbRF_GetNamesProp(dpy, NULL, &vd);

        group = strtok(vd.layout, ",");
        for (int i = 0; i < grp; i++) {
            group = strtok(NULL, ",");
            if (group == NULL) {
                fprintf(stderr, "Group out of bounds: %s\n", grp);
                return;
            }
        }
    }

    printf("%s\n", group);
    XChangeProperty(dpy, RootWindow(dpy, DefaultScreen(dpy)), wm_name, string, 8, PropModeReplace, (unsigned char*)group, strlen(group));
}

int main(int argc, char **argv) {
    Display *dpy = XOpenDisplay(NULL);

    if (dpy == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }
    
    Bool useLabel = (argc < 2 || strcmp(argv[1], "2lc"));
    
    wm_name = XInternAtom(dpy, "WM_NAME", 0);
    string = XInternAtom(dpy, "STRING", 0);

    XkbStateRec state;
    XkbGetState(dpy, XkbUseCoreKbd, &state);
    int lastlang = state.group;
    printGroup(dpy, lastlang, useLabel);
    
    int opcode, xkbEventType, error, major, minor;
    XkbQueryExtension(dpy, &opcode, &xkbEventType, &error, &major, &minor);
    XkbSelectEventDetails(dpy, XkbUseCoreKbd, XkbStateNotify, XkbAllStateComponentsMask, XkbAllStateComponentsMask);

    XEvent event;
    while (1) {
        XNextEvent(dpy, &event);
        if (event.type == xkbEventType) {
            XkbEvent* xkbe = (XkbEvent*)&event;
            if (xkbe->any.xkb_type == XkbStateNotify) {
                if (xkbe->state.group != lastlang) {
                    lastlang = xkbe->state.group;
                    printGroup(dpy, lastlang, useLabel);
                }
            }
        }
    }
}
