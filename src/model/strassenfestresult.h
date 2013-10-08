/*
 * Copyright (C) 2013 Tommi Maekitalo
 *
 */

#ifndef STRASSENFESTRESULT_H
#define STRASSENFESTRESULT_H

#include <strassenfest.h>

namespace cxxtools
{
  class SerializationInfo;
}

class StrassenfestResult
{
    friend void operator>>= (const cxxtools::SerializationInfo& si, StrassenfestResult& strassenfestResult);

  public:
    typedef std::vector<std::string> Messages;

  private:
    Messages _messages;
    std::string _success;
    unsigned _resultCount;
    unsigned _itemsPerPage;
   Strassenfeste _strassenfeste;

  public:
    Messages::size_type messagesSize() const
    { return _messages.size(); }

    const std::string& message(Messages::size_type n) const
    { return _messages[n]; }

    unsigned resultCount() const    { return _resultCount; }
    unsigned itemsPerPage() const   { return _itemsPerPage; }

    Strassenfeste strassenfeste() const
    { return _strassenfeste; }

    Strassenfeste::size_type strassenfesteSize() const
    { return _strassenfeste.size(); }

    const Strassenfest& strassenfest(Strassenfeste::size_type n) const
    { return _strassenfeste[n]; }

};

void operator>>= (const cxxtools::SerializationInfo& si, StrassenfestResult& strassenfestResult);

#endif // STRASSENFESTRESULT_H

