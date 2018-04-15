/*
 * This project is licensed under the MIT license. For more information see the
 * LICENSE file.
 */
#include "gmock/gmock.h"

#include "errorredirector.h"

#include "exa/exa.h"

// -----------------------------------------------------------------------------

class TEST_EXA_FIXTURE : public ::testing::Test
{
protected:
  void
  checkOutput(
    const std::string& output,
    const std::string& condition,
    const std::string& level,
    const std::string& message
  ) {
    ASSERT_TRUE(output.find(condition) != std::string::npos);
    ASSERT_TRUE(output.find(level) != std::string::npos);
    ASSERT_TRUE(output.find(message) != std::string::npos);
  }
};

// -----------------------------------------------------------------------------

TEST_F(TEST_EXA_FIXTURE, ItShouldGiveTheCorrectOutputForDebugAsserts)
{
  const std::string condition = "1 == 0";
  const std::string level = "Debug:";
  const std::string message = "This is some test";

  ErrorRedirector cerrRedirector;
  cerrRedirector.StartRedirecting();

  EXA_DEBUG(1 == 0, "This {} some test", "is");
  const std::string actualOutput = cerrRedirector.GetOutput();

  cerrRedirector.StopRedirecting();

  checkOutput(actualOutput, condition, level, message);
}

TEST_F(TEST_EXA_FIXTURE, ItShouldGiveTheCorrectOutputForWarningAsserts)
{
  const std::string condition = "2 == 0";
  const std::string level = "Warning:";
  const std::string message = "This is some test";

  ErrorRedirector cerrRedirector;
  cerrRedirector.StartRedirecting();

  EXA_WARNING(2 == 0, message);
  const std::string actualOutput = cerrRedirector.GetOutput();

  cerrRedirector.StopRedirecting();

  checkOutput(actualOutput, condition, level, message);
}

TEST_F(TEST_EXA_FIXTURE, ItShouldGiveTheCorrectOutputForDefaultAsserts)
{
  const std::string condition = "3 == 0";
  const std::string level = "Default:";
  const std::string message = "This is some test";

  ErrorRedirector cerrRedirector;
  cerrRedirector.StartRedirecting();

  EXA(3 == 0, message);
  const std::string actualOutput = cerrRedirector.GetOutput();

  cerrRedirector.StopRedirecting();

  checkOutput(actualOutput, condition, level, message);
}

TEST_F(TEST_EXA_FIXTURE, ItShouldGiveTheCorrectOutputForErrorAsserts)
{
  const std::string condition = "4 == 0";
  const std::string level = "Error:";
  const std::string message = "This is some test";

  ErrorRedirector cerrRedirector;
  cerrRedirector.StartRedirecting();

  EXA_ERROR(4 == 0, message);
  const std::string actualOutput = cerrRedirector.GetOutput();

  cerrRedirector.StopRedirecting();

  checkOutput(actualOutput, condition, level, message);
}

TEST_F(TEST_EXA_FIXTURE, ItShouldGiveTheCorrectOutputForFatalAsserts)
{
  const std::string condition = "5 == 0";
  const std::string level = "Fatal:";
  const std::string message = "This is some test";

  ErrorRedirector cerrRedirector;
  cerrRedirector.StartRedirecting();

  EXA_FATAL(5 == 0, message);
  const std::string actualOutput = cerrRedirector.GetOutput();

  cerrRedirector.StopRedirecting();

  checkOutput(actualOutput, condition, level, message);
}
