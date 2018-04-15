/*
 * This project is licensed under the MIT license. For more information see the
 * LICENSE file.
 */
#pragma once

// -----------------------------------------------------------------------------

#include <string>

#include "fmt/format.h"

// -----------------------------------------------------------------------------

namespace exa {

// -----------------------------------------------------------------------------

enum class AssertLevel
{
  DEBUG,
  WARNING,
  DEFAULT,
  ERROR,
  FATAL
};

// -----------------------------------------------------------------------------

namespace impl {

// -----------------------------------------------------------------------------

void writeMessageImpl(
  const AssertLevel level,
  const std::string& condition,
  const std::string& fileName,
  const uint64_t lineNumber,
  const std::string& functionName,
  const std::string& message
);

template<typename ...ARGS>
void
writeMessage(
  const AssertLevel level,
  const std::string& condition,
  const std::string& fileName,
  const uint64_t lineNumber,
  const std::string& functionName,
  ARGS... message
) {
  std::string msg = "";
  if (sizeof...(message) > 0)
  {
    msg = fmt::format(message...);
  }

  writeMessageImpl(
    level,
    condition,
    fileName,
    lineNumber,
    functionName,
    msg
  );
}

// -----------------------------------------------------------------------------

} // namespace impl

// -----------------------------------------------------------------------------

#if defined(__GNUC__) || defined(__clang__)
  #define EXA_FUNCNAME __PRETTY_FUNCTION__
#else
  #define EXA_FUNCNAME __FUNCTION__
#endif

#ifdef NDEBUG
  #define EXA_ABORT abort();

  #if defined(_WIN32)
    #define EXA_BREAK_HERE __debugbreak();
  #else
    #if defined(__APPLE__)
      #include <TargetConditionals.h>
    #endif
    #if defined(__clang__) && !TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
      #define EXA_BREAK_HERE __builtin_debugtrap();
    #elif defined(__APPLE__)
      #include <signal.h>
      #define EXA_BREAK_HERE raise(SIGTRAP);
    #elif defined(__GNUC__)
      #define EXA_BREAK_HERE __builtin_trap();
    #else
      #define EXA_BREAK_HERE ((void)0);
    #endif
  #endif
#else
  #define EXA_ABORT
  #define EXA_BREAK_HERE
#endif

// -----------------------------------------------------------------------------

#define EXA_DEBUG(condition, ...) \
  do \
  { \
    if (condition) break; \
    exa::impl::writeMessage( \
      exa::AssertLevel::DEBUG, \
      #condition, \
      __FILE__, \
      __LINE__, \
      (EXA_FUNCNAME), ## __VA_ARGS__ \
    ); \
    EXA_BREAK_HERE \
  } while(0)

#define EXA_WARNING(condition, ...) \
  do \
  { \
    if (condition) break; \
    exa::impl::writeMessage( \
      exa::AssertLevel::WARNING, \
      #condition, \
      __FILE__, \
      __LINE__, \
      (EXA_FUNCNAME), ## __VA_ARGS__ \
    ); \
    EXA_BREAK_HERE \
  } while(0)

#define EXA(condition, ...) \
  do \
  { \
    if (condition) break; \
    exa::impl::writeMessage( \
      exa::AssertLevel::DEFAULT, \
      #condition, \
      __FILE__, \
      __LINE__, \
      (EXA_FUNCNAME), ## __VA_ARGS__ \
    ); \
    EXA_ABORT \
  } while(0)


#define EXA_ERROR(condition, ...) \
  do \
  { \
    if (condition) break; \
    exa::impl::writeMessage( \
      exa::AssertLevel::ERROR, \
      #condition, \
      __FILE__, \
      __LINE__, \
      (EXA_FUNCNAME), ## __VA_ARGS__ \
    ); \
    EXA_ABORT \
  } while(0)

#define EXA_FATAL(condition, ...) \
  do \
  { \
    if (condition) break; \
    exa::impl::writeMessage( \
      exa::AssertLevel::FATAL, \
      #condition, \
      __FILE__, \
      __LINE__, \
      (EXA_FUNCNAME), ## __VA_ARGS__ \
    ); \
    EXA_ABORT \
  } while(0)

// -----------------------------------------------------------------------------

} // namespace exa
