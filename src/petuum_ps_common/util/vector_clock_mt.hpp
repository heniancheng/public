// Copyright (c) 2014, Sailing Lab
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the <ORGANIZATION> nor the names of its contributors
// may be used to endorse or promote products derived from this software
// without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
// author: jinliang

#pragma once

#include <petuum_ps_common/util/vector_clock.hpp>
#include <petuum_ps_common/util/lock.hpp>

#include <boost/noncopyable.hpp>
#include <glog/logging.h>
#include <boost/thread.hpp>
#include <vector>
#include <cstdint>

namespace petuum {

// VectorClock is a thread-safe extension of VectorClockST.
class VectorClockMT : public VectorClock, boost::noncopyable {
public:
  VectorClockMT();
  explicit VectorClockMT(const std::vector<int32_t>& ids);

  // Override VectorClock
  void AddClock(int32_t id, int32_t clock = 0);
  int32_t Tick(int32_t id);

  // Accessor to a particular clock.
  int32_t get_clock(int32_t id) const;
  int32_t get_min_clock() const;

private:
  // Lock for slowest record
  mutable SharedMutex mutex_;
};

}  // namespace petuum
