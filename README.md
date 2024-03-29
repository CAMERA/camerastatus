camerastatus
============

CAMERA status is a ncurses based UI providing status of CAMERA system

![Image](doc/screenshot.png)


Requirements
============

The following applications are libraries are required to compile and run
camera status.  

 autoconf
 
 make
 
 g++
 
 ncurses or ncursesw library
 
 libcurl >= 7.15.5
 
 libtool
 

 libcppunit (to build and run the test cases)


Compiling
=========

 ./autogen.sh
 
 ./configure
 
 make
 
 make test (requires libcppunit)
 
 make install

Installation on Ubuntu 12.04
============================

Several packages need to be installed to compile and run camerastatus on Ubuntu.  To
install these packages run this command from a terminal:
 
 sudo apt-get install autoconf libncurses5-dev libcurl4-openssl-dev curl libtool g++

After running the above command simply follow the steps above in the "Compiling" section




Copyright Notice
================

Copyright 2012   The Regents of the University of California
All Rights Reserved
 
Permission to copy, modify and distribute any part of this camerastatus for educational, research and non-profit purposes, without fee, and without a written agreement is hereby granted, provided that the above copyright notice, this paragraph and the following three paragraphs appear in all copies.
 
Those desiring to incorporate this camerastatus into commercial products or use for commercial purposes should contact the Technology Transfer Office, University of California, San Diego, 9500 Gilman Drive, Mail Code 0910, La Jolla, CA 92093-0910, Ph: (858) 534-5815, FAX: (858) 534-7345, E-MAIL:invent@ucsd.edu.
 
IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF THIS camerastatus, EVEN IF THE UNIVERSITY OF CALIFORNIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
THE camerastatus PROVIDED HEREIN IS ON AN "AS IS" BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.  THE UNIVERSITY OF CALIFORNIA MAKES NO REPRESENTATIONS AND EXTENDS NO WARRANTIES OF ANY KIND, EITHER IMPLIED OR EXPRESS, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, OR THAT THE USE OF THE camerastatus WILL NOT INFRINGE ANY PATENT, TRADEMARK OR OTHER RIGHTS. 

