#include "commands.h"
#include "bot.h"

#include <iostream>

int config(int argc, char** argv) {
    std::string token, chat;
    std::cout << "Bot token: ";
    std::getline(std::cin, token);
    std::cout << "User id: (leave empty if unknown)";
    std::getline(std::cin, chat);

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
        setuser(argc, argv);
    }

    return 0;
}
