
## Check if $KOS_BASE is set.
if test ! $KOS_BASE; then { echo "ERROR: Set \$KOS_BASE installing kos sdk and kos-ports before continuing."; exit 1; } fi

## Check if KOS_PORTS is set.
if test ! $KOS_PORTS; then { echo "ERROR: Set \$KOS_PORTS installing kos sdk and kos-ports before continuing."; exit 1; } fi

git clone https://github.com/raylib4Consoles/raylib -b raylib4Consoles
cd raylib/src
make 
make install
