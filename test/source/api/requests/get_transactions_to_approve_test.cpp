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

#include <gtest/gtest.h>
#include <json.hpp>

#include <iota/api/requests/get_transactions_to_approve.hpp>

TEST(GetTransactionToApproveRequest, Ctor) {
  const IOTA::API::Requests::GetTransactionsToApprove req;

  EXPECT_EQ(req.getDepth(), 0);
  EXPECT_EQ(req.getReference(), "");
}

TEST(GetTransactionToApproveRequest, CtorShouldInitFields) {
  const IOTA::API::Requests::GetTransactionsToApprove req{ 42, "ref" };

  EXPECT_EQ(req.getDepth(), 42);
  EXPECT_EQ(req.getReference(), "ref");
}

TEST(GetTransactionToApproveRequest, SetDepth) {
  IOTA::API::Requests::GetTransactionsToApprove req{ 42, "ref" };

  req.setDepth(84);

  EXPECT_EQ(req.getDepth(), 84);
  EXPECT_EQ(req.getReference(), "ref");
}

TEST(GetTransactionToApproveRequest, SetReference) {
  IOTA::API::Requests::GetTransactionsToApprove req{ 42, "ref" };

  req.setReference("ref2");

  EXPECT_EQ(req.getDepth(), 42);
  EXPECT_EQ(req.getReference(), "ref2");
}

TEST(GetTransactionToApproveRequest, SerializeShouldInitJson) {
  const IOTA::API::Requests::GetTransactionsToApprove req{ 42, "ref" };
  json                                                data;

  req.serialize(data);

  EXPECT_EQ(data["command"], "getTransactionsToApprove");
  EXPECT_EQ(data["depth"], 42);
  EXPECT_EQ(data["reference"], "ref");
}
