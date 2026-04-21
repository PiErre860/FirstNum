#!/bin/bash
echo "Disinstallazione..."
if [ -f "/usr/bin/first" ]; then
   sudo rm "/usr/bin/first"
fi
if [ -f "/usr/bin/firstnum" ]; then
   sudo rm "/usr/bin/firstnum"
fi
if [ -e $HOME/.fstlang.cfg ]; then
   rm "$HOME/.fstlang.cfg"
fi
if [ -e $HOME/.firstlang.cfg ]; then
   rm "$HOME/.firstlang.cfg"
fi
if [ -e "$HOME/.fnl" ]; then
   rm -r "$HOME/.fnl"
fi
echo "Disinstallazione completata."
