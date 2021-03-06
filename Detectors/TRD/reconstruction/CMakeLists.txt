#Copyright CERN and copyright holders of ALICE O2.This software is distributed
#under the terms of the GNU General Public License v3(GPL Version 3), copied
#verbatim in the file "COPYING".
#
#See http: //alice-o2.web.cern.ch/license for full licensing information.
#
#In applying this license CERN does not waive the privileges and immunities
#granted to it by virtue of its status as an Intergovernmental Organization or
#submit itself to any jurisdiction.


o2_add_library(TRDReconstruction
               SOURCES src/CTFCoder.cxx
                       src/CTFHelper.cxx
                       src/DigitsParser.cxx
                       src/TrackletsParser.cxx
                       src/CruRawReader.cxx
                       src/CompressedRawReader.cxx
                       src/DataReaderTask.cxx
                       src/CruCompressorTask.cxx
               PUBLIC_LINK_LIBRARIES O2::TRDBase
                                     O2::DataFormatsTRD
                                     O2::DataFormatsTPC
                                     O2::ReconstructionDataFormats
                                     O2::DetectorsRaw
                                     O2::rANS
                                     Microsoft.GSL::GSL)


o2_add_executable(compressor
    COMPONENT_NAME trd
    SOURCES src/CruCompressor.cxx
    PUBLIC_LINK_LIBRARIES O2::TRDReconstruction
    )

o2_add_executable(datareader
    COMPONENT_NAME trd
    SOURCES src/DataReader.cxx
    PUBLIC_LINK_LIBRARIES O2::TRDReconstruction
    )
