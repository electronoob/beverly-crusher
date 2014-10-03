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
	#include "buildnumber.h"
	int output_to_alsa;
	int output_to_file;
	int input_from_file;
	char *dest_filename_buffer;
	char *src_filename_buffer;

	void process ()
	{
		unsigned char buf[BUFFER];
		unsigned int i,j,err,offset,rawDataSize;
		offset = 0;
		rawDataSize = sizeof(rawData) / 2 / BUFFER;
	        for (i = 0; i < rawDataSize; ++i) {
                        for ( j = 0; j<BUFFER; j++) {
				if (rawData[offset]>100) {
					buf[j] = 255;
				} else {
					buf[j] = 0;
				}
				offset++;
				offset++;
                        }
			if(output_to_alsa)
	                        if ((err = snd_pcm_writei (playback_handle, buf, BUFFER)) != BUFFER)
					M_ALSA_ERR
                }
	}
	void showhelp() {
		printf("example:\n\n\t./crusher --input mysing.raw --alsa\n\nor\n\n\t./crusher --input mysing.raw --output crushed.raw\n\n");
	}
	int main (int argc, char *argv[])
	{
		printf("beverly-crusher (build %d) [http://electronoob.com]\n\n",BUILDNUMBER);
		printf("Released under the terms of the MIT license.\nCopyright (c) 2014 electronoob.\nAll rights reserved.\n\n");
	        output_to_alsa = 0;
        	output_to_file = 0;
		input_from_file = 0;

		dest_filename_buffer = NULL;
		src_filename_buffer = NULL;

		int i;
		for (i=1;i<argc;i++)
		{
			if (strcmp("--alsa", argv[i]) == 0) {
				output_to_alsa = 1;
				continue;
			}
			if (strcmp("--output", argv[i]) == 0) {
				i++;
				if(argc == i) {
					showhelp();
					fprintf (stderr, "--output [filename] error. missing filename parameter.\n");
					exit(1);
				}
				dest_filename_buffer = malloc(strlen(argv[i]));
				if (dest_filename_buffer == NULL)  {
					fprintf (stderr, "--output [filename] error. unable to malloc() memory.\n");
					exit(1);
				}
				memset(dest_filename_buffer, 0, strlen(argv[i]));
				strcpy(dest_filename_buffer, argv[i]);
				output_to_file = 1;
				continue;
			}
                        if (strcmp("--input", argv[i]) == 0) {
                                i++;
                                if(argc == i) {
					showhelp();
                                        fprintf (stderr, "--input [filename] error. missing filename parameter.\n");
                                        exit(1);
                                }
                                src_filename_buffer = malloc(strlen(argv[i]));
                                if (src_filename_buffer == NULL)  {
                                        fprintf (stderr, "--input [filename] error. unable to malloc() memory.\n");
                                        exit(1);
                                }
                                memset(src_filename_buffer, 0, strlen(argv[i]));
                                strcpy(src_filename_buffer, argv[i]);
				input_from_file = 1;
                                continue;
                        }
			fprintf (stderr, "warning argument '%s' unknown. rtfm.\n", argv[i]);
		}
		if(!input_from_file) {
			showhelp();
			fprintf (stderr, "error: --input not set.\n");
			exit(1);
		} else {
			printf("input filename is '%s'\n", src_filename_buffer);
		}
		if(output_to_file) {
			printf("output filename is '%s'\n", dest_filename_buffer);
		}
		if (!(output_to_file | output_to_alsa)) {
			showhelp();
			fprintf (stderr, "error: at least one output mode required.\n");
			exit(1);
		}
		if(output_to_alsa) { initMyAlsa(); };
		process();
		if(output_to_alsa) { destroyMyAlsa(); }
		if(output_to_file) { free(dest_filename_buffer); }
		free(src_filename_buffer);
		return 0;
	}
