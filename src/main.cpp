#include "appwindow.h"

#include <kdbindings/signal.h>

#include <iostream>
#include <string>

using namespace KDBindings;

int main(int argc, char **argv)
{
    auto ui = AppWindow::create();

    // Create new signal
    Signal<std::string, int> signal;

    // Connect a lambda
    signal.connect([ui](std::string arg1, int arg2) {
        std::cout << arg1 << " " << arg2 << std::endl;
        ui->set_counter(arg2);
    });

    ui->on_request_increase_value([&]{
      // Emit the signal and the lambda is called
      signal.emit("New counter value is:", ui->get_counter() + 1);
    });

    ui->run();
    return 0;
}
