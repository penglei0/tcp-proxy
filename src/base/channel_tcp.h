#ifndef SRC_BASE_CHANNEL_TCP_H_
#define SRC_BASE_CHANNEL_TCP_H_

#include <string>

#include "base/channel.h"

/// @brief the message format between the proxy client and proxy server.
class TcpConnection {
 public:
  uint32_t src_ip;
  uint16_t src_port;
  uint32_t dst_ip;
  uint16_t dst_port;
  int fd;
  int type;
};

class TcpChannelCfg {
 public:
  int port = 0;
  std::string ip;
};

class TCPChannel : public Channel {
 public:
  TCPChannel() = default;
  explicit TCPChannel(const TcpChannelCfg& cfg) {}
  virtual ~TCPChannel() = default;
  TCPChannel(const TCPChannel&) = delete;
  TCPChannel& operator=(const TCPChannel&) = delete;
  TCPChannel(const TCPChannel&&) = delete;
  TCPChannel& operator=(const TCPChannel&&) = delete;

  PacketPtr Read() override { return nullptr; }
  bool Write(const PacketPtr& packet) override { return true; }
  int GetFd() const override { return fd_; }
  const TcpConnection& ConnectionInfo() const { return conn_info_; }
  TcpConnection& ConnectionInfo() { return conn_info_; }

 private:
  int fd_ = 0;
  TcpConnection conn_info_;
};
using TCPChannelPtr = std::shared_ptr<TCPChannel>;

#endif  // SRC_BASE_CHANNEL_TCP_H_