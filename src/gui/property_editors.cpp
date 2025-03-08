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

#include "property_editors.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <functional>

PropertyEditor::PropertyEditor(GUI::Screen *parent, int x, int y, const char *title)
: Window(parent, x, y, 250, 80, title), prop(nullptr) {
    ok = new GUI::Button(this, 200, 60, "OK", 50);
    ok->addActionHandler(this);
    
    cancel = new GUI::Button(this, 140, 60, "Cancel", 50);
    cancel->addActionHandler(this);
}

PropertyEditor::~PropertyEditor() {
}

void PropertyEditor::actionExecuted(GUI::ActionEventSource *b, const GUI::String &arg) {
    if (b == ok) {
        std::string buffer;
        if (prepare(buffer)) {
            prop->SetValue(buffer);
            propChanged();
        }
    }
    
    close();
}

PropertyEditorBool::PropertyEditorBool(GUI::Screen *parent, int x, int y, Property *p)
: PropertyEditor(parent, x, y, "Edit Boolean Property"), input(nullptr) {
    prop = p;
    input = new GUI::Checkbox(this, 20, 30, "Value");
    input->setChecked(prop->GetValue() == "true");
}

PropertyEditorBool::~PropertyEditorBool() {
}

bool PropertyEditorBool::prepare(std::string &buffer) {
    buffer = input->isChecked() ? "true" : "false";
    return true;
}

void PropertyEditorBool::set_property(const char *str) {
    input->setChecked(strcmp(str, "true") == 0);
}

void PropertyEditorBool::propChanged() {
}

PropertyEditorString::PropertyEditorString(GUI::Screen *parent, int x, int y, Property *p)
: PropertyEditor(parent, x, y, "Edit String Property"), input(nullptr) {
    prop = p;
    input = new GUI::Input(this, 20, 30, 210, 16);
    input->setText(prop->GetValue());
}

PropertyEditorString::~PropertyEditorString() {
}

bool PropertyEditorString::prepare(std::string &buffer) {
    buffer = input->getText();
    return true;
}

void PropertyEditorString::set_property(const char *str) {
    input->setText(str);
}

void PropertyEditorString::propChanged() {
}

PropertyEditorFloat::PropertyEditorFloat(GUI::Screen *parent, int x, int y, Property *p)
: PropertyEditor(parent, x, y, "Edit Float Property"), input(nullptr) {
    prop = p;
    input = new GUI::Input(this, 20, 30, 210, 16);
    input->setText(prop->GetValue());
}

PropertyEditorFloat::~PropertyEditorFloat() {
}

bool PropertyEditorFloat::prepare(std::string &buffer) {
    buffer = input->getText();
    
    try {
        std::istringstream iss(buffer);
        float value;
        if (!(iss >> value)) {
            return false;
        }
        std::ostringstream oss;
        oss << value;
        buffer = oss.str();
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

void PropertyEditorFloat::set_property(const char *str) {
    input->setText(str);
}

void PropertyEditorFloat::propChanged() {
}

PropertyEditorHex::PropertyEditorHex(GUI::Screen *parent, int x, int y, Property *p)
: PropertyEditor(parent, x, y, "Edit Hex Property"), input(nullptr) {
    prop = p;
    input = new GUI::Input(this, 20, 30, 210, 16);
    input->setText(prop->GetValue());
}

PropertyEditorHex::~PropertyEditorHex() {
}

bool PropertyEditorHex::prepare(std::string &buffer) {
    buffer = input->getText();
    
    auto trim = [](const std::string& str) {
        auto wsfront = std::find_if_not(str.begin(), str.end(), [](int c) { return std::isspace(c); });
        auto wsback = std::find_if_not(str.rbegin(), str.rend(), [](int c) { return std::isspace(c); }).base();
        return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
    };
    
    std::string trimmed = trim(buffer);
    if (trimmed.size() > 2 && trimmed[0] == '0' && (trimmed[1] == 'x' || trimmed[1] == 'X')) {
        trimmed = trimmed.substr(2);
    }
    
    for (size_t i = 0; i < trimmed.size(); i++) {
        if (!std::isxdigit(static_cast<unsigned char>(trimmed[i]))) {
            return false;
        }
    }
    
    if (trimmed.size() > 0) {
        buffer = "0x" + trimmed;
    } else {
        buffer = "0x0";
    }
    
    return true;
}

void PropertyEditorHex::set_property(const char *str) {
    input->setText(str);
}

void PropertyEditorHex::propChanged() {
}

PropertyEditorInt::PropertyEditorInt(GUI::Screen *parent, int x, int y, Property *p)
: PropertyEditor(parent, x, y, "Edit Integer Property"), input(nullptr) {
    prop = p;
    input = new GUI::Input(this, 20, 30, 210, 16);
    input->setText(prop->GetValue());
}

PropertyEditorInt::~PropertyEditorInt() {
}

bool PropertyEditorInt::prepare(std::string &buffer) {
    buffer = input->getText();
    
    try {
        std::istringstream iss(buffer);
        int value;
        if (!(iss >> value)) {
            return false;
        }
        std::ostringstream oss;
        oss << value;
        buffer = oss.str();
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

void PropertyEditorInt::set_property(const char *str) {
    input->setText(str);
}

void PropertyEditorInt::propChanged() {
} 