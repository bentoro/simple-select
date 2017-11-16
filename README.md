# simple-select
A tutorial on using select() for linux sockets
- Assuming a socket connection is established using TCP

While loop
- FD_SET is backed up for each iteration
  - memcpy(), copying the backup into the master FD_SET
- select() is called this will wait till "timeout" for any calls from the sockets (this is a blocking call)
  - returns + number indicating a descriptor is ready
  - returns 0 if timeout (Only if a timeout is specified)
  - returns -1 on error
- Iterate through the file descriptors untill an event is found in a socket
- Check if the file descriptor is part of the set you're listening to
- If the file descriptor is part of the set, check which socket the event was from
