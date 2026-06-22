#include "bot.h"
#include "commands.h"

#include <atomic>
#include <cstring>
#include <tgbot/tgbot.h>

int setuser() {
    Bot        *bot   = get_bot();
    TgBot::Bot *tgbot = bot->getTgBot();

    TgBot::TgLongPoll longpoll(*tgbot, 100, 1);

    std::atomic<int>          received(0);
    std::atomic<long>         id;
    std::atomic<const char *> name;
    std::atomic<const char *> last_name;
    std::atomic<const char *> msg;

    tgbot->getEvents().onAnyMessage([&id, &name, &last_name, &msg, &received](TgBot::Message::Ptr message) {
        received++;
        id        = message->chat->id;
        name      = message->chat->firstName.c_str();
        last_name = message->chat->lastName.c_str();
        msg       = message->text.c_str();
    });

    bool confirm = false;
    bool run     = true;
    while (run) {
        longpoll.start();
        if (received > 0) {
            received--;
        }
    }

    if (!confirm) return 0;

    FILE *creds = fopen(credspath.c_str(), "r+");
    // skip the first line with the token
    char c;
    do {
        c = fgetc(creds);
    } while (c != '\n' && c != EOF);
    fprintf(creds, "%ld\n", id.load());
    fclose(creds);

    return 0;
}
