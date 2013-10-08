/*
 * Copyright (C) 2013 Tommi Maekitalo
 *
 */

#include <strassenfest.h>
#include <cxxtools/serializationinfo.h>

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
}

void operator>>= (const cxxtools::SerializationInfo& si, Strassenfest& strassenfest)
{
    si.getMember("id")            >>= strassenfest._id;
    si.getMember("bezirk")        >>= strassenfest._bezirk;
    si.getMember("bezeichnung")   >>= strassenfest._bezeichnung;
    si.getMember("strasse")       >>= strassenfest._strasse;
    si.getMember("plz")           >>= strassenfest._plz;

    std::string s;

    si.getMember("von")           >>= s;
    strassenfest._von = str2date(s);

    si.getMember("bis")           >>= s;
    strassenfest._bis = str2date(s);

    si.getMember("zeit")          >>= strassenfest._zeit;
    si.getMember("veranstalter")  >>= strassenfest._veranstalter;
    si.getMember("mail")          >>= strassenfest._mail;
    si.getMember("www")           >>= strassenfest._www;
    si.getMember("bemerkungen")   >>= strassenfest._bemerkungen;
}
