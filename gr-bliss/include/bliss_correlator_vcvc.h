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

#ifndef INCLUDED_BLISS_CORRELATOR_VCVC_H
#define INCLUDED_BLISS_CORRELATOR_VCVC_H

#include <bliss_api.h>
#include <gr_block.h>

class bliss_correlator_vcvc;
typedef boost::shared_ptr<bliss_correlator_vcvc> bliss_correlator_vcvc_sptr;

BLISS_API bliss_correlator_vcvc_sptr bliss_make_correlator_vcvc (unsigned int vlen=1);

/*!
 * \brief <+description+>
 *
 */
class BLISS_API bliss_correlator_vcvc : public gr_block
{
	friend BLISS_API bliss_correlator_vcvc_sptr bliss_make_correlator_vcvc (unsigned int vlen);

	bliss_correlator_vcvc (unsigned int vlen);

	unsigned int  d_vlen;

 public:
	~bliss_correlator_vcvc ();


  int general_work (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
};

#endif /* INCLUDED_BLISS_CORRELATOR_VCVC_H */

