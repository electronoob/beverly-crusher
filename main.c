/*

The MIT License (MIT)

Copyright (c) 2014 electronoob.github.io

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
	#include <stdio.h>
	#include <stdlib.h>
	#include "sample.h"
	#include "alsa.h"

	void loop ()
	{
		unsigned char buf[BUFFER];
		unsigned int i,j,err,offset,rawDataSize;
		offset = 0;
		rawDataSize = sizeof(rawData) / 2 / BUFFER;
	        for (i = 0; i < rawDataSize; ++i) {
			usleep(100);
                        for ( j = 0; j<BUFFER; j++) {
				if (rawData[offset]>100) {
					buf[j] = 255;
				} else {
					buf[j] = 0;
				}
				offset++;
				offset++;
                        }
                        if ((err = snd_pcm_writei (playback_handle, buf, BUFFER)) != BUFFER) {
				M_ALSA_ERR
                        }
                }
	}
	void main (int argc, char *argv[])
	{
		initMyAlsa();
		loop();
		destroyMyAlsa();
	}

