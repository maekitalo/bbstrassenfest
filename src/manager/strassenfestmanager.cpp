/*
 * Copyright (C) 2013 Tommi Maekitalo
 *
 */

#include <manager/strassenfestmanager.h>
#include <model/strassenfestresult.h>
#include <configuration.h>
#include <cxxtools/net/uri.h>
#include <cxxtools/json.h>
#include <cxxtools/log.h>
#include <cxxtools/query_params.h>

log_define("strassenfest.manager");

namespace manager
{

StrassenfestManager::StrassenfestManager()
{
  _client.connect(Configuration::it().berlinUrl());
}

std::vector<std::string> StrassenfestManager::getBezirke()
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

model::Strassenfeste StrassenfestManager::getAll()
{
  cxxtools::net::Uri uri = Configuration::it().berlinUrl();
  std::string results = _client.get(uri.path() + "?q=&bezirk=--+Alles+--&von_from=&von_to=&bis=&ipp=10000");

  std::istringstream in(results);

  model::StrassenfestResult r;
  in >> cxxtools::Json(r);

  return r.strassenfeste();
}

model::Strassenfeste StrassenfestManager::getAllByBezirk(const std::string& bezirk)
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

  model::StrassenfestResult r;
  in >> cxxtools::Json(r);

  return r.strassenfeste();
}

model::Strassenfeste StrassenfestManager::search(const std::string& keyword, const cxxtools::Date& from, const cxxtools::Date& to)
{
  return model::Strassenfeste();
}

}
