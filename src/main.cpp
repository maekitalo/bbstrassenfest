#include <iostream>
#include <configuration.h>
#include <tnt/tntnet.h>
#include <tnt/configurator.h>
#include <cxxtools/log.h>
#include <cxxtools/posix/daemonize.h>

log_define("bbstrassenfest")

int main(int argc, char* argv[])
{
  try
  {
    Configuration& configuration = Configuration::it();

    if (argc > 1)
      configuration.readConfiguration(argv[1]);
    else
      configuration.readConfiguration("bbstrassenfest.conf");

    log_init(configuration.loggingConfiguration());

    if (configuration.daemon())
      cxxtools::posix::daemonize(configuration.pidfile());

    tnt::Tntnet app;
    app.listen(configuration.listenIp(), configuration.listenPort());

    tnt::Configurator configurator(app);
    if (configuration.sessionTimeout())
      configurator.setSessionTimeout(configuration.sessionTimeout());

    // configure static stuff - lookup files in static resources first
    app.mapUrl("^/(.*)", "resources")
       .setPathInfo("resources/$1");

    // index page
    app.mapUrl("^/$", "webmain")
       .setArg("next", "index");

    // controller
    app.mapUrl("^/(.*)$", "controller/$1");

    // view
    app.mapUrl("^/(.*)$", "webmain")
       .setArg("next", "view/$1");

    app.run();
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

