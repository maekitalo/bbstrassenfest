#include <sstream>
#include <tnt/component.h>
#include <tnt/componentfactory.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>
#include <cxxtools/log.h>
#include <strassenfestresult.h>
#include <strassenfestmanager.h>
#include <suchesession.h>

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

    TNT_SESSION_SHARED_VAR(SucheSession, suche, ());

    log_debug("sucheController; q=" << qparam.getUrl());

    StrassenfestManager manager;

    if (bezirke.empty())
    {
      bezirke = manager.getBezirke();
    }

    if (qparam.arg<bool>("suchen"))
    {
      log_debug("suchen");

      suche.q        = qparam.arg<std::string>("q");
      suche.bezirk   = qparam.arg<std::string>("bezirk");

      suche.von_from = qparam.arg<std::string>("von_from");
      suche.von_to   = qparam.arg<std::string>("von_to");

      if (!suche.von_from.empty())
        suche.from = cxxtools::Date(suche.von_from, "%d.%m.%Y");

      if (!suche.von_to.empty())
        suche.to = cxxtools::Date(suche.von_to, "%d.%m.%Y");

      suche.pageNo = 1;
      strassenfestResult = manager.search(suche.q, suche.bezirk, suche.from, suche.to,
        cxxtools::Date(), suche.itemsPerPage, suche.pageNo);
    }
    else if (qparam.arg<bool>("previousPage"))
    {
      --suche.pageNo;
      strassenfestResult = manager.search(suche.q, suche.bezirk, suche.from, suche.to,
        cxxtools::Date(), suche.itemsPerPage, suche.pageNo);
    }
    else if (qparam.arg<bool>("nextPage"))
    {
      ++suche.pageNo;
      strassenfestResult = manager.search(suche.q, suche.bezirk, suche.from, suche.to,
        cxxtools::Date(), suche.itemsPerPage, suche.pageNo);
    }

    // Return DECLINED to tell tntnet to continue processing with next mapping.
    // The next mapping will be the corresponding view.

    return DECLINED;
  }

}
