/*
Copyright (c) 2015, Edward Haas
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
  
* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
  
* Neither the name of st_histogram nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.
  
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

statistic_histogram.cpp

*/

#include "statistic_histogram.h"

#include <stdio.h>
#include <vector>


Statistic_histogram::Statistic_histogram(std::string h_name, const ssize_t domain_start, const ssize_t domain_end, const size_t range_size) :
    name(h_name),
    dstart(domain_start),
    dend(domain_end),
    rsize(range_size)
{
    for(ssize_t i = dstart; i < dend; i += rsize)
        hval.push_back(0);
}

void Statistic_histogram::inc_val(uint64_t val)
{
    int range = (val - dstart) / rsize;

    if(range < 0)
        range = 0;
    else if((unsigned)range >= hval.size())
        range = hval.size() - 1;

    ++hval[range];
}

size_t Statistic_histogram::report(char * report_buffer, size_t report_buffer_size)
{
    char * buf = report_buffer;
    int  len;

    len = snprintf(buf, report_buffer_size, "%s Report: (range = %lu)", name.c_str(), rsize);
    buf += len;
    report_buffer_size -= len;

    int entry_id = 0;
    for(hv_iterator range_itr = hval.begin(); range_itr != hval.end(); ++range_itr, ++entry_id)
    {
        if((0 == entry_id) || ( 0x0 == (entry_id & 0x07)))
        {
            len = snprintf(buf, report_buffer_size, "\n""%02u: ", entry_id);
            buf += len;
            report_buffer_size -= len;
        }

        len = snprintf(buf, report_buffer_size, "%8lu  ", *range_itr);
        buf += len;
        report_buffer_size -= len;
    }

    len = snprintf(buf, report_buffer_size, "\n");
    buf += len;
    report_buffer_size -= len;

    return (buf - report_buffer);
}


