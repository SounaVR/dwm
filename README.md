# Souna's Arch Tools 🐧🛠️
Welcome ! Here's one of the tools I use on my Arch installation, and it's obviously subject to evolution and improvement.
The main goal of this kind of repo is to keep "backups" in case I break anything.
Also it'll be very useful for my **future custom arch install interactive script** 🔥.

### Oh ? Interested by using it ? Nothing special but.. Why not.

Just clone the repo by typing the following lines in a terminal

```bash
git clone https://github.com/SounaVR/dwm.git
cd dwm
sudo make install
```

Now you need to add `dwm &` to your startup file, it's the `.xinitrc` file in my case (for X11).

Reboot and you're done!

### Editing the appearance, keybinds...

Edit the `config.def.h` to suit your needs, then do

```bash
rm config.h
make
```

Use (<kbd>super+shift+q</kbd>) to restart dwm.

# ⚠️
You should create a script available in your PATH to prevent your X session for being killed when you use the restart shortcut
```bash
while true; do
    # Log stderror to a file 
    dwm 2> ~/.dwm.log
    # No error logging
    #dwm >/dev/null 2>&1
done
```
Then add it to your startup file instead of `dwm &`

Also the keybinds are setup for the AZERTY layout, you check the diff file [here](https://dwm.suckless.org/patches/azerty/dwm-azerty-6.2.diff).