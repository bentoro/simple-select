# simple-select
A tutorial on using select() for linux sockets

Sockets
- Create two socket connections

Initialization
- Create 2 fd_sets one for back up and one for the while loop
- Create a timeout value
- Set fdmax to the max file descriptor 
- Empty FD_SET using FD_ZERO()
- Add the two file descriptors from the created sockets
- Initillize the timeout values

While loop
- FD_SET is backed up for each iteration
  - memcpy(), copys the backup into the master FD_SET
- select() is called this will wait till "timeout" for any calls from the sockets (this is a blocking call)
- Select() has three timeouts
  - Always waiting - setting timeout to NULL will make select always wait for an event
  - Wait untill "timeout" - This is set in the timeval struct
  - Don't wait - If tv_sec and tv_usec in the timeval struct is set to 0 the 
    select will immediately check the descriptors
    - returns positive number indicating a descriptor is ready
    - returns 0 if timeout (Only if a timeout is specified)
    - returns -1 on error
- Iterate through the file descriptors untill an event is found in a socket
- Check if the file descriptor is part of the set you're listening to
- If the file descriptor is part of the set, check which socket the event was from
  - Do something with the socket
