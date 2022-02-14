#pragma once

#include <slint.h>

#include <vector>

#include "backend_controller.h"

typedef slint::private_api::StandardListViewItem UndoStackEntries;

/**
 * @brief Exposes an undo stack as a Slint model for consumption by ListViews etc.
 * 
 */
class UndoStackModel : public slint::Model<UndoStackEntries> {

public: 
    UndoStackModel( Controller& );
    int row_count() const override;
    std::optional<UndoStackEntries> row_data(int i) const override;
private:
    Controller& mController;
    std::vector<int> mUndoStack;
};