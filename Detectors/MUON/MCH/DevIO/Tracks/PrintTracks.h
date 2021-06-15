// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#ifndef O2_MCH_DEVIO_TRACKS_PRINTRACKS_H
#define O2_MCH_DEVIO_TRACKS_PRINTRACKS_H

#include <iosfwd>
#include <gsl/span>
#include "DataFormatsMCH/TrackMCH.h"
#include "DataFormatsMCH/ROFRecord.h"

namespace o2::mch
{
void printTracksAndRofs(std::ostream& os,
                        gsl::span<const o2::mch::TrackMCH> tracks,
                        gsl::span<const o2::mch::ROFRecord> rofs);

}
#endif
