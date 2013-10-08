#include <sstream>
#include <tnt/component.h>
#include <tnt/componentfactory.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>
#include <cxxtools/log.h>
#include <strassenfestresult.h>
#include <strassenfestmanager.h>

log_define("suche.controller")

namespace
{
  cxxtools::Date str2date(const std::string& s)
  {
    std::istringstream in(s);
    char ch;
    unsigned n1, n2, n3;
    in >> n1 >> ch >> n2 >> ch >> n3;
    if (!in)
      throw std::runtime_error("invalid date: \"" + s + '"');

    if (ch == '-')  // Format: jjjj-mm-dd
      return cxxtools::Date(n1, n2, n3);
    else
      return cxxtools::Date(n3, n2, n1);  // gehen wir mal mutig von dd.mm.jjjj aus
  }

  class sucheController : public tnt::Component
  {
    public:
      unsigned operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam);
  };

  static tnt::ComponentFactoryImpl<sucheController> factory("controller/suche");

  unsigned sucheController::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
  {
    TNT_APPLICATION_SHARED_VAR(std::vector<std::string>, bezirke, ());
    TNT_REQUEST_SHARED_VAR(StrassenfestResult, strassenfestResult, ());

    log_debug("sucheController; q=" << qparam.getUrl());

    StrassenfestManager manager;

    if (bezirke.empty())
    {
      bezirke = manager.getBezirke();
    }

    if (qparam.arg<bool>("suchen"))
    {
      log_debug("suchen");

      std::string q        = qparam.arg<std::string>("q");
      std::string bezirk   = qparam.arg<std::string>("bezirk");

      std::string von_from = qparam.arg<std::string>("von_from");
      std::string von_to   = qparam.arg<std::string>("von_to");

      cxxtools::Date from;
      if (!von_from.empty())
        from = str2date(von_from);

      cxxtools::Date to;
      if (!von_to.empty())
        to = str2date(von_to);

      strassenfestResult = manager.search(q, bezirk, from, to, cxxtools::Date(), 20, 1);
    }

    return DECLINED;
  }

}
