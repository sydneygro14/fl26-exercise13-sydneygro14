// qt_shared_deque_2.cpp
#include <iostream>
#include <cassert>
#include <limits>

#include "shared_ring_buffer.h"

int main(int argc, char *argv[])
{
  SharedRingBuffer<int> buffer;

  buffer.create(100);

  // keeps prompting for numbers for as long as there is space in the buffer
  while(true){
    int value;
    std::cout << "$>";

    // reads an integer from standard input and checks that the read worked
    if(!(std::cin >> value)){

      // exits the loop when standard input is closed, such as with ctrl+d
      if(std::cin.eof()){
        break;
      }

      // clears the error flag and throws away the bad line so typing a non-number does not loop forever
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Not a number, try again" << std::endl;
      continue;
    }

    // enqueues the number right away without waiting for the buffer to be empty
    if(buffer.enqueue(value)){
      std::cout << "Enqueued: " << value << std::endl;
    }
    // enqueue returns false when the buffer is full, so the loop stops since there is no space left
    else{
      std::cout << "Buffer is full, stopping" << std::endl;
      break;
    }
  }

  return 0;
}