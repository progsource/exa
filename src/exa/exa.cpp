/*
 * This project is licensed under the MIT license. For more information see the
 * LICENSE file.
 */
#include "exa/exa.h"

#include <iostream>
#include <sstream>
#include <map>

// -----------------------------------------------------------------------------

namespace exa {

// -----------------------------------------------------------------------------

namespace impl {

// -----------------------------------------------------------------------------

void
writeMessageImpl(
  const AssertLevel level,
  const std::string& condition,
  const std::string& fileName,
  const uint64_t lineNumber,
  const std::string& functionName,
  const std::string& message
) {
#if defined(NDEBUG)
  if (level == AssertLevel::DEBUG)
  {
    return;
  }
#endif

  const std::map<AssertLevel, std::string> levelStrings = {
    { AssertLevel::DEBUG, "Debug:" },
    { AssertLevel::WARNING, "Warning:" },
    { AssertLevel::DEFAULT, "Default:" },
    { AssertLevel::ERROR, "Error:" },
    { AssertLevel::FATAL, "Fatal:" }
  };

  std::stringstream endlStream;
  endlStream << std::endl;
  const std::string endl = endlStream.str();

  std::string outputMessage = fmt::format(
    "{timestamp} {level}{endl}\t{condition}{endl}\tfailed in {fileName}{endl}\t{function}{endl}\tline {line}{endl}\twith message{endl}\t{message}{endl}",
    fmt::arg("timestamp", __TIMESTAMP__),
    fmt::arg("level", levelStrings.at(level)),
    fmt::arg("endl", endl),
    fmt::arg("condition", condition),
    fmt::arg("fileName", fileName),
    fmt::arg("function", functionName),
    fmt::arg("line", lineNumber),
    fmt::arg("message", message)
  );

  std::cerr << outputMessage;
}

// -----------------------------------------------------------------------------

} // namespace impl

// -----------------------------------------------------------------------------

} // namespace exa
