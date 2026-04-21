#!/bin/bash
echo "Installazione..."
if [ ! -f "/usr/bin/first" ]; then
   sudo cp -a "./first104-20260416" "/usr/bin/first"
else
   sudo rm "/usr/bin/first"
   sudo cp -a "./first104-20260416" "/usr/bin/first"
fi
if [ ! -f "/usr/bin/firstnum" ]; then
   sudo cp -a "./firstnum109a-20260319" "/usr/bin/firstnum"
else
   sudo rm "/usr/bin/firstnum"
   sudo cp -a "./firstnum109a-20260319" "/usr/bin/firstnum"
fi
if [ -f "/usr/bin/firstnum" ]; then
   sudo chown root:root "/usr/bin/firstnum"
fi
if [ -e "$HOME/.fnl" ]; then
   rm -r "$HOME/.fnl"
fi
cp -r -a "./.fnl" $HOME/
echo "Installazione completata."
