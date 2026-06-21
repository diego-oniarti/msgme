#include "commands.h"
#include "bot.h"

#include <iostream>

#include "ftxui/component/app.hpp"
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/util/ref.hpp"  // for Ref

int config() {
    using namespace ftxui;
    auto screen = App::TerminalOutput();

    std::string token, chat;

    // InputOption tmp;
    // tmp.on_enter = screen.

    Component input_token = Input(&token, "token");
    Component input_chat  = Input(&chat, "chat id");
    Component button_confirm = Button("Confirm", screen.ExitLoopClosure());

    auto component = Container::Vertical({
            input_token,
            input_chat,
            });

    auto renderer = Renderer(component, [&] {
            return vbox({
                    hbox(text(" Bot Token: "), input_token->Render()),
                    hbox(text(" Chat id:   "), input_chat->Render()), text(" (optional)"),
                    });
            });
    screen.Loop(renderer);

    bool created = std::filesystem::create_directories(confdir);
    FILE *conf = fopen(credspath.c_str(), "w");
    fprintf(conf, "%s\n%s\n", token.c_str(), chat.c_str());
    fclose(conf);

    if (chat.empty()) {
        std::cout << "No userid given. Launch assistant? [Y, n]" << std::endl;
        std::string reply;
        getline(std::cin, reply);
        std::transform(reply.begin(), reply.end(), reply.begin(), ::tolower);
        if (reply=="no" || reply=="n") return 0;
        setuser();
    }

    return 0;
}
