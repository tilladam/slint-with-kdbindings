

#include <kdbindings/signal.h>

#include <iostream>
#include <memory>
#include <string>

#include "appwindow.h"
#include "backend_controller.h"
#include "undostack_model.h"

using namespace KDBindings;

int main(int argc, char **argv)
{
    auto ui = AppWindow::create();
    auto controller = Controller();
    
    // create a model that adapts the controller state for display
    auto model = UndoStackModel(controller);
    // set the model on the listview
    ui->set_model(std::shared_ptr<UndoStackModel>(&model));

    // Create new signal, superfluous, we could connect directly to the 
    // property's valueChanged, this just adds intermediate information
    // for purposes of illustration
    Signal<std::string, int> signal;

    // when the signal is emitted, we produce output and update the UI
    signal.connect([ui](std::string arg1, int arg2) {
        std::cout << arg1 << " " << arg2 << std::endl;
        ui->set_counter(arg2);
    });

    // when the controller tells us that the thingie changed, we
    // emit an annotated signal
    controller.thingie.valueChanged().connect([&](const int &newValue) {
        signal.emit("New counter value is:", newValue );
    });

    controller.undoPossible.valueChanged().connect([ui](const bool &newValue){
        // the controller says undo availability changed, update UI state
        ui->set_undoPossible(newValue);
    });

    // the UI is calling this callback as a result of a click event
    ui->on_request_increase_value([&controller]{
      // tell the controller to increment the value
      controller.thingie.set(controller.thingie.get() + 1);
    });

    // the UI wants to trigger and undo
    ui->on_request_undo([&controller]{
      controller.undo();
    });

    ui->run();
    return 0;
}
