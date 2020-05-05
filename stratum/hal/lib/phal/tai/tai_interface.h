/*
 * Copyright 2020-present Open Networking Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef STRATUM_HAL_LIB_PHAL_TAI_TAI_INTERFACE_H_
#define STRATUM_HAL_LIB_PHAL_TAI_TAI_INTERFACE_H_

#include <vector>

#include "stratum/glue/integral_types.h"
#include "stratum/glue/status/status.h"
#include "stratum/glue/status/statusor.h"

namespace stratum {
namespace hal {
namespace phal {
namespace tai {

/*
 * An interface that defines functions we need to manage optical-relative
 * components such as module, network interface, and host interface.
 */
class TaiInterface {
 public:
  // Initialize the TAI interface.
  virtual util::Status Initialize() = 0;

  // Gets all module id.
  virtual util::StatusOr<std::vector<uint64>> GetModuleIds() = 0;

  // Gets all network interface id from a module.
  virtual util::StatusOr<std::vector<uint64>>
      GetNetworkInterfacesFromModule(const uint64 module_id) = 0;

  // Gets all host interface id from a module
  virtual util::StatusOr<std::vector<uint64>>
      GetHostInterfacesFromModule(const uint64 module_id) = 0;

  // TODO(Yi): Complete functions for Module and Host Interface

  // Functions for Network Interface
  // Gets frequency from a network interface.
  virtual util::StatusOr<uint64> GetFrequency(const uint64 netif_id) = 0;

  // Gets input power from a network interface.
  virtual util::StatusOr<double>
      GetCurrentInputPower(const uint64 netif_id) = 0;

  // Gets output power from a network interface.
  virtual util::StatusOr<double>
      GetCurrentOutputPower(const uint64 netif_id) = 0;

  // Gets target output power from a network interface.
  virtual util::StatusOr<double>
      GetTargetOutputPower(const uint64 netif_id) = 0;

  // Gets modulation format from a network interface.
  virtual util::StatusOr<uint64>
      GetModulationFormats(const uint64 netif_id) = 0;

  // Sets target output power to a network interafce.
  virtual util::Status SetTargetOutputPower(const uint64 netif_id,
                                            const double power) = 0;

  // Sets modulation format to a network interface.
  virtual util::Status SetModulationsFormats(const uint64 netif_id,
                                             const uint64 mod_format) = 0;
};

}  // namespace tai
}  // namespace phal
}  // namespace hal
}  // namespace stratum

#endif  // STRATUM_HAL_LIB_PHAL_TAI_TAI_INTERFACE_H_
