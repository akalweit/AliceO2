// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#include "PrintTracks.h"
#include "PrintRofs.h"
#include <fmt/format.h>
#include <string>

namespace o2::mch
{
std::string asString(const o2::mch::TrackMCH& track)
{
  return fmt::format("X {} Y {} Z {}", track.getX(), track.getY(), track.getZ());
}

void printTracksAndRofs(std::ostream& os,
                        gsl::span<const o2::mch::TrackMCH> tracks,
                        gsl::span<const o2::mch::ROFRecord> rofs)
{
  printRofs(os, rofs);
  os << fmt::format("{:=^70}\n", fmt::format("{} tracks", tracks.size()));
  size_t irof{0};
  size_t trackIndex{0};
  for (const auto& r : rofs) {
    os << fmt::format("{:-^95}\n", fmt::format("ROF {:4d} with {:5d} tracks",
                                               irof, r.getNEntries()));
    ++irof;
    size_t i{0};
    for (auto j = r.getFirstIdx(); j <= r.getLastIdx(); j++) {
      const auto& track = tracks[j];
      os << fmt::format("[{:6d}] ({:6d}) {}\n", j, i, asString(track));
      ++trackIndex;
      ++i;
    }
  }
}
} // namespace o2::mch
