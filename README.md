![Dr. Crusher portrait by aliceazzo.](http://www.electronoob.com/images/Beverly_Crusher_by_aliceazzo.jpg "The fantastic Beverly Crusher artwork is by aliceazzo and the link to her deviantart is http://aliceazzo.deviantart.com/ - This work is entirely hers and I havent asked permission to associate it with my application, website, nor have I even spoken to this person before so please keep in mind that this image is not part of the same license as this software.")

Image &copy; [aliceazzo](http://aliceazzo.deviantart.com/ "aliceazzo's deviant art page.") [http://aliceazzo.deviantart.com/].


beverly-crusher [http://electronoob.com]
========================================
Released under the terms of the MIT license.
Copyright (c) 2014 electronoob.
All rights reserved.


**Syntax**

To output file direct to alsa default device:

	./crusher --input mysing.raw --alsa


To write conversion to file:

	./crusher --input mysing.raw --output crushed.raw

To dump output to standard output:

	./crusher --input mysing.raw --stdout

To set the output bitrate, enter a positive integer to divide the bitrate by:

	./crusher --input mysing.raw --alsa --bitrate 2



**compile**

	make clean && make all

**about**

i wanted a tool for crushing audio data for use with a microcontroller but i couldn't find one; so i'm writing one.


the idea is very simple actually.

right now the code is incomplete and is very early days of development, it can take a RAW audio data and play it back crushed to 1bit. 

