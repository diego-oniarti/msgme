# Setup
```sh
sudo make dependencies
sudo make install
msgmecreds
```

# Usage
To send a single message call `msgme [text]`.  
Calling `msgme` with no arguments enters the interactive mode.  
In interactive mode enter messages preceded by a dash (`-`) or quit with `q`.

# TODO
- [ ] Remove msgmecreds and make them one executable with options
    - [ ] msgme
    - [ ] msgme send [message]
    - [ ] msgme creds
    - [ ] msgme getuser
- [ ] Use an argument parser with nice formatting
