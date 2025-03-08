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

#include "message_boxes.h"
#include "setup.h"
#include "menu.h"
#include "midi.h"
#include "bios_disk.h"
#include "../dos/drives.h"
#include <sstream>
#include <iomanip>
#include <vector>

extern std::string helpcmd;

ShowOptions::ShowOptions(GUI::Screen *parent, int x, int y, const char *title)
: MessageBox2(parent, x, y, 460, 350, title) {
    std::vector<std::string> options;
    
    if (std::string(title) == "Audio Options") {
        options.push_back("Sound output rate: " + std::to_string(48000) + " Hz");
        options.push_back("Mixer prebuffer: " + std::to_string(20) + " ms");
        options.push_back("Output mode: Default");
        options.push_back("DMA buffer size: 16 KB");
    } else if (std::string(title) == "Video Options") {
        options.push_back("Video mode: VGA");
        options.push_back("Aspect ratio: 4:3");
        options.push_back("Fullscreen: No");
        options.push_back("V-Sync: Disabled");
        options.push_back("Screen filter: none");
    } else if (std::string(title) == "CPU Options") {
        options.push_back("CPU Core: auto");
        options.push_back("CPU Type: auto");
        options.push_back("Cycles: auto");
        options.push_back("Emulate CPU Speed: Fixed");
    } else {
        options.push_back("No specific options available for this category.");
    }
    
    int y_pos = 10;
    for (const auto& option : options) {
        new GUI::Label(this, 10, y_pos, option);
        y_pos += 25;
    }
}

ShowOptions::~ShowOptions() {
}

LogWindow::LogWindow(GUI::Screen *parent, int x, int y, const char *title)
: MessageBox3(parent, x, y, 550, 400, title) {
    std::vector<std::string> logs;
    logs.push_back("DOSBox-X version " + std::string(VERSION) + " started");
    logs.push_back("GUI: Font size: 14");
    logs.push_back("CPU: Auto cycle mode setting: true");
    logs.push_back("CPU: Core set to AUTO");
    logs.push_back("CPU: Dynamic Block size set to 32kb");
    logs.push_back("MIXER: Sample rate: 48000Hz");
    logs.push_back("MIXER: Using wave: DirectSound");
    logs.push_back("MIDI: Opened device:win32");
    
    std::stringstream log;
    for (const auto& line : logs) {
        log << line << std::endl;
    }
    
    setText(log.str());
}

LogWindow::~LogWindow() {
}

CodeWindow::CodeWindow(GUI::Screen *parent, int x, int y, const char *title)
: MessageBox3(parent, x, y, 600, 450, title) {
    std::string code = "0x0100: MOV AX, 0x0013    ; Set VGA mode 13h\n"
                       "0x0103: INT 0x10          ; BIOS video interrupt\n"
                       "0x0105: MOV AX, 0xA000    ; Set ES to video memory segment\n"
                       "0x0108: MOV ES, AX        ; \n"
                       "0x010A: XOR DI, DI        ; Start from offset 0\n"
                       "0x010C: MOV CX, 64000     ; Number of pixels (320x200)\n"
                       "0x0111: MOV AL, 0x0F      ; White color\n"
                       "0x0113: REP STOSB         ; Fill screen with white pixels\n"
                       "0x0115: RET               ; Return to DOS\n";
                       
    setText(code);
}

CodeWindow::~CodeWindow() {
}

HelpWindow::HelpWindow(GUI::Screen *parent, int x, int y, const char *title)
: MessageBox2(parent, x, y, 550, 350, title) {
    std::string helpText;
    
    if (helpcmd.length()) {
        helpText = "Command Help: " + helpcmd + "\n\n";
        
        if (helpcmd == "cd") {
            helpText += "CD [drive:][path]\n"
                       "CD [..]\n\n"
                       "  Changes the current directory or displays the current directory.\n\n"
                       "  CD..     Changes to the parent directory.\n"
                       "  CD       Displays the current drive and directory.";
        } else if (helpcmd == "dir") {
            helpText += "DIR [drive:][path][filename] [/P] [/W]\n\n"
                      "  Lists files and directories in the specified location.\n\n"
                      "  /P       Pauses after each screenful of information.\n"
                      "  /W       Uses wide list format.";
        } else {
            helpText += "Detailed help for this command is not available.";
        }
    } else {
        helpText = "DOSBox-X Help\n\n"
                 "Press F1 for this help screen.\n"
                 "Press F4 to display the configuration GUI.\n"
                 "Press Alt-F11 to capture/release the mouse.\n"
                 "Press Alt-Enter to toggle fullscreen mode.\n"
                 "Press Ctrl-F5 to save a screenshot.\n"
                 "Press Ctrl-F6 to start/stop recording AVI video.\n"
                 "Press Ctrl-Alt-F5 to start/stop recording audio.\n"
                 "Type 'HELP' at the DOS prompt for DOS command help.";
    }
    
    setText(helpText);
}

HelpWindow::~HelpWindow() {
}

ShowMixerInfo::ShowMixerInfo(GUI::Screen *parent, int x, int y)
: ToplevelWindow(parent, x, y, 450, 300, "Sound Mixer Information") {
    int ypos = 10;
    
    new GUI::Label(this, 10, ypos, "Sound device information:");
    ypos += 30;
    
    new GUI::Label(this, 10, ypos, "Mixer sample rate: 48000 Hz");
    ypos += 20;
    
    new GUI::Label(this, 10, ypos, "Sound output: DirectSound");
    ypos += 20;
    
    new GUI::Label(this, 10, ypos, "Mixer channels:");
    ypos += 30;
    
    std::vector<std::pair<std::string, int>> channels = {
        {"MASTER", 100},
        {"SPEAKER", 100},
        {"GUS", 100},
        {"SB", 100},
        {"FM", 100},
        {"MIDI", 100}
    };
    
    for (const auto& channel : channels) {
        std::string info = channel.first + ": " + std::to_string(channel.second) + "%";
        new GUI::Label(this, 20, ypos, info);
        ypos += 20;
    }
    
    GUI::Button *closeButton = new GUI::Button(this, 370, 270, "Close", 60);
    closeButton->addActionHandler(this);
}

ShowMixerInfo::~ShowMixerInfo() {
}

ShowSBInfo::ShowSBInfo(GUI::Screen *parent, int x, int y)
: ToplevelWindow(parent, x, y, 400, 250, "Sound Blaster Information") {
    int ypos = 10;
    
    new GUI::Label(this, 10, ypos, "Sound Blaster configuration:");
    ypos += 30;
    
    new GUI::Label(this, 10, ypos, "Type: Sound Blaster 16");
    ypos += 20;
    
    new GUI::Label(this, 10, ypos, "Base address: 220h");
    ypos += 20;
    
    new GUI::Label(this, 10, ypos, "IRQ: 7");
    ypos += 20;
    
    new GUI::Label(this, 10, ypos, "DMA: 1 (8-bit), 5 (16-bit)");
    ypos += 20;
    
    new GUI::Label(this, 10, ypos, "MIDI: Enabled");
    ypos += 20;
    
    new GUI::Label(this, 10, ypos, "DSP version: 4.05");
    ypos += 20;
    
    GUI::Button *closeButton = new GUI::Button(this, 320, 220, "Close", 60);
    closeButton->addActionHandler(this);
}

ShowSBInfo::~ShowSBInfo() {
}

ShowMidiDevice::ShowMidiDevice(GUI::Screen *parent, int x, int y)
: ToplevelWindow(parent, x, y, 400, 200, "MIDI Device Information") {
    int ypos = 10;
    
    new GUI::Label(this, 10, ypos, "MIDI configuration:");
    ypos += 30;
    
    new GUI::Label(this, 10, ypos, "Device: " + std::string(MidiHandler_GetName()));
    ypos += 20;
    
    new GUI::Label(this, 10, ypos, "Status: Active");
    ypos += 40;
    
    GUI::Button *closeButton = new GUI::Button(this, 320, 170, "Close", 60);
    closeButton->addActionHandler(this);
}

ShowMidiDevice::~ShowMidiDevice() {
}

ShowDriveInfo::ShowDriveInfo(GUI::Screen *parent, int x, int y)
: ToplevelWindow(parent, x, y, 500, 300, "Drive Information") {
    int ypos = 10;
    
    Section_prop * section=static_cast<Section_prop *>(control->GetSection("dos"));
    std::string drive_z = section->Get_string("drive_z");

    new GUI::Label(this, 10, ypos, "Drive configuration:");
    ypos += 30;
    
    new GUI::Label(this, 10, ypos, "Drive Z: " + drive_z);
    ypos += 20;
    
    new GUI::Label(this, 10, ypos, "Mounted drives:");
    ypos += 30;
    
    for (int i=0; i<DOS_DRIVES; i++) {
        if (Drives[i]) {
            char letter = 'A' + i;
            std::string info = std::string(1, letter) + ": - " + Drives[i]->GetInfo();
            
            new GUI::Label(this, 20, ypos, info);
            ypos += 20;
            
            if (ypos > 250) break;
        }
    }
    
    GUI::Button *closeButton = new GUI::Button(this, 430, 270, "Close", 60);
    closeButton->addActionHandler(this);
}

ShowDriveInfo::~ShowDriveInfo() {
}

ShowIDEInfo::ShowIDEInfo(GUI::Screen *parent, int x, int y)
: ToplevelWindow(parent, x, y, 400, 200, "IDE Information") {
    int ypos = 10;
    
    new GUI::Label(this, 10, ypos, "IDE controller configuration:");
    ypos += 30;
    
    // This would need to pull actual IDE info from IDEController classes
    new GUI::Label(this, 10, ypos, "Primary IDE (1F0h): Active");
    ypos += 20;
    
    new GUI::Label(this, 10, ypos, "Secondary IDE (170h): Active");
    ypos += 20;
    
    new GUI::Label(this, 10, ypos, "Tertiary IDE: Inactive");
    ypos += 20;
    
    new GUI::Label(this, 10, ypos, "Quaternary IDE: Inactive");
    ypos += 40;
    
    GUI::Button *closeButton = new GUI::Button(this, 320, 170, "Close", 60);
    closeButton->addActionHandler(this);
}

ShowIDEInfo::~ShowIDEInfo() {
}

ShowHelpAbout::ShowHelpAbout(GUI::Screen *parent, int x, int y)
: ToplevelWindow(parent, x, y, 450, 300, "About DOSBox-X") {
    int ypos = 10;
    
    new GUI::Label(this, 10, ypos, "DOSBox-X " + std::string(VERSION));
    ypos += 30;
    
    new GUI::Label(this, 10, ypos, "An open-source DOS emulator for Windows, Linux,");
    ypos += 20;
    
    new GUI::Label(this, 10, ypos, "macOS, DOS, and other platforms.");
    ypos += 30;
    
    new GUI::Label(this, 10, ypos, "Based on DOSBox but with many added features.");
    ypos += 40;
    
    new GUI::Label(this, 10, ypos, "Copyright (C) 2002-2021 The DOSBox Team");
    ypos += 20;
    
    new GUI::Label(this, 10, ypos, "Copyright (C) 2012-2021 The DOSBox-X Team");
    ypos += 40;
    
    new GUI::Label(this, 10, ypos, "Website: https://dosbox-x.com");
    ypos += 30;
    
    GUI::Button *closeButton = new GUI::Button(this, 370, 270, "Close", 60);
    closeButton->addActionHandler(this);
}

ShowHelpAbout::~ShowHelpAbout() {
}

ShowHelpPRT::ShowHelpPRT(GUI::Screen *parent, int x, int y)
: MessageBox2(parent, x, y, 580, 350, "Printer Output Help") {
    std::string helpText = 
        "DOSBox-X Printer Support\n\n"
        "DOSBox-X can emulate a printer in the following ways:\n\n"
        "1. Output to a text file (ASCII only)\n"
        "2. Output to a PostScript file (graphics capable)\n"
        "3. Output to a PDF file via a PostScript converter\n"
        "4. Output to a Windows printer (Windows only)\n\n"
        "See the [printer] section in the configuration file for more options.";
    
    setText(helpText);
}

ShowHelpPRT::~ShowHelpPRT() {
}

ShowHelpNIC::ShowHelpNIC(GUI::Screen *parent, int x, int y)
: MessageBox2(parent, x, y, 580, 350, "Network Support Help") {
    std::string helpText = 
        "DOSBox-X Network Support\n\n"
        "DOSBox-X provides network support through the NE2000 adapter emulation.\n\n"
        "To use networking:\n"
        "1. Enable the NE2000 adapter in the [ne2000] section\n"
        "2. Configure the appropriate settings for your host system\n"
        "3. Load a packet driver in DOS (such as NE2000.COM)\n\n"
        "See the documentation for more details on network configuration.";
    
    setText(helpText);
}

ShowHelpNIC::~ShowHelpNIC() {
} 