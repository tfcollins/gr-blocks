/* -*- c++ -*- */

#define BLISS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "BLISS_swig_doc.i"


%{
//#include "BLISS_equalizer.h"
#include "BLISS_vector_conjugate.h"
%}


//GR_SWIG_BLOCK_MAGIC(BLISS,equalizer);
//%include "BLISS_equalizer.h"

GR_SWIG_BLOCK_MAGIC(BLISS,vector_conjugate);
%include "BLISS_vector_conjugate.h"
