#include "bot.h"
#include "commands.h"

#include <filesystem>
#include <iostream>

#include "ftxui/component/app.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/util/ref.hpp"

int config() {
    using namespace ftxui;
    auto screen = App::TerminalOutput();

    std::string token, chat_id;
    bool        abort = false;

    InputOption in_op;
    in_op.multiline = false;

    Component input_token    = Input(&token, "token", in_op);
    Component input_chat     = Input(&chat_id, "chat id", in_op);
    Component button_confirm = Button("confirm", screen.ExitLoopClosure(), ButtonOption::Ascii());
    Component button_abort   = Button(
        "abort",
        [&]() {
            abort = true;
            screen.Exit();
        },
        ButtonOption::Ascii());

    Component buttons   = Container::Horizontal({button_confirm, button_abort});
    Component container = Container::Vertical({input_token, input_chat, buttons});

    int       i       = 0;
    Component comps[] = {input_token, input_chat, buttons};

    auto renderer = Renderer(container, [&] {
        return vbox(hbox(text(" Bot Token*: "), input_token->Render()),
                    hbox(text(" Chat id:    "), input_chat->Render()), separator(),
                    hbox(button_confirm->Render(), button_abort->Render())) |
               border | size(WIDTH, LESS_THAN, 60);
    });

    renderer |= CatchEvent([&](Event e) {
        // Enter works like CtrlN only when navigating the inputs (index 0 and 1)
        if (e == Event::CtrlN || (e == Event::Return && i < 2)) {
            container->SetActiveChild(comps[++i % 3]);
            return true;
        }
        if (e == Event::CtrlP) {
            container->SetActiveChild(comps[(--i + 3) % 3]);
            return true;
        }
        return false;
    });

    screen.Loop(renderer);
    if (abort) return 0;

    bool  created = std::filesystem::create_directories(confdir);
    FILE *conf    = fopen(credspath.c_str(), "w");
    if (conf) {
        fprintf(conf, "%s\n%s\n", token.c_str(), chat_id.c_str());
        fclose(conf);
    }

    if (!chat_id.empty()) return 0;

    screen               = App::TerminalOutput();
    Component button_yes = Button("Yes", screen.ExitLoopClosure(), ButtonOption::Ascii());
    Component button_no  = Button(
        "No",
        [&] {
            abort = true;
            screen.Exit();
        },
        ButtonOption::Ascii());

    Component confirm_container = Container::Horizontal({button_yes, button_no});

    screen.Loop(Renderer(confirm_container, [&] {
        return vbox(text("No user id given.") | center, text("Launch assistant?") | center, separator(),
                    hbox(button_yes->Render(), button_no->Render())) |
               border | size(WIDTH, LESS_THAN, 30);
    }));

    if (abort) return 0;

    setuser();
    return 0;
}
