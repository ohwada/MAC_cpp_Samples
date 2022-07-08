#pragma once
/**
 * encoder.h
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/xiph/vorbis/blob/master/examples/encoder_example.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <vorbis/vorbisenc.h>
#include "wav_header.h"

// prototype
int encode(FILE *fpin, FILE *fpout);


#define READ 1024
signed char readbuffer[READ*4+44]; /* out of the data segment, not the stack */


/**
 * encoder
 */
int encode(FILE *fpin, FILE *fpout)
{
const float BASE_QUALITY = 0.1;

// 16 bit per sample
const float MAX_VAL = (float)(SHRT_MAX+1); // 32768

  ogg_stream_state os; /* take physical pages, weld into a logical
                          stream of packets */
  ogg_page         og; /* one Ogg bitstream page.  Vorbis packets are inside */
  ogg_packet       op; /* one raw packet of data for decode */

  vorbis_info      vi; /* struct that stores all the static vorbis bitstream
                          settings */
  vorbis_comment   vc; /* struct that stores all the user comments */

  vorbis_dsp_state vd; /* central working state for the packet->PCM decoder */
  vorbis_block     vb; /* local working space for packet->PCM decode */

  int eos=0,ret;
  int i, founddata;

#if defined(macintosh) && defined(__MWERKS__)
  int argc = 0;
  char **argv = NULL;
  argc = ccommand(&argv); /* get a "command line" from the Mac user */
                          /* this also lets the user set stdin and stdout */
#endif

  /* we cheat on the WAV header; we just bypass 44 bytes (simplest WAV
     header is 44 bytes) and assume that the data is 44.1khz, stereo, 16 bit
     little endian pcm samples. This is just an example, after all. */

  /* we cheat on the WAV header; we just bypass the header and never
     verify that it matches 16bit/stereo/44.1kHz.  This is just an
     example, after all. */
int wav_chs;
int wav_bits;
int wav_size;
int wav_rate;
int ret1 = readWavHeader(fpin, &wav_chs, &wav_bits, &wav_size, &wav_rate);
if(ret1 == 0){
    printf(" wav_channels: %d \n", wav_chs);
    printf(" wav_bits: %d \n", wav_bits);
    printf(" wav_size: %d \n", wav_size);
    printf(" wav_rate: %d \n", wav_rate);
} else {
    fprintf(stderr, "cannot read wav file");
    return 1;
}

  readbuffer[0] = '\0';
  for (i=0, founddata=0; i<30 && ! feof(fpin) && ! ferror(fpin); i++)
  {
    fread(readbuffer, 1, 2, fpin);

    if ( ! strncmp((char*)readbuffer, "da", 2) ){
      founddata = 1;
      fread(readbuffer, 1, 6, fpin);
      break;
    }
  }

  /********** Encode setup ************/

  vorbis_info_init(&vi);

  /* choose an encoding mode.  A few possibilities commented out, one
     actually used: */

  /*********************************************************************
   Encoding using a VBR quality mode.  The usable range is -.1
   (lowest quality, smallest file) to 1. (highest quality, largest file).
   Example quality mode .4: 44kHz stereo coupled, roughly 128kbps VBR

   ret = vorbis_encode_init_vbr(&vi, 2, 44100,. 4);

   ---------------------------------------------------------------------

   Encoding using an average bitrate mode (ABR).
   example: 44kHz stereo coupled, average 128kbps VBR

   ret = vorbis_encode_init(&vi, 2, 44100, -1, 128000, -1);

   ---------------------------------------------------------------------

   Encode using a quality mode, but select that quality mode by asking for
   an approximate bitrate.  This is not ABR, it is true VBR, but selected
   using the bitrate interface, and then turning bitrate management off:

   ret = ( vorbis_encode_setup_managed(&vi, 2, 44100, -1, 128000, -1) ||
           vorbis_encode_ctl(&vi,OV_ECTL_RATEMANAGE2_SET,NULL) ||
           vorbis_encode_setup_init(&vi));

   *********************************************************************/

  ret=vorbis_encode_init_vbr(&vi, wav_chs, wav_rate, BASE_QUALITY);

  /* do not continue if setup failed; this can happen if we ask for a
     mode that libVorbis does not support (eg, too low a bitrate, etc,
     will return 'OV_EIMPL') */

  if(ret) return 1;

  /* add a comment */
  vorbis_comment_init(&vc);
  vorbis_comment_add_tag(&vc,"ENCODER","encoder_example.c");

  /* set up the analysis state and auxiliary encoding storage */
  vorbis_analysis_init(&vd,&vi);
  vorbis_block_init(&vd,&vb);

  /* set up our packet->stream encoder */
  /* pick a random serial number; that way we can more likely build
     chained streams just by concatenation */
  srand(time(NULL));
  ogg_stream_init(&os,rand());

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

    vorbis_analysis_headerout(&vd,&vc,&header,&header_comm,&header_code);
    ogg_stream_packetin(&os,&header); /* automatically placed in its own
                                         page */
    ogg_stream_packetin(&os,&header_comm);
    ogg_stream_packetin(&os,&header_code);

    /* This ensures the actual
     * audio data will start on a new page, as per spec
     */
    while(!eos){
      int result=ogg_stream_flush(&os,&og);
      if(result==0)break;
      fwrite(og.header, 1, og.header_len, fpout);
      fwrite(og.body, 1, og.body_len, fpout);
    }

  }

  while(!eos){
    long i;
    long bytes=fread(readbuffer, 1, READ*4, fpin); /* stereo hardwired here */

    if(bytes==0){
      /* end of file.  this can be done implicitly in the mainline,
         but it's easier to see here in non-clever fashion.
         Tell the library we're at end of stream so that it can handle
         the last frame and mark end of stream in the output properly */
      vorbis_analysis_wrote(&vd,0);

    }else{
      /* data to encode */

      /* expose the buffer to submit data */
      float **buffer=vorbis_analysis_buffer(&vd,READ);

      /* uninterleave samples */
      for(i=0;i<bytes/4;i++){
        buffer[0][i]=((readbuffer[i*4+1]<<8)|
                      (0x00ff&(int)readbuffer[i*4]))/MAX_VAL;
        buffer[1][i]=((readbuffer[i*4+3]<<8)|
                      (0x00ff&(int)readbuffer[i*4+2]))/MAX_VAL;
      }

      /* tell the library how much we actually submitted */
      vorbis_analysis_wrote(&vd,i);
    }

    /* vorbis does some data preanalysis, then divvies up blocks for
       more involved (potentially parallel) processing.  Get a single
       block for encoding now */
    while(vorbis_analysis_blockout(&vd,&vb)==1){

      /* analysis, assume we want to use bitrate management */
      vorbis_analysis(&vb,NULL);
      vorbis_bitrate_addblock(&vb);

      while(vorbis_bitrate_flushpacket(&vd,&op)){

        /* weld the packet into the bitstream */
        ogg_stream_packetin(&os,&op);

        /* write out pages (if any) */
        while(!eos){
          int result=ogg_stream_pageout(&os,&og);
          if(result==0)break;
          fwrite(og.header, 1, og.header_len, fpout);
          fwrite(og.body, 1, og.body_len, fpout);

          /* this could be set above, but for illustrative purposes, I do
             it here (to show that vorbis does know where the stream ends) */

          if(ogg_page_eos(&og))eos=1;
        }
      }
    }
  }

  /* clean up and exit.  vorbis_info_clear() must be called last */

  ogg_stream_clear(&os);
  vorbis_block_clear(&vb);
  vorbis_dsp_clear(&vd);
  vorbis_comment_clear(&vc);
  vorbis_info_clear(&vi);

  /* ogg_page and ogg_packet structs always point to storage in
     libvorbis.  They're never freed or manipulated directly */

  fprintf(stderr,"Done.\n");
  return 0;
}

