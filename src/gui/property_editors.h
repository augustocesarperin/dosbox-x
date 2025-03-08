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

#ifndef DOSBOX_PROPERTY_EDITORS_H
#define DOSBOX_PROPERTY_EDITORS_H

#include "SDL.h"
#include "../libs/gui_tk/gui_tk.h"
#include "setup.h"
#include <string>
#include <stdexcept>

class BadConversion : public std::runtime_error {
public:
    BadConversion(const std::string& s) : std::runtime_error(s) {}
};

class PropertyEditor : public GUI::Window, public GUI::ActionEventSource_Callback {
public:
    PropertyEditor(GUI::Screen *parent, int x, int y, const char *title);
    virtual ~PropertyEditor();
    
    virtual bool prepare(std::string &buffer) = 0;
    virtual void set_property(const char *str) = 0;
    
    void actionExecuted(GUI::ActionEventSource *b, const GUI::String &arg);
    virtual void propChanged() = 0;
    
    Property *prop;
    
protected:
    GUI::Button *cancel, *ok;
};

class PropertyEditorBool : public PropertyEditor {
public:
    PropertyEditorBool(GUI::Screen *parent, int x, int y, Property *prop);
    ~PropertyEditorBool();
    
    bool prepare(std::string &buffer);
    void set_property(const char *str);
    void propChanged();
    
private:
    GUI::Checkbox *input;
};

class PropertyEditorString : public PropertyEditor {
public:
    PropertyEditorString(GUI::Screen *parent, int x, int y, Property *prop);
    ~PropertyEditorString();
    
    bool prepare(std::string &buffer);
    void set_property(const char *str);
    void propChanged();
    
private:
    GUI::Input *input;
};

class PropertyEditorFloat : public PropertyEditor {
public:
    PropertyEditorFloat(GUI::Screen *parent, int x, int y, Property *prop);
    ~PropertyEditorFloat();
    
    bool prepare(std::string &buffer);
    void set_property(const char *str);
    void propChanged();
    
private:
    GUI::Input *input;
};

class PropertyEditorHex : public PropertyEditor {
public:
    PropertyEditorHex(GUI::Screen *parent, int x, int y, Property *prop);
    ~PropertyEditorHex();
    
    bool prepare(std::string &buffer);
    void set_property(const char *str);
    void propChanged();
    
private:
    GUI::Input *input;
};

class PropertyEditorInt : public PropertyEditor {
public:
    PropertyEditorInt(GUI::Screen *parent, int x, int y, Property *prop);
    ~PropertyEditorInt();
    
    bool prepare(std::string &buffer);
    void set_property(const char *str);
    void propChanged();
    
private:
    GUI::Input *input;
};

#endif /* DOSBOX_PROPERTY_EDITORS_H */ 