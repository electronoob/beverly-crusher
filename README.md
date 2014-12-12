![Dr. Crusher portrait by aliceazzo.](https://hackadaycom.files.wordpress.com/2014/10/9132521412537668507.jpg "The fantastic Beverly Crusher artwork is by aliceazzo and the link to her deviantart is http://aliceazzo.deviantart.com/ - This work is entirely hers and I havent asked permission to associate it with my application, website, nor have I even spoken to this person before so please keep in mind that this image is not part of the same license as this software.")

Image &copy; [aliceazzo](http://aliceazzo.deviantart.com/ "aliceazzo's deviant art page.") [http://aliceazzo.deviantart.com/].


beverly-crusher [http://electronoob.com]
========================================
Released under the terms of the MIT license.
Copyright (c) 2014 electronoob.
All rights reserved.


**Syntax**

To output file direct to alsa default device:

	./crusher --input mysing.raw --alsa


To write conversion to file (this bit isnt written yet):

	./crusher --input mysing.raw --output crushed.raw

To generate Arduino sketch:

	./crusher --input mysing.raw --arduino --bitrate 10 > arduino_sketch.c

To set the output bitrate, enter a positive integer to divide the bitrate by:

	./crusher --input mysing.raw --alsa --bitrate 2



**compile**

	make clean && make all


**about**

I had been looking for a tool to convert audio down to 1-bit depth
but struggled to find one, so I'm writing one which can also do
other neat stuff such as preview with ALSA and downsample the
bitrate easily.


Instructables [project page here](http://www.instructables.com/id/Beverly-Crusher-bit-crushing-1-bit-Arduino-music/ "Instructables").


[![Demo and project information.](http://img.youtube.com/vi/U2mQjJXUQ4k/0.jpg)](http://www.youtube.com/watch?v=U2mQjJXUQ4k)

