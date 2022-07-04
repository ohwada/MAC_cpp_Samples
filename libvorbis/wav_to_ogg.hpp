#pragma once
/**
 * wav_ogg.hpp
 * 2020-03-01 K.OHWADA
 */


// encode ogg from wav
// original : https://github.com/xiph/vorbis/blob/master/examples/encoder_example.c

/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis SOURCE CODE IS (C) COPYRIGHT 1994-2007             *
 * by the Xiph.Org Foundation http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************

 function: simple example encoder

 ********************************************************************/

/* takes a stereo 16bit 44.1kHz WAV file from stdin and encodes it into
   a Vorbis bitstream */

/* Note that this is POSIX, not ANSI, code */

#include<iostream>
#include <string>
#include <time.h>
#include <math.h>
#include <climits>

#include <vorbis/vorbisenc.h>
#include "wav_header.h"


#define READ 1024
#define BUF_SIZE 4096  // 4*READ

const int ENCODE_SUCCESS = 0;
const int ENCODE_ERR_INPUT = 1;
const int ENCODE_ERR_OUTPUT = 2;
const int ENCODE_ERR_FORMAT = 3;
const int ENCODE_ERR_INIT = 4;
const int ENCODE_ERR_WRITE = 5;

// prototype
int convWavToOgg(std::string input, std::string output);
int wav_to_ogg(char* input, char *output);
std::string addExtOgg( std::string file);


/**
 * convWavToOgg
 */
int convWavToOgg(std::string input, std::string output) 
{
    return wav_to_ogg( (char *) input.c_str(), (char *)output.c_str() );
}


/**
 * wav_to_ogg
 */
int wav_to_ogg(char* input, char *output) 
{

const float ENCODE_QUALITY = 0.1;
const char TAG_KEY[] = "ENCODER";
const char TAG_VALUE[] = "vorbisenc";

/* out of the data segment, not the stack */
signed char *readbuffer = new signed char[BUF_SIZE];

  ogg_stream_state os; /* take physical pages, weld into a logical
                          stream of packets */
  ogg_page         og; /* one Ogg bitstream page.  Vorbis packets are inside */
  ogg_packet       op; /* one raw packet of data for decode */

  vorbis_info      vi; /* struct that stores all the static vorbis bitstream
                          settings */
  vorbis_comment   vc; /* struct that stores all the user comments */

  vorbis_dsp_state vd; /* central working state for the packet->PCM decoder */
  vorbis_block     vb; /* local working space for packet->PCM decode */

  int eos = 0;

   	FILE *fpin = fopen(input, "rb");
	if(!fpin) {
        return ENCODE_ERR_INPUT;
	}


   	FILE *fpout = fopen(output, "wb");
	if(!fpout) {
        return ENCODE_ERR_OUTPUT;
	}

    int wavChannels;
    int wavBit;
    int wavSize;
    int wavSamplingrate;
    int ret1 = readWavHeader(fpin, &wavChannels, &wavBit, &wavSize, &wavSamplingrate);
	if (ret1 != 0){
        return ENCODE_ERR_FORMAT;
	}

    // wav info
    std::cout << "wavChannels: " << wavChannels <<   std::endl;
      std::cout << "wavSamplingrate: " << wavSamplingrate <<   std::endl;
      std::cout << "wavBit: " << wavBit <<   std::endl;
      std::cout << "wavSize: " << wavSize <<   std::endl;



  /********** Encode setup ************/

  vorbis_info_init(&vi);

  /* choose an encoding mode.  A few possibilities commented out, one
     actually used: */

  /*********************************************************************
   Encoding using a VBR quality mode.  The usable range is -.1
   (lowest quality, smallest file) to 1. (highest quality, largest file).
   Example quality mode .4: 44kHz stereo coupled, roughly 128kbps VBR

   ret = vorbis_encode_init_vbr(&vi,2,44100,.4);

   ---------------------------------------------------------------------

   Encoding using an average bitrate mode (ABR).
   example: 44kHz stereo coupled, average 128kbps VBR

   ret = vorbis_encode_init(&vi,2,44100,-1,128000,-1);

   ---------------------------------------------------------------------

   Encode using a quality mode, but select that quality mode by asking for
   an approximate bitrate.  This is not ABR, it is true VBR, but selected
   using the bitrate interface, and then turning bitrate management off:

   ret = ( vorbis_encode_setup_managed(&vi,2,44100,-1,128000,-1) ||
           vorbis_encode_ctl(&vi,OV_ECTL_RATEMANAGE2_SET,NULL) ||
           vorbis_encode_setup_init(&vi));

   *********************************************************************/

  int ret2 = vorbis_encode_init_vbr(&vi, wavChannels, wavSamplingrate, ENCODE_QUALITY);
  if(ret2 != 0){
        return ENCODE_ERR_INIT;
    }

  /* do not continue if setup failed; this can happen if we ask for a
     mode that libVorbis does not support (eg, too low a bitrate, etc,
     will return 'OV_EIMPL') */

  /* add a comment */
  vorbis_comment_init(&vc);
  vorbis_comment_add_tag(&vc, TAG_KEY, TAG_VALUE);

  /* set up the analysis state and auxiliary encoding storage */
  vorbis_analysis_init(&vd, &vi);
  vorbis_block_init(&vd, &vb);

  /* set up our packet->stream encoder */
  /* pick a random serial number; that way we can more likely build
     chained streams just by concatenation */
  srand(time(NULL));
  ogg_stream_init(&os, rand());

  /* Vorbis streams begin with three headers; the initial header (with
     most of the codec setup parameters) which is mandated by the Ogg
     bitstream spec.  The second header holds any comment fields.  The
     third header holds the bitstream codebook.  We merely need to
     make the headers, then pass them to libvorbis one at a time;
     libvorbis handles the additional Ogg bitstream constraints */

  {
    ogg_packet header;
    ogg_packet header_comm;
    ogg_packet header_code;

    vorbis_analysis_headerout(&vd, &vc, &header, &header_comm, &header_code);
    ogg_stream_packetin(&os, &header); /* automatically placed in its own
                                         page */
    ogg_stream_packetin(&os, &header_comm);
    ogg_stream_packetin(&os, &header_code);

    /* This ensures the actual
     * audio data will start on a new page, as per spec
     */
    while(!eos)
    {
        int result = ogg_stream_flush(&os, &og);
        if(result == 0){
            break;
        }
        fwrite(og.header, 1, og.header_len, fpout);
        fwrite(og.body, 1, og.body_len, fpout);
    } // while page header

  } // orbis streams header

// read wav file until end
  while(!eos){
    long i;

 /* stereo hardwired here */
    long bytes = fread(readbuffer, 1, BUF_SIZE, fpin);
    if(bytes==0){
      /* end of file.  this can be done implicitly in the mainline,
         but it's easier to see here in non-clever fashion.
         Tell the library we're at end of stream so that it can handle
         the last frame and mark end of stream in the output properly */
        vorbis_analysis_wrote(&vd, 0);

    }else{
      /* data to encode */

      /* expose the buffer to submit data */
        float **buffer = vorbis_analysis_buffer(&vd, READ);

      /* uninterleave samples */
        for(i=0; i<bytes/4; i++){
            buffer[0][i]=((readbuffer[i*4+1]<<8)|
                      (0x00ff&(int)readbuffer[i*4]))/(float)SHRT_MAX;
            buffer[1][i]=((readbuffer[i*4+3]<<8)|
                      (0x00ff&(int)readbuffer[i*4+2]))/(float)SHRT_MAX;
        } // for

      /* tell the library how much we actually submitted */
        vorbis_analysis_wrote(&vd, i);
    } // if

    /* vorbis does some data preanalysis, then divvies up blocks for
       more involved (potentially parallel) processing.  Get a single
       block for encoding now */
    while(vorbis_analysis_blockout(&vd,&vb)==1){
      /* analysis, assume we want to use bitrate management */
      vorbis_analysis(&vb, NULL);
      vorbis_bitrate_addblock(&vb);

      while(vorbis_bitrate_flushpacket(&vd,&op)){
        /* weld the packet into the bitstream */
        ogg_stream_packetin(&os,&op);

        /* write out pages (if any) */
        while(!eos){
            int result = ogg_stream_pageout(&os, &og);
            if(result == 0){
                break;
            }
            fwrite(og.header, 1, og.header_len, fpout);
            fwrite(og.body, 1, og.body_len, fpout);

          /* this could be set above, but for illustrative purposes, I do
             it here (to show that vorbis does know where the stream ends) */

            if(ogg_page_eos(&og)){
                eos = 1;
            }
        } // while write out pages
      } // while vorbis_bitrate_flushpacket
    } // while vorbis_analysis_blockout
  } // while read


  /* clean up and exit.  vorbis_info_clear() must be called last */
  ogg_stream_clear(&os);
  vorbis_block_clear(&vb);
  vorbis_dsp_clear(&vd);
  vorbis_comment_clear(&vc);
  vorbis_info_clear(&vi);

  /* ogg_page and ogg_packet structs always point to storage in
     libvorbis.  They're never freed or manipulated directly */

	return ENCODE_SUCCESS;
}


/**
 * addExtOgg
 */
std::string addExtOgg( std::string file)
{
    std::string ogg = file + std::string(".ogg");
    return ogg;
}


