# Setup
```sh
sudo make dependencies
sudo make install
msgme creds
```

# Usage
To send a single message call `msgme [text]`.  
Calling `msgme` with no arguments enters the interactive mode.  
In interactive mode enter messages preceded by a dash (`-`) or quit with `q`.

# TODO
- [x] Remove msgmecreds and make them one executable with options
    - [x] msgme
    - [x] msgme send [message]
    - [x] msgme creds
    - [ ] msgme getuser
- [ ] Use an argument parser with nice formatting
