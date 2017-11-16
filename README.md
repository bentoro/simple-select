# simple-select
A tutorial on using select() for linux sockets
- Assuming a socket connection is established using TCP

While loop
- FD_SET is backed up for each iteration
- select() is called this will wait till "timeout" for any calls from the sockets (this is a blocking call)
- Iterate through the file descriptors untill an event is found in a socket
- Check if the file descriptor is part of the set you're listening to
- If the file descriptor is part of the set, check which socket the event was from
