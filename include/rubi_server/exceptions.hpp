#pragma once

#include <csignal>
#include <cstring>
#include <exception>
#include <string>

#include "rubi_server/board.hpp"

#define ASSERT(x, ...) \
  if (!(x)) \
  throw AssertionFailedException(__FILE__, __LINE__, #__VA_ARGS__);

class RubiException : public std::exception
{
public:
  std::string rubi_msg;

  const char * what() const throw() {return rubi_msg.c_str();}

  virtual ~RubiException() throw() {}
  explicit RubiException(std::string what)
  : rubi_msg(what) {}
};

class AssertionFailedException : RubiException
{
public:
  AssertionFailedException(const char * file, int line, std::string msg = "")
  : RubiException("")
  {
    if (msg == "") {
      rubi_msg += (std::string) "Assertion at " + std::string(file) +
        ":" + std::to_string(line) + " has failed.";
    } else {
      rubi_msg += msg + " (" + std::string(file) + ":" +
        std::to_string(line) + ")";
    }

    Logger("Exception").Error(rubi_msg);
  }
};

class CanFailureException : public RubiException
{
public:
  explicit CanFailureException(std::string msg)
  : RubiException(std::string("Can failure: ") + msg) {}
  virtual ~CanFailureException() throw() {}
};

class FrontendCommunicationException : public RubiException
{
public:
  explicit FrontendCommunicationException(std::string msg)
  : RubiException(std::string("Frontend failure: ") + msg) {}
  virtual ~FrontendCommunicationException() throw() {}
};
