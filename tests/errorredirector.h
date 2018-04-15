/*
 * This project is licensed under the MIT license. For more information see the
 * LICENSE file.
 */
#pragma once

#include <sstream>
#include <streambuf>
#include <iostream>

/**
 * ErrorRedirector
 *
 * This class is for redirecting the cerr stream for unit tests.
 *
 * @class
 */
class ErrorRedirector
{
public:
  ErrorRedirector()
    : oldCerrStreamBuf(nullptr)
  {
  }

  ~ErrorRedirector()
  {
    this->StopRedirecting();
  }

  void
  StartRedirecting()
  {
    if (this->oldCerrStreamBuf)
    {
      return;
    }

    this->oldCerrStreamBuf = std::cerr.rdbuf();

    std::cerr.rdbuf(this->stream.rdbuf());
  }

  void
  StopRedirecting()
  {
    if (this->oldCerrStreamBuf)
    {
      std::cerr.rdbuf(this->oldCerrStreamBuf);
      #ifdef UNIT_TESTS_DEBUG
        std::cerr << this->stream.str() << std::endl;
      #endif
      this->oldCerrStreamBuf = nullptr;
    }
  }

  std::string
  GetOutput()
  {
    return this->stream.str();
  }

  void
  ClearOutput()
  {
    this->stream.str("");
  }

private:
  std::streambuf* oldCerrStreamBuf;
  std::ostringstream stream;
}; // class ErrorRedirector
