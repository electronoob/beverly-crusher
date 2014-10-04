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
	enum { P_NONE, P_ALSA, P_FILE, P_STDOUT} process_mode = P_NONE;

        int output_to_alsa;
        int output_to_file;
        int output_to_stdout;
        int input_from_file;

        char *dest_filename_buffer;
        char *src_filename_buffer;

        void process(unsigned char mode);
        void showhelp();
	int main(int argc, char *argv[]);
	/* buffer must be multiple of 8 for conversion of stream to binary representation */
	#define BUFFER  256
	#define DEFAULT_BITRATE_DIVISOR 1
#endif
