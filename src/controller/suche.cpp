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

    TNT_SESSION_SHARED_VAR(std::string, q, ());
    TNT_SESSION_SHARED_VAR(std::string, bezirk, ());
    TNT_SESSION_SHARED_VAR(std::string, von_from, ());
    TNT_SESSION_SHARED_VAR(std::string, von_to, ());
    TNT_SESSION_SHARED_VAR(cxxtools::Date, from, ());
    TNT_SESSION_SHARED_VAR(cxxtools::Date, to, ());
    TNT_SESSION_SHARED_VAR(unsigned, pageNo, (1));
    TNT_SESSION_SHARED_VAR(unsigned, itemsPerPage, (20));

    log_debug("sucheController; q=" << qparam.getUrl());

    StrassenfestManager manager;

    if (bezirke.empty())
    {
      bezirke = manager.getBezirke();
    }

    if (qparam.arg<bool>("suchen"))
    {
      log_debug("suchen");

      q        = qparam.arg<std::string>("q");
      bezirk   = qparam.arg<std::string>("bezirk");

      von_from = qparam.arg<std::string>("von_from");
      von_to   = qparam.arg<std::string>("von_to");

      if (!von_from.empty())
        from = cxxtools::Date(von_from, "%d.%m.%Y");

      if (!von_to.empty())
        to = cxxtools::Date(von_to, "%d.%m.%Y");

      pageNo = 1;
      strassenfestResult = manager.search(q, bezirk, from, to, cxxtools::Date(), itemsPerPage, pageNo);
    }
    else if (qparam.arg<bool>("previousPage"))
    {
      --pageNo;
      strassenfestResult = manager.search(q, bezirk, from, to, cxxtools::Date(), itemsPerPage, pageNo);
    }
    else if (qparam.arg<bool>("nextPage"))
    {
      ++pageNo;
      strassenfestResult = manager.search(q, bezirk, from, to, cxxtools::Date(), itemsPerPage, pageNo);
    }

    // Return DECLINED to tell tntnet to continue processing with next mapping.
    // The next mapping will be the corresponding view.

    return DECLINED;
  }

}
