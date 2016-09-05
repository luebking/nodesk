[submenu] (FluxBox)
    [workspaces] (Workspaces)
    [submenu] (Styles)
        [submenu] (Local)
            [stylesdir] (~/.fluxbox/styles)
        [end]
        [submenu] (System)
            [stylesdir] (/usr/share/fluxbox/styles)
        [end]
        [submenu] (Wallpaper)
            [wallpapers] (~/wallpapers/favorites) {~/.fluxbox/setbg.sh}
        [end]
    [end]
    [config] (Configure)
    [separator]
    [exec] (Rebuild Menu) {mmaker -c -i -t xterm fluxbox > ~/.fluxbox/menu.apps}
    [separator]
    [reconfig] (Reconfig)
    [restart] (Restart)
    [separator]
    [exit] (Exit)
[end]
