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

* Neither the name of unit_tester_template nor the names of its
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

 * statistic_histogram.cpp
 *
 */

#include "CppUTest/TestHarness.h"

#include "statistic_histogram.h"
#include <stdio.h>
#include <vector>

#define NL        "\n"
#define HVAL_ZERO "       0  "
#define HVAL_01   "       1  "

TEST_GROUP(statistic_histogram)
{
    void setup()
    {

    }

    void teardown()
    {

    }
};


TEST(statistic_histogram, empty_histogram_report)
{
    const ssize_t domain_start = 0;
    const size_t  range_size   = 10;
    const ssize_t domain_end   = 32 * range_size;
    Statistic_histogram histogram = Statistic_histogram("TestHistogram", domain_start, domain_end, range_size);

    const size_t BUF_SIZE = 8*1024;
    char report_buf[BUF_SIZE];

    const char expected[] = "TestHistogram Report: (range = 10)" NL
                            "00: " HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO NL
                            "08: " HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO NL
                            "16: " HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO NL
                            "24: " HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO NL;

    histogram.report(report_buf, sizeof(report_buf));

    STRCMP_EQUAL(expected, report_buf);
}

TEST(statistic_histogram, empty_histogram_size19_report)
{
    const ssize_t domain_start = 0;
    const size_t  range_size   = 10;
    const ssize_t domain_end   = 19 * range_size;
    Statistic_histogram histogram = Statistic_histogram("TestHistogram", domain_start, domain_end, range_size);

    const size_t BUF_SIZE = 8*1024;
    char report_buf[BUF_SIZE];

    const char expected[] = "TestHistogram Report: (range = 10)" NL
                            "00: " HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO NL
                            "08: " HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO NL
                            "16: " HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  NL;

    histogram.report(report_buf, sizeof(report_buf));

    STRCMP_EQUAL(expected, report_buf);
}

TEST(statistic_histogram, histogram_add_OOR_values)
{
    const ssize_t domain_start = 0;
    const size_t  range_size   = 10;
    const ssize_t domain_end   = 19 * range_size;
    Statistic_histogram histogram = Statistic_histogram("TestHistogram", domain_start, domain_end, range_size);

    const size_t BUF_SIZE = 8*1024;
    char report_buf[BUF_SIZE];

    const char expected[] = "TestHistogram Report: (range = 10)" NL
                            "00: " HVAL_01    HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO NL
                            "08: " HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO NL
                            "16: " HVAL_ZERO  HVAL_ZERO  HVAL_01    NL;

    histogram.inc_val(domain_start - 10);
    histogram.inc_val(domain_end + 10);

    histogram.report(report_buf, sizeof(report_buf));

    STRCMP_EQUAL(expected, report_buf);
}

TEST(statistic_histogram, histogram_add_EDGE_values)
{
    const ssize_t domain_start = 0;
    const size_t  range_size   = 10;
    const ssize_t domain_end   = 19 * range_size;
    Statistic_histogram histogram = Statistic_histogram("TestHistogram", domain_start, domain_end, range_size);

    const size_t BUF_SIZE = 8*1024;
    char report_buf[BUF_SIZE];

    const char expected[] = "TestHistogram Report: (range = 10)" NL
                            "00: " HVAL_01    HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO NL
                            "08: " HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO NL
                            "16: " HVAL_ZERO  HVAL_ZERO  HVAL_01    NL;

    histogram.inc_val(domain_start);
    histogram.inc_val(domain_end);

    histogram.report(report_buf, sizeof(report_buf));

    STRCMP_EQUAL(expected, report_buf);
}

TEST(statistic_histogram, histogram_add_upper_INNER_values)
{
    const ssize_t domain_start = 0;
    const size_t  range_size   = 10;
    const ssize_t domain_end   = 19 * range_size;
    Statistic_histogram histogram = Statistic_histogram("TestHistogram", domain_start, domain_end, range_size);

    const size_t BUF_SIZE = 8*1024;
    char report_buf[BUF_SIZE];

    const char expected[] = "TestHistogram Report: (range = 10)" NL
                            "00: " HVAL_ZERO  HVAL_01    HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO NL
                            "08: " HVAL_ZERO  HVAL_01    HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO  HVAL_ZERO NL
                            "16: " HVAL_ZERO  HVAL_01    HVAL_ZERO    NL;

    histogram.inc_val(domain_start + 01*range_size);
    histogram.inc_val(domain_start + 10*range_size-1);
    histogram.inc_val(domain_start + 17*range_size+1);

    histogram.report(report_buf, sizeof(report_buf));

    STRCMP_EQUAL(expected, report_buf);
}
