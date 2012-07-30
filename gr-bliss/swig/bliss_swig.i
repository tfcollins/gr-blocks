/* -*- c++ -*- */

#define BLISS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "bliss_swig_doc.i"


%{
#include "bliss_correlator_vcvc.h"
%}


GR_SWIG_BLOCK_MAGIC(bliss,correlator_vcvc);
%include "bliss_correlator_vcvc.h"
