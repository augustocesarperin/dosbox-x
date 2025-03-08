/*
 *  Copyright (C) 2002-2021  The DOSBox Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef DOSBOX_MESSAGE_BOXES_H
#define DOSBOX_MESSAGE_BOXES_H



#include "SDL.h"
#include "../libs/gui_tk/gui_tk.h"

// ShowOptions displays different content based on the title parameter
class ShowOptions : public GUI::MessageBox2 {
public:
    ShowOptions(GUI::Screen *parent, int x, int y, const char *title);
    ~ShowOptions();
};

class LogWindow : public GUI::MessageBox3 {
public:
    LogWindow(GUI::Screen *parent, int x, int y, const char *title);
    ~LogWindow();
};

class CodeWindow : public GUI::MessageBox3 {
public:
    CodeWindow(GUI::Screen *parent, int x, int y, const char *title);
    ~CodeWindow();
};

class HelpWindow : public GUI::MessageBox2 {
public:
    HelpWindow(GUI::Screen *parent, int x, int y, const char *title);
    ~HelpWindow();
};

class ShowMixerInfo : public GUI::ToplevelWindow {
public:
    ShowMixerInfo(GUI::Screen *parent, int x, int y);
    ~ShowMixerInfo();
};

class ShowSBInfo : public GUI::ToplevelWindow {
public:
    ShowSBInfo(GUI::Screen *parent, int x, int y);
    ~ShowSBInfo();
};

class ShowMidiDevice : public GUI::ToplevelWindow {
public:
    ShowMidiDevice(GUI::Screen *parent, int x, int y);
    ~ShowMidiDevice();
};

// Displays information about all mounted drives in the system
class ShowDriveInfo : public GUI::ToplevelWindow {
public:
    ShowDriveInfo(GUI::Screen *parent, int x, int y);
    ~ShowDriveInfo();
};

class ShowIDEInfo : public GUI::ToplevelWindow {
public:
    ShowIDEInfo(GUI::Screen *parent, int x, int y);
    ~ShowIDEInfo();
};

class ShowHelpAbout : public GUI::ToplevelWindow {
public:
    ShowHelpAbout(GUI::Screen *parent, int x, int y);
    ~ShowHelpAbout();
};

class ShowHelpPRT : public GUI::MessageBox2 {
public:
    ShowHelpPRT(GUI::Screen *parent, int x, int y);
    ~ShowHelpPRT();
};

class ShowHelpNIC : public GUI::MessageBox2 {
public:
    ShowHelpNIC(GUI::Screen *parent, int x, int y);
    ~ShowHelpNIC();
};

#endif /* DOSBOX_MESSAGE_BOXES_H */
