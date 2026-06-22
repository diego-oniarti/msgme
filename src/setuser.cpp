#include "bot.h"
#include "commands.h"

#include <atomic>
#include <cstdio>
#include <thread>

#include <tgbot/tgbot.h>

#include "ftxui/component/app.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"

int setuser() {
    using namespace ftxui;

    Bot        *bot   = get_bot();
    TgBot::Bot *tgbot = bot->getTgBot();

    TgBot::TgLongPoll longpoll(*tgbot, 100, 1);

    struct MessageData {
        long        id;
        std::string name;
        std::string last_name;
        std::string text;
    };
    MessageData                current_msg;
    std::atomic<MessageData *> pending{nullptr};

    tgbot->getEvents().onAnyMessage([&](TgBot::Message::Ptr message) {
        if (!pending.load(std::memory_order_relaxed)) {
            pending.store(
                new MessageData{message->chat->id, message->chat->firstName, message->chat->lastName, message->text},
                std::memory_order_release);
        }
    });

    std::atomic<bool> running{true};
    std::thread       poll_thread([&] {
        while (running) {
            try {
                longpoll.start();
            } catch (...) {
                break;
            }
        }
    });

    auto screen = App::TerminalOutput();
    screen.HandlePipedInput(false);

    bool confirm = false;
    int  tab     = 0;

    Component button_yes = Button(
        "Yes",
        [&] {
            confirm = true;
            running = false;
            screen.Exit();
        },
        ButtonOption::Ascii());

    Component button_no = Button("No", [&] { tab = 0; }, ButtonOption::Ascii());

    Component buttons = Container::Horizontal({button_yes, button_no});

    auto waiting = Renderer(
        [&] { return vbox(text("Send a message to the bot") | center, text("Press q to cancel") | center) | center; });

    auto confirming = Renderer(buttons, [&] {
        return vbox(text("Is this you?") | center | bold, separator(),
                    hbox(text("  ID: "), text(std::to_string(current_msg.id))),
                    hbox(text("Name: "), text(current_msg.name + " " + current_msg.last_name)),
                    hbox(text(" Msg: "), text(current_msg.text)), separator(),
                    hbox(button_yes->Render(), button_no->Render())) |
               border;
    });

    auto container = Container::Tab({waiting, confirming}, &tab);

    container |= CatchEvent([&](Event e) {
        if (tab == 0 && e == Event::Character('q')) {
            running = false;
            screen.Exit();
            return true;
        }
        return false;
    });

    auto main_renderer = Renderer(container, [&] {
        auto *data = pending.exchange(nullptr, std::memory_order_acquire);
        if (data) {
            current_msg = std::move(*data);
            delete data;
            tab = 1;
        }
        return container->Render();
    });

    screen.Loop(main_renderer);

    running = false;
    poll_thread.join();

    if (!confirm) return 0;

    FILE *creds = fopen(credspath.c_str(), "r+");
    char  c;
    do {
        c = fgetc(creds);
    } while (c != '\n' && c != EOF);
    fprintf(creds, "%ld\n", current_msg.id);
    fclose(creds);

    return 0;
}
