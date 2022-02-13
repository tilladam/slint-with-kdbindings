#pragma once

#include <kdbindings/property.h>
#include <string>
#include <stack>

using KDBindings::Property;

class Controller 
{
public:
    Controller();

    Property<int> thingie{ 42 };
    Property<std::string> textualThingie{ "donkey" };
    Property<bool> undoPossible{ false };
    void undo();
private:
    std::stack<int> mUndoStack;
};