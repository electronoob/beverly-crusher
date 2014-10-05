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

I had been looking for a tool to convert audio down to 1-bit depth
but struggled to find one, so I'm writing one which can also do
other neat stuff such as preview with ALSA and downsample the
bitrate easily.


Hackaday.io (https://hackaday.io/project/3119-Beverly-Crusher%3A-bit-crushing-toy-for-1-bit-audio. "project page here").


[![Demo and project information.](http://img.youtube.com/vi/U2mQjJXUQ4k/0.jpg)](http://www.youtube.com/watch?v=U2mQjJXUQ4k)

