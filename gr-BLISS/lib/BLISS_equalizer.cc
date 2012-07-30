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
#include <BLISS_equalizer.h>
#include <iostream>
#include <stdio.h>
#include <ncurses.h>
//#include <gr_conjugate_cc.h>
#include <complex>
#include <fft/fft.h>

using namespace std;

BLISS_equalizer_sptr
BLISS_make_equalizer ()
{
	return BLISS_equalizer_sptr (new BLISS_equalizer ());
}


static const int MIN_IN = 1;    // mininum number of input streams
static const int MAX_IN = 1;    // maximum number of input streams
static const int MIN_OUT = 1;   // minimum number of output streams
static const int MAX_OUT = 1;   // maximum number of output streams


BLISS_equalizer::BLISS_equalizer ()
	: gr_sync_block ("equalizer",
		gr_make_io_signature (MIN_IN, MAX_IN, sizeof (float)),
		gr_make_io_signature (MIN_OUT, MAX_OUT, sizeof (float)))
{
set_history(4);//OUTPUT
}


BLISS_equalizer::~BLISS_equalizer ()
{
}


int
BLISS_equalizer::work (int noutput_items,
			gr_vector_const_void_star &input_items,
			gr_vector_void_star &output_items)
{
	

	//const gr_complex  *in = (const gr_complex *) input_items[0];
	//gr_complex *out = (gr_complex *) output_items[0];

	const float *in = (const float *) input_items[0];
	float *out = (float *) output_items[0];

	// Do <+signal processing+>
	fprintf(stderr,"ITEMS: %d\n",noutput_items);
	

	//Find start of frame
		//Use correlator
	//Fastest cross-correlation is CORR=G(f) x H(f)* 
	//if all real then H(f)* = H(-f)
	int fft_size=4;
	gr_complex preamble[4];	
	preamble[0]=(10.0,2);
	preamble[1]=(10.0,2); 
	preamble[2]=(10.0,2); 
	preamble[3]=(10.0,2); 

	gr_complex correlation[fft_size];
	//gr_complex   *dline = fft::malloc_complex(4);

	//memset(dline, 0, INPUT_LEN*sizeof(gr_complex));
	
	for(int j=0;j<fft_size;j++){
		correlation[j]=in[j]*conj(preamble[j]);
		fprintf(stderr,"%f + %fj\n",real(correlation[j]), imag(correlation[j]));	
	}	


	//Compare know symbols to received and calculate channel estimate
	for(int i=0;i<noutput_items;i++){
		out[i]=in[i];
		//fprintf(stderr,"%f\n",out[i]);

	}
	// Tell runtime system how many output items we produced.
	return noutput_items;
}

