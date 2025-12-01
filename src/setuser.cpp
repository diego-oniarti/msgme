#include "commands.h"
#include "bot.h"

#include <atomic>
#include <cstring>
#include <tgbot/tgbot.h>
#include <ncurses.h>
#include <panel.h>
#include <menu.h>

int setuser(int argc, char** argv) {
    const char instruction_msg[] = "Send a message to the bot";
    const char instruction_msg2[] = "Press q to cancel";
    const char confirm_msg[] = "Is this you?";

    Bot *bot = get_bot();
    TgBot::Bot *tgbot = bot->getTgBot();

    initscr();
    curs_set(0);
    cbreak();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    // start_color();
    // use_default_colors();
    // init_pair(1, COLOR_WHITE, COLOR_BLUE);

    TgBot::TgLongPoll longpoll(*tgbot, 100, 1);

    wattron(stdscr, A_BOLD);
    mvprintw(LINES/2, (COLS-strlen(instruction_msg))/2, "%s", instruction_msg);
    mvprintw(LINES/2+1, (COLS-strlen(instruction_msg2))/2, "%s\n", instruction_msg2);
    wattroff(stdscr, A_BOLD);
    refresh();

    std::atomic<int> received(0);
    std::atomic<long> id;
    std::atomic<const char*> name;
    std::atomic<const char*> last_name;
    std::atomic<const char*> msg;

    tgbot->getEvents().onAnyMessage([&id, &name, &last_name, &msg, &received](TgBot::Message::Ptr message) {
            received++;
            id = message->chat->id;
            name = message->chat->firstName.c_str();
            last_name = message->chat->lastName.c_str();
            msg = message->text.c_str();
            });

    const int popup_w = 30;
    const int popup_h = 9;
    WINDOW *popup_window = newwin(popup_h, popup_w, (LINES-popup_h)/2, (COLS-popup_w)/2);
    PANEL *popup_panel = new_panel(popup_window);
    hide_panel(popup_panel);

    bool confirm = false;;
    bool run = true;
    while (run) {
        longpoll.start();
        if (received>0) {
            received--;

            show_panel(popup_panel);
            // wbkgd(popup_window, COLOR_PAIR(1));
            wclear(popup_window);
            wattron(popup_window, A_BOLD);
            box(popup_window, 0, 0);
            mvwprintw(popup_window, 1, (popup_w-strlen(confirm_msg))/2, confirm_msg);
            wattroff(popup_window, A_BOLD);
            mvwprintw(popup_window, 3, 1, "  ID: %ld", id.load());
            mvwprintw(popup_window, 4, 1, "Name: %s %s", name.load(), last_name.load());
            mvwprintw(popup_window, 5, 1, " Msg: %s", msg.load());

            WINDOW *menu_win = derwin(popup_window, 1, 10, 7, (popup_w-10)/2);
            ITEM *yes_item = new_item("YES", "");
            ITEM *no_item = new_item("NO", "");
            ITEM *menu_items[] {yes_item, no_item, NULL};
            MENU *confirm_menu = new_menu((ITEM**)menu_items);
            menu_opts_off(confirm_menu, O_SHOWDESC);
            menu_opts_on(confirm_menu, O_ONEVALUE);

            set_menu_win(confirm_menu, popup_window);
            set_menu_sub(confirm_menu, menu_win);
            set_menu_format(confirm_menu, 1, 2);
            set_menu_spacing(confirm_menu, 2, 0, 0);
            set_menu_mark(confirm_menu, ">");
            post_menu(confirm_menu);

            wrefresh(popup_window);
            update_panels();
            doupdate();

            bool menu_run = true;
            while (menu_run) {
                switch (wgetch(popup_window)) {
                    case 'h':
                    case KEY_LEFT:
                        menu_driver(confirm_menu, REQ_LEFT_ITEM);
                        break;
                    case 'l':
                    case KEY_RIGHT:
                        menu_driver(confirm_menu, REQ_RIGHT_ITEM);
                        break;
                    case KEY_ENTER:
                    case '\n':
                    case ' ':
                        menu_run=false;
                        break;
                }
                wrefresh(popup_window);
            }

            if (current_item(confirm_menu)==yes_item) {
                confirm = true;
                run = false;
            }

            unpost_menu(confirm_menu);
            free_menu(confirm_menu);
            free_item(yes_item);
            free_item(no_item);
            delwin(menu_win);

            hide_panel(popup_panel);
        }else{
            switch (getch()) {
                case ERR:
                    break;
                case 'q':
                    run = false;
                    break;
            }
        }
    }

    del_panel(popup_panel);
    delwin(popup_window);
    endwin();

    if (!confirm) return 0;

    FILE *creds = fopen(credspath.c_str(), "r+");
    // skip the first line with the token
    char c;
    do {
        c = fgetc(creds);
    }while(c!='\n' && c!=EOF);
    fprintf(creds, "%ld\n", id.load());
    fclose(creds);

    return 0;
}
