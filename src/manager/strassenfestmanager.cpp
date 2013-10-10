/*
 * Copyright (C) 2013 Tommi Maekitalo
 *
 */

#include <strassenfestmanager.h>
#include <strassenfestresult.h>
#include <configuration.h>
#include <cxxtools/net/uri.h>
#include <cxxtools/json.h>
#include <cxxtools/log.h>
#include <cxxtools/query_params.h>
#include <cxxtools/convert.h>
#include <cxxtools/http/client.h>
#include <cxxtools/refcounted.h>
#include <stdio.h>

log_define("strassenfest.manager")

////////////////////////////////////////////////////////////////////////
// declare implementation interface for StrassenfestManager

class StrassenfestManager::Impl : public cxxtools::RefCounted
{
    cxxtools::http::Client _client;

  public:
    Impl();

    std::vector<std::string> getBezirke();
    StrassenfestResult search(const std::string& keyword, const std::string& bezirk,
        const cxxtools::Date& von_from, const cxxtools::Date& von_to, const cxxtools::Date& bis,
        unsigned ipp, unsigned page);

    Strassenfeste getAll();
    Strassenfeste getAllByBezirk(const std::string& bezirk);
};

StrassenfestManager::Impl::Impl()
  : _client(Configuration::it().berlinUrl())
{
}

std::vector<std::string> StrassenfestManager::Impl::getBezirke()
{
  static const char* bezirke[] = {
  	"-- Alles --",
	"Charlottenburg-Wilmersdorf",
	"Friedrichshain-Kreuzberg",
	"Lichtenberg",
	"Marzahn-Hellersdorf",
	"Mitte",
	"Neukölln",
	"Pankow",
	"Reinickendorf",
	"Spandau",
	"Steglitz-Zehlendorf",
	"Tempelhof-Schöneberg",
	"Treptow-Köpenick",
	"Brandenburg"
  };

  std::vector<std::string> ret;
  ret.insert(ret.begin(), bezirke, bezirke + sizeof(bezirke) / sizeof(bezirke[0]));

  return ret;
}

Strassenfeste StrassenfestManager::Impl::getAll()
{
  cxxtools::net::Uri uri = Configuration::it().berlinUrl();
  std::string results = _client.get(uri.path() + "?q=&bezirk=--+Alles+--&von_from=&von_to=&bis=&ipp=10000");

  std::istringstream in(results);

  StrassenfestResult r;
  in >> cxxtools::Json(r);

  return r.strassenfeste();
}

Strassenfeste StrassenfestManager::Impl::getAllByBezirk(const std::string& bezirk)
{
  cxxtools::net::Uri uri = Configuration::it().berlinUrl();

  cxxtools::QueryParams q;
  q.add("q", "");
  q.add("bezirk", bezirk);
  q.add("von_from", "");
  q.add("von_to", "");
  q.add("ipp", "20");

  std::string results = _client.get(uri.path() + '?' + q.getUrl());

  std::istringstream in(results);

  StrassenfestResult r;
  in >> cxxtools::Json(r);

  return r.strassenfeste();
}

StrassenfestResult StrassenfestManager::Impl::search(const std::string& keyword, const std::string& bezirk,
    const cxxtools::Date& von_from, const cxxtools::Date& von_to, const cxxtools::Date& bis,
    unsigned ipp, unsigned page)
{
  char buffer[40];

  cxxtools::net::Uri uri = Configuration::it().berlinUrl();

  cxxtools::QueryParams q;
  q.add("q", keyword);
  q.add("bezirk", bezirk);

  if (von_from != cxxtools::Date())
  {
    sprintf(buffer, "%02u.%02u.%04d", von_from.day(), von_from.month(), von_from.year());
    q.add("von_from", buffer);
  }

  if (von_to != cxxtools::Date())
  {
    sprintf(buffer, "%02u.%02u.%04d", von_to.day(), von_to.month(), von_to.year());
    q.add("von_to", buffer);
  }

  if (bis != cxxtools::Date())
  {
    sprintf(buffer, "%02u.%02u.%04d", bis.day(), bis.month(), bis.year());
    q.add("bis", buffer);
  }

  q.add("ipp", cxxtools::convert<std::string>(ipp));
  q.add("page", cxxtools::convert<std::string>(page));

  std::string results = _client.get(uri.path() + '?' + q.getUrl());

  std::istringstream in(results);

  StrassenfestResult r;
  in >> cxxtools::Json(r);

  return r;
}

////////////////////////////////////////////////////////////////////////
// StrassenfestManager

StrassenfestManager::StrassenfestManager()
  : _impl(new Impl())
{
  _impl->addRef();
}

StrassenfestManager::~StrassenfestManager()
{
  if (_impl && _impl->release() == 0)
    delete _impl;
}

StrassenfestManager::StrassenfestManager(const StrassenfestManager& other)
  : _impl(other._impl)
{
  if (_impl)
    _impl->addRef();
}

StrassenfestManager& StrassenfestManager::operator=(const StrassenfestManager& other)
{
  if (_impl && _impl->release() == 0)
    delete _impl;

  _impl = other._impl;

  if (_impl)
    _impl->addRef();

  return *this;
}

std::vector<std::string> StrassenfestManager::getBezirke()
{
  return _impl->getBezirke();
}

Strassenfeste StrassenfestManager::getAll()
{
  return _impl->getAll();
}

Strassenfeste StrassenfestManager::getAllByBezirk(const std::string& bezirk)
{
  return _impl->getAllByBezirk(bezirk);
}

StrassenfestResult StrassenfestManager::search(const std::string& keyword, const std::string& bezirk,
    const cxxtools::Date& von_from, const cxxtools::Date& von_to, const cxxtools::Date& bis,
    unsigned ipp, unsigned page)
{
  return _impl->search(keyword, bezirk, von_from, von_to, bis, ipp, page);
}

