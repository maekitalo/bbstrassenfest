#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <cxxtools/log.h>

namespace cxxtools
{
  class SerializationInfo;
}

class Configuration
{
    friend void operator>>= (const cxxtools::SerializationInfo& si, Configuration& config);

  public:
    static Configuration& it();

    void readConfiguration(const std::string& file);

    const std::string& listenIp() const
    { return _listenIp; }

    unsigned short listenPort() const
    { return _listenPort; }

    unsigned sessionTimeout() const
    { return _sessionTimeout; }

    const std::string& berlinUrl() const
    { return _berlinUrl; }

    const cxxtools::LogConfiguration& loggingConfiguration() const
    { return _loggingConfiguration; }

  private:
    Configuration();
    Configuration(const Configuration&);  // no implementation
    const Configuration& operator=(const Configuration&);  // no implementation

    std::string    _listenIp;
    unsigned short _listenPort;
    unsigned       _sessionTimeout;
    std::string    _berlinUrl;
    cxxtools::LogConfiguration _loggingConfiguration;
};

#endif // CONFIGURATION_H
