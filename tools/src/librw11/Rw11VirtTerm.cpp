// $Id: Rw11VirtTerm.cpp 1186 2019-07-12 17:49:59Z mueller $
// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2013-2018 by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
// 
// Revision History: 
// Date         Rev Version  Comment
// 2018-12-02  1076   1.1    use unique_ptr for New()
// 2017-04-07   868   1.0.1  Dump(): add detail arg
// 2013-03-06   495   1.0    Initial version
// 2013-02-13   488   0.1    First draft
// ---------------------------------------------------------------------------

/*!
  \brief   Implemenation of Rw11VirtTerm.
*/
#include <memory>

#include "librtools/RparseUrl.hpp"
#include "librtools/RosFill.hpp"
#include "Rw11VirtTermPty.hpp"
#include "Rw11VirtTermTcp.hpp"

#include "Rw11VirtTerm.hpp"

using namespace std;

/*!
  \class Retro::Rw11VirtTerm
  \brief FIXME_docs
*/

// all method definitions in namespace Retro
namespace Retro {

//------------------------------------------+-----------------------------------
//! Default constructor

Rw11VirtTerm::Rw11VirtTerm(Rw11Unit* punit)
  : Rw11Virt(punit),
    fChannelId(),
    fRcvCb()
{
  fStats.Define(kStatNVTRcvPoll,     "NVTRcvPoll", "VT RcvPollHandler() calls");
  fStats.Define(kStatNVTSnd,         "NVTSnd",       "VT Snd() calls");
  fStats.Define(kStatNVTRcvByt,      "NVTRcvByt",    "VT bytes received");
  fStats.Define(kStatNVTSndByt,      "NVTSndByt",    "VT bytes send");
}

//------------------------------------------+-----------------------------------
//! Destructor

Rw11VirtTerm::~Rw11VirtTerm()
{}

//------------------------------------------+-----------------------------------
//! FIXME_docs

std::unique_ptr<Rw11VirtTerm> Rw11VirtTerm::New(const std::string& url,
                                                Rw11Unit* punit,
                                                RerrMsg& emsg)
{
  string scheme = RparseUrl::FindScheme(url, "tcp");
  unique_ptr<Rw11VirtTerm> up;
  
  if        (scheme == "pty") {             // scheme -> pty:
    up.reset(new Rw11VirtTermPty(punit));
    if (!up->Open(url, emsg)) up.reset();

  } else if (scheme == "tcp") {             // scheme -> tcp:
    up.reset(new Rw11VirtTermTcp(punit));
    if (!up->Open(url, emsg)) up.reset();

  } else {                                  // scheme -> no match
    emsg.Init("Rw11VirtTerm::New", string("Scheme '") + scheme +
              "' is not supported");

  }
  return up;
}

//------------------------------------------+-----------------------------------
//! FIXME_docs

void Rw11VirtTerm::Dump(std::ostream& os, int ind, const char* text,
                        int detail) const
{
  RosFill bl(ind);
  os << bl << (text?text:"--") << "Rw11VirtTerm @ " << this << endl;

  os << bl << "  fChannelId:      " << fChannelId << endl;
  Rw11Virt::Dump(os, ind, " ^", detail);
  return;
}

} // end namespace Retro
