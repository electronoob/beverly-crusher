#ifndef MAIN_H
#define MAIN_H
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
	/* buffer must be multiple of 8 for conversion of stream to binary representation */
	#define BUFFER  2048
	#define DEFAULT_BITRATE_DIVISOR 1
        #define TMPF_BUFFER_SIZE 1024

	enum { P_NONE, P_ALSA, P_STDOUT} process_mode = P_NONE;

        int output_to_alsa;
        int output_to_stdout;
        int input_from_file;
        int output_bitrate_divisor;

        char *src_filename_buffer;
        char *set_bitrate_buffer;

        unsigned char *rawData;
        unsigned int rawData_len;

        unsigned char *import_file(char *file);
        void process(unsigned char mode);
        void showhelp();
	int main(int argc, char *argv[]);

#endif
