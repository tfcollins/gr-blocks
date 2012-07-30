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

#ifndef INCLUDED_BLISS_VECTOR_CONJUGATE_H
#define INCLUDED_BLISS_VECTOR_CONJUGATE_H

#include <BLISS_api.h>
#include <gr_block.h>

class BLISS_vector_conjugate;
typedef boost::shared_ptr<BLISS_vector_conjugate> BLISS_vector_conjugate_sptr;

BLISS_API BLISS_vector_conjugate_sptr BLISS_make_vector_conjugate(); // (unsigned int vlen=1);

/*!
 * \brief <+description+>
 *
 */
class BLISS_API BLISS_vector_conjugate : public gr_block
{
	friend BLISS_API BLISS_vector_conjugate_sptr BLISS_make_vector_conjugate(); //(unsigned int  d_vlen);

	BLISS_vector_conjugate(); //(unsigned int  d_vlen);

	//unsigned int  d_vlen;
 public:
	~BLISS_vector_conjugate ();


  int general_work (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
};

#endif /* INCLUDED_BLISS_VECTOR_CONJUGATE_H */

