/*------------------------------------------------------------------------------------------------
-- SOURCE FILE: select.cpp
--
-- DESIGNER:    Benedict Lo
--
-- PROGRAMMER:  Benedict Lo
--
-- NOTES:       Simple example of select
--------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

main(int argc, char*argv[]){
      int rc;

      // create socket connections
    	Client *RXdata = new Client(connectionIP,7008);
      // set each socket to non-blocking mode
      rc = fcntl(RXdata->GetSocket(),F_SETFL,O_NONBLOCK);
    	if (rc < 0){
	    	 perror("Error setting socket to non-blocking");
	    	exit(3);
    	}
	    Client *TXdata = new Client(connectionIP, 7005);
      rc = fcntl(TXdata->GetSocket(),F_SETFL,O_NONBLOCK);
    	if (rc < 0){
	    	 perror("Error setting socket to non-blocking");
	    	exit(3);
    	}

      // create a back up set and a master set
      fd_set backup
      fd_set master;
      // create timeout struct
    	struct timeval timeout;
      // sets the max descriptor
    	int fdmax;

    	// empty the descriptor set
    	FD_ZERO(&backup);
    	FD_ZERO(&master);

    	// Add sockets to set
      // FD_SET(file descriptor, SET)
      FD_SET(TXdata->GetSocket(),&backup);
    	FD_SET(RXdata->GetSocket(),&backup);

      // set timeout
      // timeout set to 1 minute
      timeout.tv_sec = 60; // seconds
      timeout.tv_usec = 0; // microseconds

      //keep track of the largest file descriptor
      fdmax = RXdata->GetSocket();
      
      whie(1){
      // back up the file descriptors
      // If the descriptors are not backed up, the descriptors will be modified
      // by select after every iteration
      memcpy(&master, &backup, sizeof(backup));

      // select(int maxfd, fd_set *readset, fd_set *writeset, fd_set *exceptset,
      // const struct timeval *timeout)
      // the +1 in maxfd is because POSIX checks for maxfd -1
      rc = select(fdmax + 1, &master, NULL, NULL, timeout);
      // select returns positive for ready file descriptor
      // returns 0 on timeout
      // returns -1 on error

      if (rc < 0){
        perror("ERROR: Select()");
        exit(4);
      }

      // This can be used to see if it timed out can be used in the receiver
      // if (rc == 0){	}

      // loop through the available file descriptors and see which is ready
      int i;
      for (i = 0; i <= fdmax; i++){
        // if descriptor is in the set
        if (FD_ISSET(i, &master)){
          // if descriptor is equal to your specified socket
          if(i == TXdata->Socket()){
            // do something
          }
          // if descriptor is equal to your specified socket
          else if(i == RXdata->Socket()){
            // do something
          }
        }

      }

      }
}
