//
// MIT License
//
// Copyright (c) 2017-2018 Thibault Martinez and Simon Ninon
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//

#include <iota/constants.hpp>
#include <iota/errors/illegal_state.hpp>
#include <iota/models/seed.hpp>
#include <iota/types/utils.hpp>

#include <algorithm>
#include <iterator>
#include <random>

namespace IOTA {

namespace Models {

Seed::Seed(const Types::Trytes& seed) {
  setSeed(seed);
}

Seed::Seed(const char* seed) : Seed(Types::Trytes(seed)) {
}

const Types::Trytes&
Seed::toTrytes() const {
  return seed_;
}

void
Seed::setSeed(const Types::Trytes& seed) {
  if (seed.length() > SeedLength) {
    throw Errors::IllegalState("seed is too long");
  }

  if (!Types::isValidTrytes(seed)) {
    throw Errors::IllegalState("seed is not a valid trytes string");
  }

  seed_ = Types::Utils::rightPad(seed, SeedLength, '9');
}

Seed
Seed::generateRandomSeed() {
  std::random_device                 rd;
  std::default_random_engine         dre(rd());
  std::uniform_int_distribution<int> uid(0, TryteAlphabetLength - 1);

  Types::Trytes str;
  str.reserve(SeedLength);
  std::generate_n(std::back_inserter(str), SeedLength, [&]() { return TryteAlphabet[uid(dre)]; });
  return str;
}

bool
Seed::operator==(const Seed& rhs) const {
  return seed_ == rhs.seed_;
}

bool
Seed::operator!=(const Seed& rhs) const {
  return !operator==(rhs);
}

bool
Seed::operator==(const Types::Trytes& rhs) const {
  return operator==(Seed{ rhs });
}

bool
Seed::operator!=(const Types::Trytes& rhs) const {
  return operator!=(Seed{ rhs });
}

}  // namespace Models

}  // namespace IOTA
