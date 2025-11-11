#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
int main (int argc, char *argv[]) {
    std::string token, chat;
    std::cout << "Bot token: ";
    std::cin >> token;
    std::cout << "User id: ";
    std::cin >> chat;

    std::filesystem::path home = std::getenv("HOME");
    std::filesystem::path confdir = home / ".config" / "msgme";
    std::filesystem::path confpath = confdir / "creds";

    bool created = std::filesystem::create_directories(confdir);

    FILE *conf = fopen(confpath.c_str(), "w");
    fprintf(conf, "%s\n%s\n", token.c_str(), chat.c_str());
    fclose(conf);

    return 0;
}
