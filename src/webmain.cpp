////////////////////////////////////////////////////////////////////////
// webmain.cpp
// generated with ecppc
//

#include <tnt/ecpp.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>
#include <tnt/httpheader.h>
#include <tnt/http.h>
#include <tnt/data.h>
#include <tnt/componentfactory.h>
#include <cxxtools/log.h>
#include <stdexcept>

log_define("component.webmain")

// <%pre>
// </%pre>

namespace
{
class _component_ : public tnt::EcppComponent
{
    _component_& main()  { return *this; }

  protected:
    ~_component_();

  public:
    _component_(const tnt::Compident& ci, const tnt::Urlmapper& um, tnt::Comploader& cl);

    unsigned operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam);
};

static tnt::EcppComponentFactoryImpl<_component_> Factory("webmain");

static const char* rawData = "\014\000\000\000m\003\000\000\213\003\000\000<!DOCTYPE html>\n<html>\n  <head>\n    <meta"
  " charset=\"utf-8\">\n    <meta name=\"description\" content=\"bbstrassenfest application\">\n    <link rel=\"styleshe"
  "et\" href=\"/bbstrassenfest.css\" type=\"text/css\">\n    <link href=\"/jquery-ui-1.10.3.custom/css/ui-lightness/jque"
  "ry-ui-1.10.3.custom.css\" rel=\"stylesheet\">\n\t<script src=\"/jquery-ui-1.10.3.custom/js/jquery-1.9.1.js\"></script"
  ">\n\t<script src=\"/jquery-ui-1.10.3.custom/js/jquery-ui-1.10.3.custom.min.js\"></script>\n  </head>\n  <body>\n    <"
  "div id=\"header\">\n      <span id=\"title\">Berlin Brandenburger Strassenfeste 2013</span>\n    </div>\n\n    <div i"
  "d=\"menu\">\n      <ul class=\"nav\">\n        <li class=\"navitem\"><a href=\"/\">Home</a></li>\n        <li class="
  "\"navitem\"><a href=\"/strassenfeste\">strassenfeste</a></li>\n        <li class=\"navitem\"><a href=\"/suche\">suche"
  "</a></li>\n      </ul>\n    </div>\n\n    <div id=\"content\">\n       \n    </div>\n  </body>\n</html>\n";

// <%shared>
// </%shared>

// <%config>
// </%config>

#define SET_LANG(lang) \
     do \
     { \
       request.setLang(lang); \
       reply.setLocale(request.getLocale()); \
     } while (false)

_component_::_component_(const tnt::Compident& ci, const tnt::Urlmapper& um, tnt::Comploader& cl)
  : EcppComponent(ci, um, cl)
{
  // <%init>
  // </%init>
}

_component_::~_component_()
{
  // <%cleanup>
  // </%cleanup>
}

unsigned _component_::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{
  log_trace("webmain " << qparam.getUrl());

  tnt::DataChunks data(rawData);

  // <%cpp>
  reply.out() << data[0]; // <!DOCTYPE html>\n<html>\n  <head>\n    <meta charset="utf-8">\n    <meta name="description" content="bbstrassenfest application">\n    <link rel="stylesheet" href="/bbstrassenfest.css" type="text/css">\n    <link href="/jquery-ui-1.10.3.custom/css/ui-lightness/jquery-ui-1.10.3.custom.css" rel="stylesheet">\n\t<script src="/jquery-ui-1.10.3.custom/js/jquery-1.9.1.js"></script>\n\t<script src="/jquery-ui-1.10.3.custom/js/jquery-ui-1.10.3.custom.min.js"></script>\n  </head>\n  <body>\n    <div id="header">\n      <span id="title">Berlin Brandenburger Strassenfeste 2013</span>\n    </div>\n\n    <div id="menu">\n      <ul class="nav">\n        <li class="navitem"><a href="/">Home</a></li>\n        <li class="navitem"><a href="/strassenfeste">strassenfeste</a></li>\n        <li class="navitem"><a href="/suche">suche</a></li>\n      </ul>\n    </div>\n\n    <div id="content">\n       
  // <& (request.getArg("next")) ...
  { 
#line 29 "webmain.ecpp"
    tnt::QueryParams _tnt_cq0(qparam);
#line 29 "webmain.ecpp"
    callComp((request.getArg("next")), request, reply, _tnt_cq0);
    // &>
  }
  reply.out() << data[1]; // \n    </div>\n  </body>\n</html>\n
  // <%/cpp>
  return HTTP_OK;
}

} // namespace
