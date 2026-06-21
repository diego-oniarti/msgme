#include <CLI/CLI.hpp>
#include "src/commands.h"

int main(int argc, char *argv[]) {
    CLI::App app{"msgme - Send messages via Telegram"};
    app.require_subcommand(1);

    std::string msg;
    CLI::App *send_cmd = app.add_subcommand("send", "Send a single message");
    send_cmd->add_option("message", msg, "Text to send")->required();
    send_cmd->callback([&msg]() { send(msg); });

    app.add_subcommand("interactive", "Start interactive mode")
       ->callback(interactive);

    app.add_subcommand("config", "Configure bot token and optionally user id")
       ->callback(config);

    app.add_subcommand("setuser", "Set or update Telegram user id")
       ->callback(setuser);

    CLI11_PARSE(app, argc, argv);
    return 0;
}
