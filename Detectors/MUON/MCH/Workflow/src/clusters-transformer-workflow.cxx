// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#include "ClusterTransformerSpec.h"

#include "CommonUtils/ConfigurableParam.h"
#include "Framework/ConfigContext.h"
#include "Framework/ConfigParamSpec.h"
#include "Framework/Variant.h"
#include "Framework/WorkflowSpec.h"

// we need to add workflow options before including Framework/runDataProcessing
void customize(std::vector<o2::framework::ConfigParamSpec>& workflowOptions)
{
  workflowOptions.emplace_back("configKeyValues",
                               o2::framework::VariantType::String, "",
                               o2::framework::ConfigParamSpec::HelpString{"Semicolon separated key=value strings"});
}

#include "Framework/runDataProcessing.h"

o2::framework::WorkflowSpec defineDataProcessing(const o2::framework::ConfigContext& configContext)
{
  o2::conf::ConfigurableParam::updateFromString(configContext.options().get<std::string>("configKeyValues"));
  return o2::framework::WorkflowSpec{o2::mch::getClusterTransformerSpec()};
}
