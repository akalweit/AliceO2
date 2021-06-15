// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#include "PrintRofs.h"
#include <fmt/format.h>
#include <map>

namespace o2::mch
{
std::string asString(o2::mch::ROFRecord rof)
{
  return fmt::format("{} FirstIdx: {:5d} LastIdx: {:5d}",
                     rof.getBCData().asString(), rof.getFirstIdx(), rof.getLastIdx());
}

std::map<o2::mch::ROFRecord, int64_t> computeMinTimeDistances(gsl::span<const o2::mch::ROFRecord> rofs)
{
  std::map<o2::mch::ROFRecord, int64_t> minTimeDistances;

  for (auto i = 0; i < rofs.size(); i++) {
    auto const& r = rofs[i];
    o2::InteractionRecord iri{r.getBCData().bc,
                              r.getBCData().orbit};
    minTimeDistances[r] = std::numeric_limits<int64_t>::max();
    for (auto j = 0; j < rofs.size(); j++) {
      if (i == j) {
        continue;
      }
      o2::InteractionRecord irj{rofs[j].getBCData().bc,
                                rofs[j].getBCData().orbit};
      auto d = irj.differenceInBC(iri);
      if (d >= 0) {
        minTimeDistances[rofs[i]] = std::min(minTimeDistances[rofs[i]], d);
      }
    }
  }
  return minTimeDistances;
}

void printRofs(std::ostream& os, gsl::span<const o2::mch::ROFRecord> rofs)
{
  auto minTimeDistances = computeMinTimeDistances(rofs);

  for (auto i = 0; i < rofs.size(); i++) {
    auto const& r = rofs[i];
    o2::InteractionRecord iri{r.getBCData().bc,
                              r.getBCData().orbit};
    minTimeDistances[r] = std::numeric_limits<int64_t>::max();
    for (auto j = 0; j < rofs.size(); j++) {
      if (i == j) {
        continue;
      }
      o2::InteractionRecord irj{rofs[j].getBCData().bc,
                                rofs[j].getBCData().orbit};
      auto d = irj.differenceInBC(iri);
      if (d >= 0) {
        minTimeDistances[rofs[i]] = std::min(minTimeDistances[rofs[i]], d);
      }
    }
  }

  os << fmt::format("{:=^70}\n", fmt::format("{} rofs", rofs.size()));
  size_t i{0};
  for (const auto& r : rofs) {
    os << fmt::format("[{:6d}] {}", i, asString(r));
    if (minTimeDistances[r] < 4) {
      os << fmt::format(" min distance {} !", minTimeDistances[r]);
    }
    os << "\n";
    ++i;
  }
}
} // namespace o2::mch
