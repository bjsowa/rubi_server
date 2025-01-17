#pragma once

#include <memory>
#include <string>
#include <vector>

#include <boost/optional.hpp>

#include "rubi_server/board.hpp"
#include "rubi_server/communication.hpp"
#include "rubi_server/descriptors.hpp"
#include "rubi_server/frontend.hpp"

#include "rclcpp/rclcpp.hpp"

class RosBoardHandler;

class RosModule : public RubiFrontend
{
private:
  std::vector<sptr<RosBoardHandler>> boards;
  std::vector<std::string> cans_names;

  Logger log {"RosModule"};

public:
  RosModule();
  RosModule(RosModule const &) = delete;
  void operator=(RosModule const &) = delete;

  bool Init(int argc, char ** argv) override;
  std::vector<std::string> GetCansNames() override;

  void Spin() override;
  bool Quit() override;

  void LogInfo(std::string msg) override;
  void LogWarning(std::string msg) override;
  void LogError(std::string msg) override;

  void ReportCansUtilization(std::vector<float> util) override;

  std::shared_ptr<FrontendBoardHandler> NewBoard(BoardInstance inst) override;
};

class RosBoardHandler : public FrontendBoardHandler
{
  RosModule * ros_module;
  BoardInstance board;

  Logger log {"RosBoardHandler"};

public:
  RosBoardHandler(BoardInstance inst, RosModule * ros_module);

  void FFDataInbound(std::vector<uint8_t> & data, int ffid) override;
  void ReplaceBackendHandler(sptr<BoardCommunicationHandler>) override;
  void Shutdown() override;
  void ConnectionLost() override;
};
