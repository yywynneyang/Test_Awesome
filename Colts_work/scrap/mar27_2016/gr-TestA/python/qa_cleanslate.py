#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2016 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import TestA_swig as TestA_swig
from numpy import array
#from cleanslate import cleanslate





class qa_cleanslate (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
		# Here is our test data; we eventually need to add
		# a way to take in csv files.


		# Below we make the declarations
		src_data = (0, 1, -2, 5.5, -0.5)		
		expected_result = (0, 1, -2, 5.5, -0.5)	
				 			
		src = blocks.vector_source_c(src_data) 		
		testblock = cleanslate(true,1)
		sink = blocks.vector_sink_c()


		#  Now we make the connections  
		self.tb.connect(src,testblock) 
		self.tb.connect(testblock,sink)

		#  Run the test and see data 
		self.tb.run()
		result_data = sink.data() # .data() used to get vector from sink


        # check data (checks up to 6 decimal points)
		self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)

		##############################################################
		# Run the test by going to terminal and typing the following:# 
		# 					" python qa_cleanslate.py "				 #
		##############################################################
if __name__ == '__main__':
    gr_unittest.run(qa_cleanslate, "qa_cleanslate.xml")
