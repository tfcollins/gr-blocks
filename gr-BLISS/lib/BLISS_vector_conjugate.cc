/* -*- c++ -*- */
/* 
 * Copyright 2012 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gr_io_signature.h>
#include <BLISS_vector_conjugate.h>
#include <complex>
//#include <volk/volk.h>


BLISS_vector_conjugate_sptr
BLISS_make_vector_conjugate() //(unsigned int vlen)
{
	return BLISS_vector_conjugate_sptr (new BLISS_vector_conjugate); //(vlen));
}

static const int MIN_IN = 1;    // mininum number of input streams
static const int MAX_IN = 1;    // maximum number of input streams
static const int MIN_OUT = 1;   // minimum number of output streams
static const int MAX_OUT = 1;   // maximum number of output streams

BLISS_vector_conjugate::BLISS_vector_conjugate() //(unsigned int vlen)
	: gr_block ("vector_conjugate",
		gr_make_io_signature ( MIN_IN, MAX_IN, sizeof (gr_complex)*1024),
		gr_make_io_signature ( MIN_IN, MAX_IN, sizeof (gr_complex)*1024))
{
}


BLISS_vector_conjugate::~BLISS_vector_conjugate ()
{
}


int
BLISS_vector_conjugate::general_work (int noutput_items,
			       gr_vector_int &ninput_items,
			       gr_vector_const_void_star &input_items,
			       gr_vector_void_star &output_items)
{
  const gr_complex *in = (const gr_complex *) input_items[0];
  gr_complex *out = (gr_complex *) output_items[0];
  int noi = noutput_items * 1024;
  

  for (int i = 0; i < noi; i++){
      out[i] = conj(in[i]);
    }

//  unsigned int input_data_size = input_signature()->sizeof_stream_item (0);
//  unsigned int output_data_size = output_signature()->sizeof_stream_item (0);


  // Tell runtime system how many input items we consumed on
  // each input stream.
  consume_each (noutput_items);

  // Tell runtime system how many output items we produced.
  return noutput_items;
}

