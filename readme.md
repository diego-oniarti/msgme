# Setup
```sh
sudo make dependencies
sudo make install
msgme config
```

# Configuration
`msgme config` starts the configuration. Simply enter the bot's token.  
The app will prompt you for the chat id or help you acquire it.  

The chat id can be updated in any moment with `msgme setuser`  

# Usage
To send a single message call `msgme send [text]`.  
To enter interactive mode call `msgme interactive`.  
In interactive mode enter messages preceded by a dash (`-`) or quit with `q`.  

# TODO
- [ ] Use an argument parser with nice formatting
- [ ] Move configuration to FTXUI/ncurses
  - [x] Setuser moved to ncurses
- [ ] Move to CMake
