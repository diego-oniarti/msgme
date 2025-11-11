from logging import error
import sys
import telegram
import asyncio
import os
from dotenv import load_dotenv

load_dotenv()
TOKEN = os.getenv('TOKEN')
CHATID = os.getenv('CHATID')


async def main():
    if (TOKEN is None or CHATID is None):
        print("Please specify TOKEN and CHATID in a .env file")
        return

    bot = telegram.Bot(token=TOKEN)

    argc = len(sys.argv)

    if (argc == 1):
        run = True
        while run:
            opt = input()
            sel = opt[0]
            if sel == "q":
                run = False
            elif sel == "-":
                await bot.send_message(chat_id=CHATID, text=opt[1:])

    if (argc == 2):
        await bot.send_message(chat_id=CHATID, text=sys.argv[1])

    if (argc > 2):
        error("Call with 0 or 1 arguments")

asyncio.run(main())
