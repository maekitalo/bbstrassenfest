#include <tnt/component.h>
#include <tnt/componentfactory.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>
#include <cxxtools/log.h>
#include <model/strassenfest.h>
#include <manager/strassenfestmanager.h>

log_define("strasenfeste.controller")

namespace
{
  class strassenfesteController : public tnt::Component
  {
    public:
      unsigned operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam);
  };

  static tnt::ComponentFactoryImpl<strassenfesteController> factory("controller/strassenfeste");

  unsigned strassenfesteController::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
  {
    log_debug("strassenfestController; q=" << qparam.getUrl());

    TNT_APPLICATION_SHARED_VAR(std::vector<std::string>, bezirke, ());

    manager::StrassenfestManager manager;

    if (bezirke.empty())
    {
      bezirke = manager.getBezirke();
    }

    if (qparam.arg<bool>("aktualisieren"))
    {
      TNT_SESSION_SHARED_VAR(model::Strassenfeste, strassenfeste, ());

      strassenfeste = manager.getAllByBezirk(qparam.arg<std::string>("bezirk"));
    }
    return DECLINED;
  }

}
