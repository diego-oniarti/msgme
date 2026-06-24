# Setup
```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
sudo cmake --install build
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
