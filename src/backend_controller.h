#pragma once

#include "kdbindings/signal.h"
#include <kdbindings/property.h>
#include <string>
#include <stack>

using KDBindings::Property;
using KDBindings::Signal;
class Controller 
{
public:
    Controller();

    Property<int> thingie{ 42 };
    Property<std::string> textualThingie{ "donkey" };
    Property<bool> undoPossible{ false };
    void undo();
    Signal<int> valueAdded;
    Signal<int> valueUndone;
private:
    std::stack<int> mUndoStack;
};