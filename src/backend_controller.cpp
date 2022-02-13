#include "backend_controller.h"

Controller::Controller()
{
    thingie.valueAboutToChange().connect([&](const int oldValue, const int newValue) {
        // if we are just returning to the top most undo value, don't push it again
        if (!mUndoStack.empty() && newValue == mUndoStack.top())
            return;
        std::cout << "Value is about to change, old value is: " << oldValue << std::endl;
        mUndoStack.push(oldValue);
        undoPossible.set(true);
    });

}

void Controller::undo()
{
    if ( mUndoStack.empty() )
        return;
    thingie.set( mUndoStack.top() );
    mUndoStack.pop();
    if ( mUndoStack.empty() )
        undoPossible.set( false );
}



