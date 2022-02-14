#include "undostack_model.h"
#include <optional>
#include <vector>

using namespace KDBindings;

UndoStackModel::UndoStackModel(Controller& c)
:slint::Model<UndoStackEntries>(), mController(c)
{
    mController.valueAdded.connect([&](int value) {
        row_added(row_count(), 1);
        mUndoStack.push_back(value);
    });
    mController.valueUndone.connect([&](int) {
        row_removed(row_count()-1, 1);
        mUndoStack.pop_back();
    });
}

int UndoStackModel::row_count() const 
{
    return mUndoStack.size();
}

std::optional<UndoStackEntries> UndoStackModel::row_data(int i) const 
{
    std::cout << " row data at: " << i << std::endl;
    assert (i < mUndoStack.size() );
    auto undi = UndoStackEntries();
    undi.text = std::to_string(mUndoStack[i]);
    return undi;
}
