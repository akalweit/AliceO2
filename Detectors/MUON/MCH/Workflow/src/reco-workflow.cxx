// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#include "CommonUtils/ConfigurableParam.h"
#include "DetectorsRaw/HBFUtilsInitializer.h"
#include "Framework/ConfigContext.h"
#include "Framework/Logger.h"
#include "Framework/Variant.h"
#include "Framework/WorkflowSpec.h"
#include "MCHWorkflow/PreClusterFinderSpec.h"
#include "MCHWorkflow/ClusterFinderOriginalSpec.h"
#include "ClusterTransformerSpec.h"
#include "TrackFinderSpec.h"

using o2::framework::ConfigContext;
using o2::framework::ConfigParamSpec;
using o2::framework::VariantType;
using o2::framework::WorkflowSpec;

void customize(std::vector<ConfigParamSpec>& workflowOptions)
{
  std::vector<ConfigParamSpec> options{
    {"configKeyValues", VariantType::String, "", {"Semicolon separated key=value strings"}}};

  o2::raw::HBFUtilsInitializer::addConfigOption(options);

  std::swap(workflowOptions, options);
}

#include "Framework/runDataProcessing.h"

WorkflowSpec defineDataProcessing(ConfigContext const& configcontext)
{
  WorkflowSpec specs;

  // auto disableRootOutput = configcontext.options().get<bool>("disable-root-output");

  o2::conf::ConfigurableParam::updateFromString(configcontext.options().get<std::string>("configKeyValues"));

  specs.emplace_back(o2::mch::getPreClusterFinderSpec());
  specs.emplace_back(o2::mch::getClusterFinderOriginalSpec());
  specs.emplace_back(o2::mch::getClusterTransformerSpec());
  specs.emplace_back(o2::mch::getTrackFinderSpec());

  // configure dpl timer to inject correct firstTFOrbit: start from the 1st orbit of TF containing 1st sampled orbit
  o2::raw::HBFUtilsInitializer hbfIni(configcontext, specs);

  // write the configuration used for the reco workflow
  o2::conf::ConfigurableParam::writeINI("o2mchrecoflow_configuration.ini");

  return specs;
}
