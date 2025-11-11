import telegram
import asyncio
import os
from dotenv import load_dotenv

load_dotenv()
TOKEN = os.getenv('TOKEN')
CHATID = os.getenv('CHATID')

async def main():
    bot = telegram.Bot(token=TOKEN)

    run = True
    while run:
        opt = input()
        sel = opt[0]
        if sel == "q":
            run = False
        elif sel == "-":
            await bot.send_message(chat_id=CHATID, text=opt[1:])

asyncio.run(main())
