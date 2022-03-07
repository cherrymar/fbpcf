/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <memory>
#include "fbpcf/mpc_framework/engine/communication/IPartyCommunicationAgentFactory.h"
#include "fbpcf/mpc_games/unified_data_process/data_processor/DummyDataProcessor.h"
#include "fbpcf/mpc_games/unified_data_process/data_processor/IDataProcessorFactory.h"

namespace fbpcf::mpc_games::udp::data_processor::insecure {

template <int schedulerId>
class DummyDataProcessorFactory final
    : public IDataProcessorFactory<schedulerId> {
 public:
  DummyDataProcessorFactory(
      int32_t myId,
      int32_t partnerId,
      fbpcf::mpc_framework::engine::communication::
          IPartyCommunicationAgentFactory& agentFactory)
      : myId_(myId), partnerId_(partnerId), agentFactory_(agentFactory) {}

  std::unique_ptr<IDataProcessor<schedulerId>> create() {
    return std::make_unique<DummyDataProcessor<schedulerId>>(
        myId_, partnerId_, agentFactory_.create(partnerId_));
  }

 private:
  int32_t myId_;
  int32_t partnerId_;
  fbpcf::mpc_framework::engine::communication::IPartyCommunicationAgentFactory&
      agentFactory_;
};

} // namespace fbpcf::mpc_games::udp::data_processor::insecure