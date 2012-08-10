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
#include <fstream>
#include <armadillo>
#include <gr_math.h>

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
		gr_make_io_signature (MIN_IN, MAX_IN, sizeof (float)*1024),
		gr_make_io_signature (MIN_OUT, MAX_OUT, sizeof (float)*1024))
{
set_history(1024+101);//OUTPUT
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
	int vlen=1024;	
	int noi = noutput_items * vlen;

	// Do <+signal processing+>
	fprintf(stderr,"ITEMS: %d\n",noutput_items);

	//Find start of frame
		//Use correlator
	//gr_complex   *dline = fft::malloc_complex(4);
	//memset(dline, 0, INPUT_LEN*sizeof(gr_complex));
	
	fstream sig("/home/traviscollins/data/preamble.dat");
	int N=101;
	int preamble_len=N;
	//vec dataReal(N);
	//vec dataImag(N);
	float dataReal[N];
	//dataReal.fill(0);
	//cx_vec data(N);

	// import real part of data
	for(int i=0;i<N;i++){
		sig >> dataReal[i];
	}
/*	// import imaginary part of data
	for(i=0;i<N;i++){
		sig >> dataImag(i);
	}
	// construct data vector
	data=cx_vec(dataReal,dataImag);
*/

	/////////CORRELATE//////////
	//ASSUMES Preamble is shorted than input vector
	gr_complex new_preamble[noutput_items+2*vlen];
	//new_preamble.fill(0);
	//Zero pad preamble
	int h_saved;
	for(int h=0;h<preamble_len;h++){
		//fprintf(stderr,"dataReal %f\n",dataReal[h]);
		new_preamble[h]=dataReal[h];
		h_saved=h;
	}
	for(int m=h_saved;m<noutput_items+vlen;m++){
		//fprintf(stderr,"REACHED\n");
		new_preamble[m]=gr_complex(0,0);
	}


	//cross correlate
	int corr_len=2*vlen-1;
	gr_complex corr[corr_len];
	fprintf(stderr,"REACHED\n");

	for(int j=0;j<corr_len;j++){
		for(int k=0;k<vlen;k++){
			//fprintf(stderr,"in[%d]\n",k);
			try{
				corr[j]=corr[j]+in[k]*new_preamble[j+k];
			}
			catch(int e){
				fprintf(stderr,"%d %d %d\n",j,k,j+k);
			}
		}
	}
	fprintf(stderr,"REACHED\n");
	
	//fprintf(stderr,"%f + %fj\n",real(correlation[j]), imag(correlation[j]));	

	//Find first occurance of preamble
	int threshold=10; //adjust
	int g_saved;
	for(int g=0;g<corr_len;g++)
		if (real(corr[g])>=threshold){
			g_saved=g;
			break;
	}
	//Readjust with actual start of preamble
	int start = g_saved-preamble_len;
	fprintf(stderr,"TH: %d %f\n",start,real(corr[g_saved]));
	


/*	//////////Equalizer///////////
	//Create vector
	cx_vec r=;
	cx_vec s=;
	int delta=0;	//use delay <=n*length(b)

	for(i=0;i<vlen;i++)//received reversed
		r[i]=in[vlen-i];
	for(i=0;i<preamble_len;i++)//preamble reversed
		s[i]=prealbme[preamble_len-i];
	

	int n=9;	//length of equalizer - 1
	int p=noutputs-delta;
	mat R=toeplitz(r(n+1:p),r(n+1:-1:1));	//build matrix R
	mat S=s(n+1-delta:p-delta)';	// and vector S
	mat S=
	vec f=inv(R'*R)*R'*S;	//calculate equalizer f
	Jmin=S'*S-S'*R*inv(R'*R)*R'*S;	//Jmin for this f and delta



*/


	//Compare know symbols to received and calculate channel estimate
	for(int i=0;i<noutput_items;i++){
		out[i]=in[i];
		//fprintf(stderr,"%f\n",out[i]);

	}
	// Tell runtime system how many output items we produced.
	return noutput_items;
}

