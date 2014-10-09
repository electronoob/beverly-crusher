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
        #include <unistd.h>
        #include <string.h>
	#include "main.h"
	#include "alsa.h"
	/* http://buildnumber.sourceforge.net/ */
	#include "buildnumber.h"
	#include "binary.h"

	int output_to_alsa;
	int output_to_file;
	int output_to_stdout;
	int input_from_file;
	int output_bitrate_divisor;

	char *dest_filename_buffer;
	char *src_filename_buffer;
	char *set_bitrate_buffer;

	unsigned char *rawData;
	unsigned int rawData_len;

        unsigned char *import_file(char *file) {
                FILE *input;
                input = fopen(file, "rb");
                if (input == NULL) {
                        fprintf(stderr, "Unable to open file for reading.\n");
                        exit(1);
                }
                unsigned int bytes;
                unsigned int the_file_len = 0;
		unsigned char *the_file_data;
                unsigned char *tmp_buffer;
                unsigned char *tmp_ptr;
                tmp_ptr = NULL;
                tmp_buffer = malloc(TMPF_BUFFER_SIZE);
		the_file_data = malloc(TMPF_BUFFER_SIZE);
                memset(the_file_data, 0, TMPF_BUFFER_SIZE);
		while (1) {
                    memset(tmp_buffer, 0, TMPF_BUFFER_SIZE);
                    bytes = fread (tmp_buffer, 1, TMPF_BUFFER_SIZE, input);
                    if(bytes == 0) { break; }
                    if ( (tmp_ptr = realloc(the_file_data, the_file_len+bytes)) == NULL ) {
                        fprintf(stderr, "Unable to realloc().\n");
                        exit(1);
                    } else {
                        the_file_data = tmp_ptr;
                        memcpy(the_file_data + the_file_len, tmp_buffer, bytes);
                    }
                    the_file_len += bytes;
                    if(bytes != TMPF_BUFFER_SIZE) {
                        break;
                    }
		}

		rawData_len = the_file_len;
                free(tmp_buffer);
                fclose(input);
		return the_file_data;
        }

	void process (unsigned char mode)
	{
		unsigned char buf[BUFFER];
		unsigned int process_begun,j,k,err,offset,obsample_bits, obsample_bytes;
		offset = 0; process_begun = 0; obsample_bits = 0; obsample_bytes = 0;

		if(mode == P_STDOUT) {
			printf("\n#include <arduino.h>\n#include <avr/pgmspace.h>\nprog_uchar onebitraw[] PROGMEM = {");
		}
		while (offset != -1) {
			memset(buf, 0, BUFFER);
                        for ( j = 0; j<BUFFER; j++) {
				if (rawData[offset]>128) {
					buf[j] = 255;
				} else {
					buf[j] = 0;
				}
				int z;
				for(z=0;z<output_bitrate_divisor;z++) {
					offset++;
	                                if(offset > rawData_len) {
        	                                offset = -1;
						goto end_of_src_samples;
                	                }
				}
                        }
end_of_src_samples:
			if(mode == P_ALSA) {
	                        if ((err = snd_pcm_writei (playback_handle, buf, BUFFER)) != BUFFER)
					M_ALSA_ERR
			}
			if(mode == P_STDOUT+99) {
				/* get 8 bytes from buffer */
				for ( j = 0; j<BUFFER; j=j+8) {
					if(process_begun) { printf(", "); } else { process_begun = 1; }
					if(!(obsample_bytes % 15)) {printf("\n");}
					/* move through those 8 bytes and convert to binary. 0x00 = 0, 0x255 = 1. */
					unsigned char converted_bits;
					converted_bits = 0;
					for ( k=0; k<8; k++ ) {
						if(k>=BUFFER) {
							/* trying to read past buffer? */
							fprintf (stderr, "Critical error: Tried to exceed BUFFER.\n");
							exit(1);
						}
						converted_bits = converted_bits << 1;
						converted_bits = converted_bits + (buf[j+k] == 255);
						obsample_bits++;
					}
					printf("0x%02X",converted_bits);
					obsample_bytes++;
				}
			}
                }
                if(mode == P_STDOUT) {
                        printf("\n};\n");
			printf("\n#define BC_BIT_COUNT %d\n#define BC_BYTE_COUNT %d\n",obsample_bits, obsample_bytes);
printf("\
#define SPK_PIN 5\n\
\n\
void setup(){ pinMode(SPK_PIN, OUTPUT); }\n\
\n\
void loop(){\n\
        unsigned char bite; int col; col = 0; int i;\n\
        for(i=0;i<BC_BYTE_COUNT;i++){\n\
          bite = pgm_read_byte_near(onebitraw + i);\n\
          unsigned char mask = 1; unsigned char copy = bite; int z;\n\
          for (z=0;z<8;z++) {\n\
            digitalWrite(SPK_PIN, copy & mask);\n\
            copy = copy >> 1;\n\
            delayMicroseconds(%u);\n\
          }\n\
        }\n\
}\n", (unsigned int) ( (float)1000000 / 44100 * output_bitrate_divisor ) );


		}
	}
	void showhelp() {
		printf("example:\n");
		printf("\t./crusher --input mysing.raw --alsa\n");
		printf("\t./crusher --input mysing.raw --arduino --bitrate 10 > arduino_sketch.c\n");
		printf("\t./crusher --input mysing.raw --output crushed.raw\n");
		printf("\t./crusher --input mysing.raw --alsa --bitrate 2\n\n");
	}
	void showabout() {
		/* will need to rename that global to output_to_arduino soon */
		if (output_to_stdout == 1){
			printf("/*\n\n");
		}
                printf("beverly-crusher (build %d) [http://electronoob.com]\n\n",BUILDNUMBER);
                printf("Released under the terms of the MIT license.\nCopyright (c) 2014 electronoob.\nAll rights reserved.\n\n");
		if (output_to_stdout == 1){
			printf("*/\n\n");
		}
	}
	int main (int argc, char *argv[])
	{
		if((BUFFER % 8) != 0) {
			showabout();
			fprintf (stderr, "Critical error: the buffer size (BUFFER) must be a multiple of 8. please fix and recompile me.\n");
			exit(1);
		}

	        output_to_alsa = 0;
        	output_to_file = 0;
		output_to_stdout = 0;
		input_from_file = 0;
		output_bitrate_divisor = DEFAULT_BITRATE_DIVISOR;

		dest_filename_buffer = NULL;
		src_filename_buffer = NULL;
		set_bitrate_buffer = NULL;

		/* begin processing commandline */
		int i;
		for (i=1;i<argc;i++)
		{
			if (strcmp("--arduino", argv[i]) == 0) {
                                output_to_stdout = 1;
                                continue;
                        }
			if (strcmp("--alsa", argv[i]) == 0) {
				output_to_alsa = 1;
				continue;
			}
			if (strcmp("--output", argv[i]) == 0) {
				i++;
				if(argc == i) {
					showabout();
					showhelp();
					fprintf (stderr, "--output [filename] error. missing filename parameter.\n");
					exit(1);
				}
				dest_filename_buffer = malloc(strlen(argv[i]) +1);
				if (dest_filename_buffer == NULL)  {
					showabout();
					fprintf (stderr, "--output [filename] error. unable to malloc() memory.\n");
					exit(1);
				}
				memset(dest_filename_buffer, 0, strlen(argv[i]) +1);
				strcpy(dest_filename_buffer, argv[i]);
				output_to_file = 1;
				continue;
			}
                        if (strcmp("--input", argv[i]) == 0) {
                                i++;
                                if(argc == i) {
					showabout();
					showhelp();
                                        fprintf (stderr, "--input [filename] error. missing filename parameter.\n");
                                        exit(1);
                                }
                                src_filename_buffer = malloc(strlen(argv[i]) +1);
                                if (src_filename_buffer == NULL)  {
					showabout();
                                        fprintf (stderr, "--input [filename] error. unable to malloc() memory.\n");
                                        exit(1);
                                }
                                memset(src_filename_buffer, 0, strlen(argv[i]) +1);
                                strcpy(src_filename_buffer, argv[i]);
				input_from_file = 1;
                                continue;
                        }
                        if (strcmp("--bitrate", argv[i]) == 0) {
                                i++;
                                if(argc == i) {
					showabout();
					showhelp();
                                        fprintf (stderr, "--bitrate [integer] error. missing division parameter.\n");
                                        exit(1);
                                }
                                set_bitrate_buffer = malloc(strlen(argv[i]) +1);
                                if (set_bitrate_buffer == NULL)  {
					showabout();
                                        fprintf (stderr, "--bitrate [integer] error. unable to malloc() memory.\n");
                                        exit(1);
                                }
                                memset(set_bitrate_buffer, 0, strlen(argv[i]) +1);
                                strcpy(set_bitrate_buffer, argv[i]);
				output_bitrate_divisor = atoi(set_bitrate_buffer);
				if (output_bitrate_divisor == 0) {
					showabout();
					fprintf (stderr, "--bitrate [integer] error. division by zero can be fatal.\n");
					exit(1);
				}
				if (output_bitrate_divisor < 0) {
					showabout();
					fprintf (stderr, "--bitrate [integer] error. sub-zero division parameter.\n");
					exit(1);
				}
                                continue;
                        }
			fprintf (stderr, "warning argument '%s' unknown. rtfm.\n", argv[i]);
		}
		if(!input_from_file) {
			showabout();
			showhelp();
			fprintf (stderr, "error: --input not set.\n");
			exit(1);
		} else {
			//printf("input filename is '%s'\n", src_filename_buffer);
		}
		if(output_to_file) {
			//printf("output filename is '%s', however this feature isn't written yet.\n", dest_filename_buffer);
		}
		if (!(output_to_file | output_to_alsa | output_to_stdout)) {
			showabout();
			showhelp();
			fprintf (stderr, "error: at least one output mode required. --alsa --arduino --output filename.\n");
			exit(1);
		}
		/* end processing commandline */

		showabout();

		rawData = import_file(src_filename_buffer);

		if(output_to_alsa) {
			initMyAlsa(output_bitrate_divisor);
			process(P_ALSA);
			destroyMyAlsa();
		}
		if(output_to_file) {
			process(P_FILE);
		}
                if(output_to_stdout) {
                        process(P_STDOUT);
                }

		free(src_filename_buffer);
                free(dest_filename_buffer);
		free(set_bitrate_buffer);
		free(rawData);
		return 0;
	}
