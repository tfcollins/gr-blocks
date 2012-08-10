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
#include <bliss_correlator_vcvc.h>
#include <gr_math.h>
#include <volk/volk.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <complex>

using namespace std;

ifstream::pos_type size;
complex<double> * memblock;


bliss_correlator_vcvc_sptr
bliss_make_correlator_vcvc (unsigned int vlen)
{
	return bliss_correlator_vcvc_sptr (new bliss_correlator_vcvc (vlen));
}


bliss_correlator_vcvc::bliss_correlator_vcvc (unsigned int vlen)
	: gr_block ("correlator_vcvc",
		gr_make_io_signature (1, 1, sizeof (gr_complex)*1024),
		gr_make_io_signature (1, 1, sizeof (gr_complex)*1024)),
	d_vlen(vlen)
{
  const int alignment_multiple =
    volk_get_alignment() / sizeof(gr_complex);
  set_alignment(std::max(1,alignment_multiple));
}


bliss_correlator_vcvc::~bliss_correlator_vcvc ()
{
}


int
bliss_correlator_vcvc::general_work (int noutput_items,
			       gr_vector_int &ninput_items,
			       gr_vector_const_void_star &input_items,
			       gr_vector_void_star &output_items)
{
  const gr_complex *in = (const gr_complex *) input_items[0];
  gr_complex *out = (gr_complex *) output_items[0];


  int noi = noutput_items * d_vlen;
  //consume_each (noutput_items);
  consume_each (noi);

  //LOAD Preamble FFT from file
  ifstream file ("/home/traviscollins/data/preamble.txt", ios::in|ios::binary|ios::ate);
  if (file.is_open())
  {
    size = file.tellg();
    //memblock = malloc(sizeof(gr_complex)*size);
    memblock = new complex<double> [size];
    file.seekg (0, ios::beg);
    file.read (memblock, size);
    file.close();

    std::cout << "the complete file content is in memory\n";

    delete[] memblock;
  }
  else cout << "Unable to open file";

  //Cross Correlate FFT with FFT of preamble
  for (int i = 0; i < noi; i++){
      //out[i] = in[i].real ();
      out[i] = preamble[i]*conj(in[i]);
  }

  //Find Beginning of sequence 

  // Tell runtime system how many input items we consumed on
  // each input stream.

    fprintf(stderr,"%f | %f\n",in[2].imag() ,out[2].imag());
//  }


  // Tell runtime system how many output items we produced.
  return noutput_items;
}

