#pragma once

#include <mos/chain/webassembly/mos-vm-oc/config.hpp>

#include <boost/asio/local/datagram_protocol.hpp>
#include <mos/chain/webassembly/mos-vm-oc/ipc_helpers.hpp>

namespace mos { namespace chain { namespace mosvmoc {

wrapped_fd get_connection_to_compile_monitor(int cache_fd);

}}}