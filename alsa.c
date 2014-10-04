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
	#include "alsa.h"

	void initMyAlsa (int obd)
	{
		int err;
		unsigned int bitrate; bitrate = BITRATE / obd;
		if ((err = snd_pcm_open (&playback_handle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0) M_ALSA_ERR
		if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) M_ALSA_ERR
		if ((err = snd_pcm_hw_params_any (playback_handle, hw_params)) < 0) M_ALSA_ERR
		if ((err = snd_pcm_hw_params_set_access (playback_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) M_ALSA_ERR
		if ((err = snd_pcm_hw_params_set_format (playback_handle, hw_params, SND_PCM_FORMAT_U8)) < 0) M_ALSA_ERR
		if ((err = snd_pcm_hw_params_set_rate_near (playback_handle, hw_params, &bitrate, 0)) < 0) M_ALSA_ERR
		if ((err = snd_pcm_hw_params_set_channels (playback_handle, hw_params, 1)) < 0) M_ALSA_ERR
		if ((err = snd_pcm_hw_params (playback_handle, hw_params)) < 0) M_ALSA_ERR
		snd_pcm_hw_params_free (hw_params);
		if ((err = snd_pcm_prepare (playback_handle)) < 0) M_ALSA_ERR
		snd_pcm_wait(playback_handle,5000);
	}

	void destroyMyAlsa ()
	{
		snd_pcm_nonblock(playback_handle, 0);
		snd_pcm_drain(playback_handle);
		snd_pcm_close (playback_handle);
	}

