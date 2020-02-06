// Copyright 2020-present Open Networking Foundation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "stratum/hal/lib/phal/tai/tai_optics_datasource.h"

#include <cmath>

#include "absl/memory/memory.h"
#include "stratum/glue/integral_types.h"
#include "stratum/glue/status/status.h"
#include "stratum/glue/status/statusor.h"
#include "stratum/hal/lib/common/common.pb.h"
#include "stratum/hal/lib/phal/datasource.h"
#include "stratum/hal/lib/phal/phal.pb.h"
#include "stratum/lib/macros.h"

namespace stratum {
namespace hal {
namespace phal {
namespace tai {

::util::StatusOr<std::shared_ptr<TaiOpticsDataSource>>
TaiOpticsDataSource::Make(int id, TaiInterface* tai_interface,
                          CachePolicy* cache_policy) {
  auto optics_datasource = std::shared_ptr<TaiOpticsDataSource>(
      new TaiOpticsDataSource(id, tai_interface, cache_policy));

  // Some tai init stuff for this module
  // Do stuff that can fail here, instead of in the constructor.
  RETURN_IF_ERROR(tai_interface->SetTxPower(id, 10.0));

  // TODO(max): not sure if this is needed anymore. Just make sure you call it
  // last.
  optics_datasource->UpdateValuesUnsafelyWithoutCacheOrLock();

  return optics_datasource;
}

TaiOpticsDataSource::TaiOpticsDataSource(int id, TaiInterface* tai_interface,
                                         CachePolicy* cache_policy)
    : DataSource(cache_policy),
      tai_interface_(ABSL_DIE_IF_NULL(tai_interface)) {
  // These values do not change during the lifetime of the data source.
  module_slot_.AssignValue(id);

  // Add setters here
  tx_power_attr_.AddSetter([this](double requested_tx_power) -> ::util::Status {
    return this->SetTxPower(requested_tx_power);
  });
}

::util::Status TaiOpticsDataSource::UpdateValues() {
  // Update attributes with fresh values from Tai.
  int slot = module_slot_.ReadValue<int>().ValueOrDie();
  ASSIGN_OR_RETURN(auto present, tai_interface_->GetLinkState(slot));
  module_hw_state_ =
      present ? HwState::HW_STATE_PRESENT : HwState::HW_STATE_NOT_PRESENT;
  card_vendor_.AssignValue("some-vendor");
  ASSIGN_OR_RETURN(auto tx_power, tai_interface_->GetTxPower(slot));
  tx_power_attr_.AssignValue(tx_power);

  return ::util::OkStatus();
}

::util::Status TaiOpticsDataSource::SetTxPower(double tx_power) {
  int slot = module_slot_.ReadValue<int>().ValueOrDie();
  return tai_interface_->SetTxPower(slot, tx_power);
}

}  // namespace tai
}  // namespace phal
}  // namespace hal
}  // namespace stratum