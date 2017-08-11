# IDReader
Console application for 3M ID Reader.

This is an example of Java implementation of sample program for the popular 3M Reader. 
I decided to share it because it was very difficult for us to find any source code for the usage of 3M Reader on Linux.
We got samples from the company (and I would like to thank them for that) and simplified it in order to ease its implementation in the future.

This software requires:
  - libusb 1.0 (apt-get install libusb)
  - MMMReader Java interface/library (included in the soure code - "mmmreader.jar")
 in order to function normally.
 
 This software is designed specifically for IDs from Azerbaijan. It might not work well with IDs from other countries. 
 However, it gives an idea about how you should initialise the device and use it. 

INSTRUCTIONS:
  1 - Connect the device to usb port
  2 - Run the program with root priveleges (I recommend to export the .jar file and run "sudo java -jar IDReader.jar")
  3 - After it's written to the console "Event: SWIPE_READER_CONNECTED", swipe the ID card and you will see the results.
  
This implementation assumes only 1 swap - after that the device will shut down. However, you can change it by changing the values
of "swipeDone" boolean variable in the Reader class.
